//
// _endian.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#if defined(__APPLE__)
	#include <machine/endian.h>
	#include <libkern/OSByteOrder.h>
#elif defined(__OpenBSD__) || defined(__Bitrig__)
	#include <machine/endian.h>
#elif defined(__SVR4) && defined(__sun)
	#include <sys/byteorder.h>
#elif defined(__linux__) || defined(__CYGWIN__) || (defined(__GNUC__) && !defined(__clang__))
	#include <endian.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__minix)
	#include <sys/endian.h>
#endif

#ifndef COCONUT_RUNTIME_ENDIAN_HPP
#define COCONUT_RUNTIME_ENDIAN_HPP

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

	#if defined(__MICROSOFT__)
		#ifndef BYTE_ORDER
			#ifndef __BYTE_ORDER
				#if defined(REG_DWORD) && (REG_DWORD == REG_DWORD_BIG_ENDIAN)
					#define BYTE_ORDER BIG_ENDIAN
				#endif
				#ifndef BYTE_ORDER
					#define BYTE_ORDER LITTLE_ENDIAN
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
			#define BYTE_ORDER LITTLE_ENDIAN
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