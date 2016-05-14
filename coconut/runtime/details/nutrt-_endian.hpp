//
// nutrt-_endian.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#if defined(__APPLE__)
	#include <sys/types.h>
	#include <machine/endian.h>
	#include <libkern/OSByteOrder.h>
#elif defined(__OpenBSD__) || defined(__Bitrig__)
	#include <machine/endian.h>
	#include <sys/types.h>
	#include <sys/endian.h>
#elif defined(__SVR4) && defined(__sun)
	#include <sys/byteorder.h>
#elif defined(__linux__) || defined(__CYGWIN__) || (defined(__GNUC__) && !defined(__clang__))
	#include <endian.h>
	#include <byteswap.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
	#include <sys/types.h>
	#include <sys/endian.h>
#elif defined(__minix__) || defined(__minix)
	#include <sys/types.h>
	#include <sys/endian.h>
#elif defined(_MSC_VER)
	#include <stdlib.h>
#endif

#ifndef COCONUT_RUNTIME_ENDIAN_HPP
#define COCONUT_RUNTIME_ENDIAN_HPP

	#ifdef __has_builtin

		#if __has_builtin(__builtin_bswap16)
			#define ___COCONUT_BUILTIN_BSWAP16(x) __builtin_bswap16(x)
		#endif

		#if __has_builtin(__builtin_bswap32)
			#define ___COCONUT_BUILTIN_BSWAP32(x) __builtin_bswap32(x)
		#endif

		#if __has_builtin(__builtin_bswap64)
			#define ___COCONUT_BUILTIN_BSWAP64(x) __builtin_bswap64(x)
		#endif

	#endif

	#if defined(__GNUC__)
		#if (__GNUC__ > 4) || (__GNUC_MINOR__ > 7)
			#if !defined(___COCONUT_BUILTIN_BSWAP16)
				#define ___COCONUT_BUILTIN_BSWAP16(x) __builtin_bswap16(x)
			#endif
		#endif
		#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ > 2)
			#if !defined(___COCONUT_BUILTIN_BSWAP32)
				#define ___COCONUT_BUILTIN_BSWAP32(x) __builtin_bswap32(x)
			#endif

			#if !defined(___COCONUT_BUILTIN_BSWAP64)
				#define ___COCONUT_BUILTIN_BSWAP64(x) __builtin_bswap64(x)
			#endif
		#endif
	#endif

	#if defined(__ICL)
		#if !defined(___COCONUT_BUILTIN_BSWAP16)
			#define ___COCONUT_BUILTIN_BSWAP16(x) _bswap16(x)
		#endif
		#if !defined(___COCONUT_BUILTIN_BSWAP32)
			#define ___COCONUT_BUILTIN_BSWAP32(x) _bswap(x)
		#endif
		#if !defined(___COCONUT_BUILTIN_BSWAP64)
			#define ___COCONUT_BUILTIN_BSWAP64(x) _bswap64(x)
		#endif
	#endif

	#if defined(_MSC_VER)
		#if !defined(___COCONUT_BUILTIN_BSWAP16)
			#define ___COCONUT_BUILTIN_BSWAP16(x) _byteswap_ushort(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP32)
			#define ___COCONUT_BUILTIN_BSWAP32(x) _byteswap_ulong(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP64)
			#define ___COCONUT_BUILTIN_BSWAP64(x) _byteswap_uint64(x)
		#endif
	#endif

	#if defined(__linux__) || defined(__GLIBC__) || defined(__CYGWIN__)
		#if !defined(___COCONUT_BUILTIN_BSWAP16)
			#define ___COCONUT_BUILTIN_BSWAP16(x) bswap_16(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP32)
			#define ___COCONUT_BUILTIN_BSWAP32(x) bswap_32(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP64)
			#define ___COCONUT_BUILTIN_BSWAP64(x) bswap_64(x)
		#endif
	#endif

	#if defined(__sun__)
		#if !defined(___COCONUT_BUILTIN_BSWAP16)
			#define ___COCONUT_BUILTIN_BSWAP16(x) BSWAP_16(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP32)
			#define ___COCONUT_BUILTIN_BSWAP32(x) BSWAP_32(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP64)
			#define ___COCONUT_BUILTIN_BSWAP64(x) BSWAP_64(x)
		#endif
	#endif

	#if defined(__OpenBSD__)
		#if !defined(___COCONUT_BUILTIN_BSWAP16)
			#define ___COCONUT_BUILTIN_BSWAP16(x) swap16(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP32)
			#define ___COCONUT_BUILTIN_BSWAP32(x) swap32(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP64)
			#define ___COCONUT_BUILTIN_BSWAP64(x) swap64(x)
		#endif
	#endif

	#if defined(__FreeBSD__) || \
		defined(__NetBSD__) || defined(__DragonFly__) || \
		defined(__minix__) || defined(__minix)

		#if !defined(___COCONUT_BUILTIN_BSWAP16)
			#define ___COCONUT_BUILTIN_BSWAP16(x) bswap16(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP32)
			#define ___COCONUT_BUILTIN_BSWAP32(x) bswap32(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP64)
			#define ___COCONUT_BUILTIN_BSWAP64(x) bswap64(x)
		#endif

	#endif

	#if defined(__APPLE__)
		#if !defined(___COCONUT_BUILTIN_BSWAP16)
			#define ___COCONUT_BUILTIN_BSWAP16(x) OSSwapInt16(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP32)
			#define ___COCONUT_BUILTIN_BSWAP32(x) OSSwapInt32(x)
		#endif

		#if !defined(___COCONUT_BUILTIN_BSWAP64)
			#define ___COCONUT_BUILTIN_BSWAP64(x) OSSwapInt64(x)
		#endif
	#endif

	#ifndef LITTLE_ENDIAN
		#ifndef __LITTLE_ENDIAN
			#define LITTLE_ENDIAN 0x76543210
		#else
			#define LITTLE_ENDIAN __LITTLE_ENDIAN
		#endif
	#endif

	#ifndef BIG_ENDIAN
		#ifndef __BIG_ENDIAN
			#define BIG_ENDIAN 0x01234567
		#else
			#define BIG_ENDIAN __BIG_ENDIAN
		#endif
	#endif

	#if defined(__sun__)
		#ifndef BYTE_ORDER
			#if defined(_LITTLE_ENDIAN)
				#define BYTE_ORDER LITTLE_ENDIAN
			#else
				#define BYTE_ORDER BIG_ENDIAN
			#endif
		#endif
	#endif

	#if defined(__MICROSOFT__)
		#ifndef BYTE_ORDER
			#ifndef __BYTE_ORDER
				#if defined(REG_DWORD) && (REG_DWORD == REG_DWORD_BIG_ENDIAN)
					#define BYTE_ORDER BIG_ENDIAN
				#endif
				#ifndef BYTE_ORDER
					#if defined(_M_PPC)
						#define BYTE_ORDER BIG_ENDIAN
					#else
						#define BYTE_ORDER LITTLE_ENDIAN
					#endif
				#endif
			#else
				#define BYTE_ORDER __BYTE_ORDER
			#endif
		#endif
	#endif

	#ifndef BYTE_ORDER
		#ifdef __BYTE_ORDER
			#define BYTE_ORDER __BYTE_ORDER
		#elif defined(_BYTE_ORDER)
			#define BYTE_ORDER _BYTE_ORDER
		#else
			#if defined(_M_PPC) || defined(__ppc__) || defined(__ppc64__)
				#define BYTE_ORDER BIG_ENDIAN
			#else
				#define BYTE_ORDER LITTLE_ENDIAN
			#endif
		#endif
	#endif

	#ifndef __BYTE_ORDER
		#define __BYTE_ORDER BYTE_ORDER
	#endif

	#ifndef __BIG_ENDIAN
		#define __BIG_ENDIAN BIG_ENDIAN
	#endif

	#ifndef __LITTLE_ENDIAN
		#define __LITTLE_ENDIAN LITTLE_ENDIAN
	#endif

	#if defined(__FLOAT_WORD_ORDER) && __FLOAT_WORD_ORDER == __BIG_ENDIAN
		#undef COCONUT_FPU_LITTLE_ENDIAN
		#define COCONUT_FPU_BIG_ENDIAN 1
	#else
		#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN
			#undef COCONUT_FPU_LITTLE_ENDIAN
			#define COCONUT_FPU_BIG_ENDIAN 1
		#else
			#undef COCONUT_FPU_BIG_ENDIAN
			#define COCONUT_FPU_LITTLE_ENDIAN 1
		#endif
	#endif

	#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN

		#undef COCONUT_ARCH_LITTLE_ENDIAN
		#define COCONUT_ARCH_BIG_ENDIAN 1

	#elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN

		#undef COCONUT_ARCH_BIG_ENDIAN
		#define COCONUT_ARCH_LITTLE_ENDIAN 1

	#else
		#error UNKNOWN BYTE ORDER FIXME!
	#endif

#endif /* !COCONUT_RUNTIME_ENDIAN_HPP */

/* EOF */