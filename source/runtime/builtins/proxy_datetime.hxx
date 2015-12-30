//
// proxy_datetime.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include "unicode/calendar.h"
#include "unicode/dtfmtsym.h"
#include "unicode/smpdtfmt.h"
#include "unicode/fieldpos.h"

namespace coconut
{
	namespace runtime
	{
		namespace builtins
		{

#if defined(__MICROSOFT__) && !defined(TIME_UTC)
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			int gettimeofday(struct timeval * tp, void * tzp)
			{
				COCONUT_UNUSED(tzp);
				union { long long ns100; FILETIME ft; } now;
				GetSystemTimeAsFileTime(&now.ft);
				tp->tv_usec = (long)((now.ns100 / 10LL) % 1000000LL);
				tp->tv_sec = (long)((now.ns100 - 116444736000000000LL) / 10000000LL);
				return 0;
			}

			struct time_spec
			{
				std::int64_t tv_sec;
				std::int64_t tv_nsec;
			};
#else
			typedef struct timespec time_spec;
#endif
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::int64_t datetime_nanotime()
			{
				std::int64_t result = 0LL;
#if defined(TIME_UTC)
				struct timespec tm;
				if (TIME_UTC == timespec_get(&tm, TIME_UTC)) {
					result = static_cast<std::int64_t>((tm.tv_sec * 1000000000LL) + tm.tv_nsec);
				}
				
#elif defined(_MSC_VER)
				FILETIME ft;
				GetSystemTimeAsFileTime(&ft);
				long long x;
				x = static_cast<long long>(ft.dwHighDateTime);
				x <<= 32;
				x |= static_cast<long long>(ft.dwLowDateTime);
				x /=10;
				x -= 11644473600000000LL;
				x *= 1000LL;
				result = static_cast<std::int64_t>(x);
#elif __MACH__
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
#elif CLOCK_REALTIME
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
			std::uint64_t datetime_microtime()
			{ return (datetime_nanotime() / 1000LL); }
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint64_t datetime_millitime()
			{ return (datetime_nanotime() / 1000000LL); }
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			time_spec datetime_timespec(std::int64_t nanosecond)
			{
				time_spec tm;
				tm.tv_sec = nanosecond / 1000000000LL;
				tm.tv_nsec = nanosecond % 1000000000LL;
				return tm;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool datetime_epoch(time_spec * tms)
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
				
#elif defined(_MSC_VER)
				
				union { unsigned long long ns100; FILETIME ft; } now;
				
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
		
#elif __MACH__
				
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
				
#elif CLOCK_REALTIME
				
				if (tms == nullptr) {
					return result;
				}
				
				if (0 != clock_gettime(CLOCK_REALTIME, &tms)) {
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
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::string datetime_format_utc(double milliseconds)
			{
				UErrorCode status = U_ZERO_ERROR;
				
				icu::SimpleDateFormat dtf = icu::SimpleDateFormat
				(
					UnicodeString::fromUTF8(u8"yyyy-MM-dd'T'HH:mm:ss.SSS'Z'"),
				 	Locale::getRoot(),
					status
				);
				
				dtf.setTimeZone(*(icu::TimeZone::getGMT()));
				UnicodeString buf;
				dtf.format(milliseconds, buf);
				
				std::string result;
				buf.toUTF8String<std::string>(result);
				return result;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			double datetime_parse_utc(const std::string & utc)
			{
				UErrorCode status = U_ZERO_ERROR;
				UDate milliseconds = 0.0;
				
				constexpr auto fmt_short = u8"yyyy-MM-dd'T'HH:mm:ss'Z'";
				constexpr auto fmt_long = u8"yyyy-MM-dd'T'HH:mm:ss.SSS'Z'";
				
				icu::SimpleDateFormat dtf = icu::SimpleDateFormat
				(
					UnicodeString::fromUTF8((utc.find(".") != std::string::npos) ? fmt_long : fmt_short),
					Locale::getRoot(),
					status
				);
				if (U_FAILURE(status)) {
					return 0.0;
				}
				UnicodeString buf = UnicodeString::fromUTF8(icu::StringPiece(utc));
				dtf.setTimeZone(*(icu::TimeZone::getGMT()));
				icu::ParsePosition pos(0);
				milliseconds = dtf.parse(
					buf,
					pos
				);
				if (!milliseconds) {
					status = U_ZERO_ERROR;
					dtf.applyLocalizedPattern(UnicodeString::fromUTF8(fmt_short), status);
					if (U_FAILURE(status)) {
						return 0.0;
					}
					milliseconds = dtf.parse(
						buf,
						pos
					);
				}
				return milliseconds;
			}
		}
	}
}

#pragma mark -

// Monday 1 January 2001 00:00:00 AM, GMT, Greenwich, London, UK ; 2001-01-01T00:00:00+00:00.

#define COCONUT_APPLE_EPOCH_PLAINSECONDS  978307200.000
#define COCONUT_APPLE_EPOCH_DOUBLESECONDS 978307200.000
#define COCONUT_APPLE_EPOCH_MILLISECONDS  978307200000.000
#define COCONUT_APPLE_EPOCH_MICROSECONDS  978307200000000.000
#define COCONUT_APPLE_EPOCH_NANOSECONDS   978307200000000000.000
#define COCONUT_FORTY_YEARS_MILLISECONDS  1262277040000.000

/* EOF */