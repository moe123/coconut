//
// datetime_epoch.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#if defined(__MICROSOFT__)
	#undef UNICODE
	#undef _UNICODE

	#define UNICODE 1
	#define _UNICODE 1

	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <rpcdce.h>
	#include <wincrypt.h>
	#include <windows.h>
#elif defined(__APPLE__)

___COCONUT_BEGIN_DECLS
	#include <mach/clock.h>
	#include <mach/mach.h>
	#include <mach/mach_error.h>
___COCONUT_END_DECLS

#endif

#include "unicode/calendar.h"
#include "unicode/dtfmtsym.h"
#include "unicode/smpdtfmt.h"
#include "unicode/fieldpos.h"

namespace coconut {
	namespace runtime {
		namespace builtins {

#if defined(__MICROSOFT__) && !defined(TIME_UTC)

struct time_spec
{
	std::int64_t tv_sec;
	std::int64_t tv_nsec;
};

#else

___COCONUT_BEGIN_DECLS
typedef struct timespec time_spec;
___COCONUT_END_DECLS

#endif

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t datetime_nanotime()
{
	std::int64_t result = 0LL;

#if defined(TIME_UTC) && (!defined(CLOCK_REALTIME) || !defined(__APPLE__))

	struct timespec tm;
	if (TIME_UTC == timespec_get(&tm, TIME_UTC)) {
		result = static_cast<std::int64_t>((tm.tv_sec * 1000000000LL) + tm.tv_nsec);
	}
	
#elif defined(__MICROSOFT__)

	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	long long x;
	x = static_cast<long long>(ft.dwHighDateTime);
	x <<= 32;
	x |= static_cast<long long>(ft.dwLowDateTime);
	x /= 10;
	x -= 11644473600000000LL;
	x *= 1000LL;
	result = static_cast<std::int64_t>(x);

#elif defined(__APPLE__)

	kern_return_t mret;
	clock_serv_t mclk;
	mach_timespec_t tm;
	
	mret = host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &mclk);
	if (KERN_SUCCESS == mret) {
		mret = clock_get_time(mclk, &tm);
		if (KERN_SUCCESS == mret) {
			result = static_cast<std::int64_t>((tm.tv_sec * 1000000000LL) + tm.tv_nsec);
		}
	}
	mach_port_deallocate(mach_task_self(), mclk);

#elif defined(CLOCK_REALTIME)
	
	struct timespec tm;
	if (0 == clock_gettime(CLOCK_REALTIME, &tm)) {
		result = static_cast<std::int64_t>((tm.tv_sec * 1000000000LL) + tm.tv_nsec);
	}

#else

	struct timeval tm;
	gettimeofday(&tm, NULL);
	result = static_cast<std::int64_t>((tm.tv_sec * 1000000000LL) + (tm.tv_usec * 1000LL));
	
#endif
	
	return result;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t datetime_microtime()
{ return (datetime_nanotime() / 1000LL); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t datetime_millitime()
{ return (datetime_nanotime() / 1000000LL); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void datetime_dotimespec(std::int64_t nanosecond, time_spec * tms_out)
{
	tms_out->tv_sec = nanosecond / 1000000000LL;
	tms_out->tv_nsec = nanosecond >= 0 ? nanosecond % 1000000000LL : -((-nanosecond) % 1000000000LL);
}

#if defined(__MICROSOFT__)

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int datetime_gettimeofday_v1(struct timeval * tmv, void * tz)
{
	COCONUT_UNUSED(tz);
	if (tp) {
		std::int64_t microsecond = datetime_microtime();
		tmv->tv_sec = microsecond / 1000000LL;
		tmv->tv_usec = microsecond >= 0 ? microsecond % 1000000LL : -((-microsecond) % 1000000LL);
		return 0;
	}
	return -1;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int datetime_gettimeofday_v0(struct timeval * tmv, void * tz)
{
	COCONUT_UNUSED(tz);
	union { long long ns100; FILETIME ft; } now;
	GetSystemTimeAsFileTime(&now.ft);
	tmv->tv_usec = ((now.ns100 / 10LL) % 1000000LL);
	tmv->tv_sec = ((now.ns100 - 116444736000000000LL) / 10000000LL);
	return 0;
}

#endif

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool datetime_epoch(time_spec * tms)
{
	if (tms) {
		std::uint64_t nanosecond = datetime_nanotime();
		if (nanosecond) {
			datetime_dotimespec(nanosecond, tms);
			return true;
		}
	}
	return false;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool datetime_epoch_v0(time_spec * tms)
{
	bool result = false;

#if defined(TIME_UTC)
	
	if (tms == nullptr) {
		return result;
	}
	
	if (TIME_UTC != timespec_get(&tms, TIME_UTC)) {
		tms->tv_sec = 0;
		tms->tv_nsec = 0;
	} else {
		result = true;
	}
	
#elif defined(__MICROSOFT__)
	
	union { long long ns100; FILETIME ft; } now;
	
	if (tms == nullptr) {
		return result;
	}
	
	tms->tv_sec = 0;
	tms->tv_nsec = 0;
	
	GetSystemTimeAsFileTime(&now.ft);
	now.ns100 -= (11644473600000000ULL * 10ULL);
	
	tms->tv_sec = unsafe_cast<std::int64_t>(now.ns100 / 10000000ULL);
	tms->tv_nsec = unsafe_cast<std::int64_t>(now.ns100 % 10000000ULL) * 100;
	
	result = true;

#elif defined(__APPLE__)
	
	kern_return_t mret;
	clock_serv_t mclk;
	mach_timespec_t mtms;
	
	if (tms == nullptr) {
		return result;
	}
	
	tms->tv_sec = 0;
	tms->tv_nsec = 0;
	
	mret = host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &mclk);
	if (KERN_SUCCESS == mret) {
		mret = clock_get_time(mclk, &mtms);
		if (KERN_SUCCESS == mret) {
			tms->tv_sec = mtms.tv_sec;
			tms->tv_nsec = mtms.tv_nsec;
			result = true;
		}
	}
	mach_port_deallocate(mach_task_self(), mclk);
	
#elif defined(CLOCK_REALTIME)
	
	if (tms == nullptr) {
		return result;
	}
	
	if (0 != clock_gettime(CLOCK_REALTIME, tms)) {
		tms->tv_sec = 0;
		tms->tv_nsec = 0;
	} else {
		result = true;
	}

#else

	if (tms == nullptr) {
		return result;
	}
	
	double utc_milli = static_cast<double>(icu::Calendar::getNow());
	if (utc_milli) {
		result = true;
		tms->tv_sec = static_cast<std::int64_t>(utc_milli) / 1000;
		tms->tv_nsec = 0;
	} else {
		tms->tv_sec = 0;
		tms->tv_nsec = 0;
	}

#endif

	return result;
}

#pragma mark -

// Monday 1 January 2001 00:00:00 AM, GMT, Greenwich, London, UK ; 2001-01-01T00:00:00+00:00.

#define COCONUT_APPLE_EPOCH_PLAINSECONDS  978307200.000
#define COCONUT_APPLE_EPOCH_DOUBLESECONDS 978307200.000
#define COCONUT_APPLE_EPOCH_MILLISECONDS  978307200000.000
#define COCONUT_APPLE_EPOCH_MICROSECONDS  978307200000000.000
#define COCONUT_APPLE_EPOCH_NANOSECONDS   978307200000000000.000
#define COCONUT_FORTY_YEARS_MILLISECONDS  1262277040000.000
	
}}} /* EONS */

/* EOF */