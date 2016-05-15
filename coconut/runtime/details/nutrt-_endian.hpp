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
	#include <sys/types.h>
	#include <machine/endian.h>
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

#if !defined(_MSC_VER)
	#include <stdint.h>
#endif

#ifndef COCONUT_RUNTIME_ENDIAN_HPP
#define COCONUT_RUNTIME_ENDIAN_HPP

	#if defined(__clang__) && defined(__has_builtin)

		#if __has_builtin(__builtin_bswap16)
			#define COCONUT_BSWAP16(x) __builtin_bswap16((x))
		#endif

		#if __has_builtin(__builtin_bswap32)
			#define COCONUT_BSWAP32(x) __builtin_bswap32((x))
		#endif

		#if __has_builtin(__builtin_bswap64)
			#define COCONUT_BSWAP64(x) __builtin_bswap64((x))
		#endif

	#endif

	#if defined(__GNUC__)
		#if (__GNUC__ > 4) || (__GNUC_MINOR__ > 7)
			#if !defined(COCONUT_BSWAP16)
				#define COCONUT_BSWAP16(x) __builtin_bswap16((x))
			#endif
		#endif
		#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ > 2)
			#if !defined(COCONUT_BSWAP32)
				#define COCONUT_BSWAP32(x) __builtin_bswap32((x))
			#endif

			#if !defined(COCONUT_BSWAP64)
				#define COCONUT_BSWAP64(x) __builtin_bswap64((x))
			#endif
		#endif
	#endif

	#if defined(__ICL)
		#if !defined(COCONUT_BSWAP16)
			#define COCONUT_BSWAP16(x) _bswap16((x))
		#endif
		#if !defined(COCONUT_BSWAP32)
			#define COCONUT_BSWAP32(x) _bswap((x))
		#endif
		#if !defined(COCONUT_BSWAP64)
			#define COCONUT_BSWAP64(x) _bswap64((x))
		#endif
	#endif

	#if defined(_MSC_VER)
		#if !defined(COCONUT_BSWAP16)
			#define COCONUT_BSWAP16(x) _byteswap_ushort((x))
		#endif

		#if !defined(COCONUT_BSWAP32)
			#define COCONUT_BSWAP32(x) _byteswap_ulong((x))
		#endif

		#if !defined(COCONUT_BSWAP64)
			#define COCONUT_BSWAP64(x) _byteswap_uint64((x))
		#endif
	#endif

	#if defined(__linux__) || defined(__GLIBC__) || defined(__CYGWIN__)
		#if !defined(COCONUT_BSWAP16)
			#define COCONUT_BSWAP16(x) bswap_16((x))
		#endif

		#if !defined(COCONUT_BSWAP32)
			#define COCONUT_BSWAP32(x) bswap_32((x))
		#endif

		#if !defined(COCONUT_BSWAP64)
			#define COCONUT_BSWAP64(x) bswap_64((x))
		#endif
	#endif

	#if defined(__sun__)
		#if !defined(COCONUT_BSWAP16)
			#define COCONUT_BSWAP16(x) BSWAP_16((x))
		#endif

		#if !defined(COCONUT_BSWAP32)
			#define COCONUT_BSWAP32(x) BSWAP_32((x))
		#endif

		#if !defined(COCONUT_BSWAP64)
			#define COCONUT_BSWAP64(x) BSWAP_64((x))
		#endif
	#endif

	#if defined(__OpenBSD__)
		#if !defined(COCONUT_BSWAP16)
			#define COCONUT_BSWAP16(x) swap16((x))
		#endif

		#if !defined(COCONUT_BSWAP32)
			#define COCONUT_BSWAP32(x) swap32((x))
		#endif

		#if !defined(COCONUT_BSWAP64)
			#define COCONUT_BSWAP64(x) swap64((x))
		#endif
	#endif

	#if defined(__FreeBSD__) || \
		defined(__NetBSD__) || defined(__DragonFly__) || \
		defined(__minix__) || defined(__minix)

		#if !defined(COCONUT_BSWAP16)
			#define COCONUT_BSWAP16(x) bswap16((x))
		#endif

		#if !defined(COCONUT_BSWAP32)
			#define COCONUT_BSWAP32(x) bswap32((x))
		#endif

		#if !defined(COCONUT_BSWAP64)
			#define COCONUT_BSWAP64(x) bswap64((x))
		#endif

	#endif

	#if defined(__APPLE__)
		#if !defined(COCONUT_BSWAP16)
			#define COCONUT_BSWAP16(x) OSSwapInt16((x))
		#endif

		#if !defined(COCONUT_BSWAP32)
			#define COCONUT_BSWAP32(x) OSSwapInt32((x))
		#endif

		#if !defined(COCONUT_BSWAP64)
			#define COCONUT_BSWAP64(x) OSSwapInt64((x))
		#endif
	#endif

	#if !defined(COCONUT_BSWAP16)
		#pragma warning COCONUT_BSWAP16 BYE BYE!

		#define COCONUT_U16_DECL(x) uint16_t x
		#define COCONUT_U16_CAST(x) ((uint16_t)(x))

		#define COCONUT_BSWAP16(x) \
		({ \
			COCONUT_U16_DECL(v) = (x);\
			(COCONUT_U16_CAST(\
				((COCONUT_U16_CAST(v) & COCONUT_U16_CAST(0x00FFU)) << 8) | \
				((COCONUT_U16_CAST(v) & COCONUT_U16_CAST(0xFF00U)) >> 8) )); \
		})

		#undef COCONUT_U16_DECL
		#undef COCONUT_U16_CAST
	#endif

	#if !defined(COCONUT_BSWAP32)
		#pragma warning COCONUT_BSWAP32 BYE BYE!

		#define COCONUT_U32_DECL(x) uint32_t x
		#define COCONUT_U32_CAST(x) ((uint32_t)(x))

		#define COCONUT_BSWAP32(x) \
		({ \
			COCONUT_U32_DECL(v) = (x); \
			(COCONUT_U32_CAST( \
				((COCONUT_U32_CAST(v) & COCONUT_U32_CAST(0x000000FFUL)) << 24) | \
				((COCONUT_U32_CAST(v) & COCONUT_U32_CAST(0x0000FF00UL)) <<  8) | \
				((COCONUT_U32_CAST(v) & COCONUT_U32_CAST(0x00FF0000UL)) >>  8) | \
				((COCONUT_U32_CAST(v) & COCONUT_U32_CAST(0xFF000000UL)) >> 24) )); \
		})

		#undef COCONUT_U32_DECL
		#undef COCONUT_U32_CAST
	#endif

	#if !defined(COCONUT_BSWAP64)
		#pragma warning COCONUT_BSWAP64 BYE BYE!

		#define COCONUT_U64_DECL(x) uint64_t x
		#define COCONUT_U64_CAST(x) ((uint64_t)(x))

		#define COCONUT_BSWAP64(x) \
		({ \
			COCONUT_U64_DECL(v) = (x); \
				(COCONUT_U64_CAST( \
				COCONUT_U64_CAST((COCONUT_U64_CAST(v) & COCONUT_U64_CAST(0x00000000000000FFULL)) << 56) | \
				COCONUT_U64_CAST((COCONUT_U64_CAST(v) & COCONUT_U64_CAST(0x000000000000FF00ULL)) << 40) | \
				COCONUT_U64_CAST((COCONUT_U64_CAST(v) & COCONUT_U64_CAST(0x0000000000FF0000ULL)) << 24) | \
				COCONUT_U64_CAST((COCONUT_U64_CAST(v) & COCONUT_U64_CAST(0x00000000FF000000ULL)) <<  8) | \
				COCONUT_U64_CAST((COCONUT_U64_CAST(v) & COCONUT_U64_CAST(0x000000FF00000000ULL)) >>  8) | \
				COCONUT_U64_CAST((COCONUT_U64_CAST(v) & COCONUT_U64_CAST(0x0000FF0000000000ULL)) >> 24) | \
				COCONUT_U64_CAST((COCONUT_U64_CAST(v) & COCONUT_U64_CAST(0x00FF000000000000ULL)) >> 40) | \
				COCONUT_U64_CAST((COCONUT_U64_CAST(v) & COCONUT_U64_CAST(0xFF00000000000000ULL)) >> 56) )); \
		})

		#undef COCONUT_U64_DECL
		#undef COCONUT_U64_CAST
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
			#if defined(_M_PPC) || \
				defined(__ppc__) || \
				defined(__ppc64__) || \
				defined(__powerpc) || \
				defined(__powerpc__) || \
				defined(__powerpc64__) || \
				defined(__POWERPC__) || \
				defined(__PPC__) || \
				defined(__PPC64__) || \
				defined(_ARCH_PPC) || \
				defined(_ARCH_PPC64) || \
				defined(__ppc) || \
				defined(__PPCGECKO__) || \
				defined(__PPCBROADWAY__) || \
				defined(_XENON)

				#define BYTE_ORDER BIG_ENDIAN
			#else
				#define BYTE_ORDER LITTLE_ENDIAN
			#endif
		#endif
	#endif

	#ifndef BYTE_ORDER
		#if defined(__i386__) || \
			defined(__i386) || \
			defined(__x86_64__) || \
			defined(__x86_64) || \
			defined(__amd64) || \
			defined(__amd64__) || \
			defined(_M_I86) || \
			defined(__I86__) || \
			defined(_X86_) || \
			defined(__X86__) || \
			defined(_M_X64) || \
			defined(_M_AMD64) || \
			defined(_M_IX86)

			#define BYTE_ORDER LITTLE_ENDIAN
		#else
			#define BYTE_ORDER BIG_ENDIAN
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

	#if defined(COCONUT_ARCH_LITTLE_ENDIAN)

		#define ___COCONUT_htobe16(x) COCONUT_BSWAP16((x))
		#define ___COCONUT_htobe32(x) COCONUT_BSWAP32((x))
		#define ___COCONUT_htobe64(x) COCONUT_BSWAP64((x))

		#define ___COCONUT_betoh16(x) COCONUT_BSWAP16((x))
		#define ___COCONUT_betoh32(x) COCONUT_BSWAP32((x))
		#define ___COCONUT_betoh64(x) COCONUT_BSWAP64((x))

		#define ___COCONUT_htole16(x) (x)
		#define ___COCONUT_htole32(x) (x)
		#define ___COCONUT_htole64(x) (x)

		#define ___COCONUT_letoh16(x) (x)
		#define ___COCONUT_letoh32(x) (x)
		#define ___COCONUT_letoh64(x) (x)

		#define ___COCONUT_htons(x) COCONUT_BSWAP16((x))
		#define ___COCONUT_htonl(x) COCONUT_BSWAP32((x))
		#define ___COCONUT_htonll(x) COCONUT_BSWAP64((x))

		#define ___COCONUT_ntohs(x) COCONUT_BSWAP16((x))
		#define ___COCONUT_ntohl(x) COCONUT_BSWAP32((x))
		#define ___COCONUT_ntohll(x) COCONUT_BSWAP64((x))

	#endif

	#if defined(COCONUT_ARCH_BIG_ENDIAN)

		#define ___COCONUT_htobe16(x) (x)
		#define ___COCONUT_htobe32(x) (x)
		#define ___COCONUT_htobe64(x) (x)

		#define ___COCONUT_betoh16(x) (x)
		#define ___COCONUT_betoh32(x) (x)
		#define ___COCONUT_betoh64(x) (x)

		#define ___COCONUT_htole16(x) COCONUT_BSWAP16((x))
		#define ___COCONUT_htole32(x) COCONUT_BSWAP32((x))
		#define ___COCONUT_htole64(x) COCONUT_BSWAP64((x))

		#define ___COCONUT_letoh16(x) COCONUT_BSWAP16((x))
		#define ___COCONUT_letoh32(x) COCONUT_BSWAP32((x))
		#define ___COCONUT_letoh64(x) COCONUT_BSWAP64((x))

		#define ___COCONUT_htons(x) (x)
		#define ___COCONUT_htonl(x) (x)
		#define ___COCONUT_htonll(x) (x)

		#define ___COCONUT_ntohs(x) (x)
		#define ___COCONUT_ntohl(x) (x)
		#define ___COCONUT_ntohll(x) (x)

	#endif

	#if !defined(bswap16)
		#define bswap16 COCONUT_BSWAP16
	#endif

	#if !defined(bswap32)
		#define bswap32 COCONUT_BSWAP32
	#endif

	#if !defined(bswap64)
		#define bswap64 COCONUT_BSWAP64
	#endif

	#if !defined(htobe16)
		#define htobe16 ___COCONUT_htobe16
	#endif

	#if !defined(htobe32)
		#define htobe32 ___COCONUT_htobe32
	#endif

	#if !defined(htobe64)
		#define htobe64 ___COCONUT_htobe64
	#endif

	#if !defined(betoh16)
		#define betoh16 ___COCONUT_betoh16
	#endif

	#if !defined(betoh32)
		#define betoh32 ___COCONUT_betoh32
	#endif

	#if !defined(betoh64)
		#define betoh64 ___COCONUT_betoh64
	#endif

	#if !defined(htole16)
		#define htole16 ___COCONUT_htole16
	#endif

	#if !defined(htole32)
		#define htole32 ___COCONUT_htole32
	#endif

	#if !defined(htole64)
		#define htole64 ___COCONUT_htole64
	#endif

	#if !defined(letoh16)
		#define letoh16 ___COCONUT_letoh16
	#endif

	#if !defined(letoh32)
		#define letoh32 ___COCONUT_letoh32
	#endif

	#if !defined(letoh64)
		#define letoh64 ___COCONUT_letoh64
	#endif

	#if !defined(htons)
		#define htons ___COCONUT_htons
	#endif

	#if !defined(htonl)
		#define htonl ___COCONUT_htonl
	#endif

	#if !defined(htonll)
		#define htonll ___COCONUT_htonll
	#endif

	#if !defined(ntohs)
		#define ntohs ___COCONUT_ntohs
	#endif

	#if !defined(ntohl)
		#define ntohl ___COCONUT_ntohl
	#endif

	#if !defined(ntohll)
		#define ntohll ___COCONUT_ntohll
	#endif

#endif /* !COCONUT_RUNTIME_ENDIAN_HPP */

/* EOF */