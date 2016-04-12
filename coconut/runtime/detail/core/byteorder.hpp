//
// byteorder.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_BYTEORDER_HPP
#define COCONUT_RUNTIME_BYTEORDER_HPP

namespace coconut
{
	namespace runtime
	{
		namespace byteorder
		{
			typedef struct { std::uint32_t v; } fswp_t;
			typedef struct { std::uint64_t v; } dswp_t;

			template <typename T>
			inline void swpi(T & x)
			{ char & raw = reinterpret_cast<char &>(x); std::reverse(&raw, &raw + sizeof(T)); }
			
			template <typename T>
			inline T swpc(T x)
			{ swpi(x); return x; }
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint16_t swpc16(const volatile std::uint16_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapInt16(x);
			#elif defined(__ICL)
				return _bswap16(x);
			#elif defined(__GNUC__) || defined(__clang__)
				return __builtin_bswap16(x);
			#elif __MICROSOFT_VS__
				return _byteswap_ushort(x);
			#else
				std::uint16_t v;
				v = (std::uint16_t)(((x << 8) & 0xFF00) | ((x >> 8) & 0xFF));
				return v;
			#endif
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::int16_t swpcs16(std::int16_t & x)
			{ return swpc16(x); }

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint32_t swpc32(const volatile std::uint32_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapInt32(x);
			#elif defined(__GNUC__) || defined(__clang__)
				return __builtin_bswap32(x);
			#elif __MICROSOFT_VS__
				return _byteswap_ulong(x);
			#else
				std::uint32_t v;
				v = ((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | ((x >> 24) & 0xFF);
				return v;
			#endif
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::int32_t swpcs32(std::int32_t & x)
			{ return swpc32(x); }
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint64_t swpc64(const volatile std::uint64_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapInt64(x);
			#elif defined(__GNUC__) || defined(__clang__)
				return __builtin_bswap64(x);
			#elif __MICROSOFT_VS__
				return _byteswap_uint64(x);
			#else
				std::uint64_t v = (
					(x >> 56)
					| ((x << 40) & 0x00FF000000000000ULL)
					| ((x << 24) & 0x0000FF0000000000ULL)
					| ((x <<  8) & 0x000000FF00000000ULL)
					| ((x >>  8) & 0x00000000FF000000ULL)
					| ((x >> 24) & 0x0000000000FF0000ULL)
					| ((x >> 40) & 0x000000000000FF00ULL)
					| (x << 56)
				);
				return v;
			#endif
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::int64_t swpcs64(std::int64_t & x)
			{ return swpc64(x); }
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void r16be(const std::uint8_t (&r)[2], std::uint16_t & out)
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[0]) << 8;
				x |= r[1];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void rs16be(const std::uint8_t (&r)[2], std::int16_t & out)
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[0]) << 8;
				x |= r[1];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void r32be(const std::uint8_t (&r)[4], std::uint32_t & out)
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[0]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 8;
				x |= r[3];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void rs32be(const std::uint8_t (&r)[4], std::int32_t & out)
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[0]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 8;
				x |= r[3];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void r64be(const std::uint8_t (&r)[8], std::uint64_t & out)
			{
				std::uint64_t x = 0;
				x |= unsafe_cast<std::uint64_t>(r[0]) << 56;
				x |= unsafe_cast<std::uint64_t>(r[1]) << 48;
				x |= unsafe_cast<std::uint64_t>(r[2]) << 40;
				x |= unsafe_cast<std::uint64_t>(r[3]) << 32;
				x |= r[4] << 24;
				x |= r[5] << 16;
				x |= r[6] << 8;
				x |= r[7];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void rs64be(const std::uint8_t (&r)[8], std::int64_t & out)
			{
				std::uint64_t x = 0;
				x |= unsafe_cast<std::uint64_t>(r[0]) << 56;
				x |= unsafe_cast<std::uint64_t>(r[1]) << 48;
				x |= unsafe_cast<std::uint64_t>(r[2]) << 40;
				x |= unsafe_cast<std::uint64_t>(r[3]) << 32;
				x |= r[4] << 24;
				x |= r[5] << 16;
				x |= r[6] << 8;
				x |= r[7];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void r16le(const std::uint8_t (&r)[2], std::uint16_t & out)
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[1]) << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void rs16le(const std::uint8_t (&r)[2], std::int16_t & out)
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[1]) << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void r32le(const std::uint8_t (&r)[4], std::uint32_t & out)
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[3]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void rs32le(const std::uint8_t (&r)[4], std::int32_t & out)
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[3]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void r64le(const std::uint8_t (&r)[8], std::uint64_t & out)
			{
				std::uint64_t x = 0;
				x |= unsafe_cast<std::uint64_t>(r[7]) << 56;
				x |= unsafe_cast<std::uint64_t>(r[6]) << 48;
				x |= unsafe_cast<std::uint64_t>(r[5]) << 40;
				x |= unsafe_cast<std::uint64_t>(r[4]) << 32;
				x |= r[3] << 24;
				x |= r[2] << 16;
				x |= r[1] << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void rs64le(const std::uint8_t (&r)[8], std::int64_t & out)
			{
				std::uint64_t x = 0;
				x |= unsafe_cast<std::uint64_t>(r[7]) << 56;
				x |= unsafe_cast<std::uint64_t>(r[6]) << 48;
				x |= unsafe_cast<std::uint64_t>(r[5]) << 40;
				x |= unsafe_cast<std::uint64_t>(r[4]) << 32;
				x |= r[3] << 24;
				x |= r[2] << 16;
				x |= r[1] << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void w16be(std::uint16_t in, std::uint8_t (&w)[2])
			{
				w[0] = ((in >> 8) & 0xFF);
				w[1] = (in & 0xFF);
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void w32be(std::uint32_t in, std::uint8_t (&w)[4])
			{
				w[0] = ((in & 0xFF000000UL) >> 24);
				w[1] = ((in & 0x00FF0000UL) >> 16);
				w[2] = ((in & 0x0000FF00UL) >> 8);
				w[3] = ((in & 0x000000FFUL));
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void w64be(std::uint64_t in, std::uint8_t (&w)[8])
			{
				w[0] = ((in & 0xFF00000000000000ULL) >> 56);
				w[1] = ((in & 0x00FF000000000000ULL) >> 48);
				w[2] = ((in & 0x0000FF0000000000ULL) >> 40);
				w[3] = ((in & 0x000000FF00000000ULL) >> 32);
				w[4] = ((in & 0x00000000FF000000ULL) >> 24);
				w[5] = ((in & 0x0000000000FF0000ULL) >> 16);
				w[6] = ((in & 0x000000000000FF00ULL) >> 8);
				w[7] = ((in & 0x00000000000000FFULL));
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void w16le(std::uint16_t in, std::uint8_t (&w)[2])
			{
				w[0] = (in & 0xFF);
				w[1] = ((in >> 8) & 0xFF);
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void w32le(std::uint32_t in, std::uint8_t (&w)[4])
			{
				w[0] = ((in & 0x000000FFUL));
				w[1] = ((in & 0x0000FF00UL) >> 8);
				w[2] = ((in & 0x00FF0000UL) >> 16);
				w[3] = ((in & 0xFF000000UL) >> 24);
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void w64le(std::uint64_t in, std::uint8_t (&w)[8])
			{
				w[0] = ((in & 0x00000000000000FFULL));
				w[1] = ((in & 0x000000000000FF00ULL) >> 8);
				w[2] = ((in & 0x0000000000FF0000ULL) >> 16);
				w[3] = ((in & 0x00000000FF000000ULL) >> 24);
				w[4] = ((in & 0x000000FF00000000ULL) >> 32);
				w[5] = ((in & 0x0000FF0000000000ULL) >> 40);
				w[6] = ((in & 0x00FF000000000000ULL) >> 48);
				w[7] = ((in & 0xFF00000000000000ULL) >> 56);
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint16_t be2h16(std::uint16_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapBigToHostInt16(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return swpc16(x);
			#else
				return x;
			#endif
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint32_t be2h32(std::uint32_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapBigToHostInt32(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return swpc32(x);
			#else
				return x;
			#endif
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint64_t be2h64(std::uint64_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapBigToHostInt64(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return swpc64(x);
			#else
				return x;
			#endif
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint16_t h2be16(std::uint16_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapHostToBigInt16(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return swpc16(x);
			#else
				return x;
			#endif
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint32_t h2be32(std::uint32_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapHostToBigInt32(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return swpc32(x);
			#else
				return x;
			#endif
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint64_t h2be64(std::uint64_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapHostToBigInt64(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return swpc64(x);
			#else
				return x;
			#endif
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint16_t le2h16(std::uint16_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapLittleToHostInt16(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return x;
			#else
				return swap16(x);
			#endif
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint32_t le2h32(std::uint32_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapLittleToHostInt32(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return x;
			#else
				return swap32(x);
			#endif
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint64_t le2h64(std::uint64_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapLittleToHostInt64(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return x;
			#else
				return swap64(x);
			#endif
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint16_t h2le16(std::uint16_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapHostToLittleInt16(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return x;
			#else
				return swap16(x);
			#endif
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint32_t h2le32(std::uint32_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapHostToLittleInt32(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return x;
			#else
				return swap32(x);
			#endif
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::uint64_t h2le64(std::uint64_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapHostToLittleInt64(x);
			#elif COCONUT_ARCH_LITTLE_ENDIAN
				return x;
			#else
				return swap64(x);
			#endif
			}
		}
	}
}

#endif /* !COCONUT_RUNTIME_BYTEORDER_HPP */

/* EOF */