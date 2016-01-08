//
// byteorder.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
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
			/**
				@assuming modern archs and compilers
				(e.g being smart with arch alignment):

				char        : 1 byte
				short       : 2 bytes
				int         : 4 bytes
				long        : 4 bytes or 8 bytes
				long long   : 8 bytes
				float       : 4 bytes
				double      : 8 bytes
				long double : 8 bytes
			 **/
			
			typedef struct { std::uint32_t v; } fswp_t;
			typedef struct { std::uint64_t v; } dswp_t;

			template <typename T>
			inline void swpi(T & x)
			{ char & raw = reinterpret_cast<char &>(x); std::reverse(&raw, &raw + sizeof(T)); }
			
			template <typename T>
			inline T swpc(T x)
			{ swpi(x); return x; }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint16_t swpc16(const volatile std::uint16_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapInt16(x);
			#elif defined(__INTEL_COMPILER)
				return _bswap16(x);
			#elif defined(__GNUC__) || defined(__clang__)
				return __builtin_bswap16(x);
			#elif defined(_MSC_VER)
				return _byteswap_ushort(x);
			#else
				std::uint16_t v;
				v = (std::uint16_t)(((x << 8) & 0xFF00) | ((x >> 8) & 0xFF));
				return v;
			#endif
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint32_t swpc32(const volatile std::uint32_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapInt32(x);
			#elif defined(__GNUC__) || defined(__clang__)
				return __builtin_bswap32(x);
			#elif defined(_MSC_VER)
				return _byteswap_ulong(x);
			#else
				std::uint32_t v;
				v = ((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | ((x >> 24) & 0xFF);
				return v;
			#endif
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint64_t swpc64(const volatile std::uint64_t x)
			{
			#if defined(__APPLE__) && !defined(__clang__)
				return OSSwapInt64(x);
			#elif defined(__GNUC__) || defined(__clang__)
				return __builtin_bswap64(x);
			#elif defined(_MSC_VER)
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			float swpf(float x)
			{
				std::uint32_t * raw = reinterpret_cast<std::uint32_t *>(&x);
				swpc32(*raw);
				return *reinterpret_cast<float *>(raw);
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			double swpd(double x)
			{
				std::uint64_t * raw = reinterpret_cast<std::uint64_t *>(&x);
				swpc64(*raw);
				return *reinterpret_cast<double *>(raw);
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint16_t * swpc16a(std::uint16_t * ar, std::size_t start, std::size_t sz)
			{
				for (std::size_t i = start ; i < sz - start ; i++) {
					std::uint16_t x = ar[i];
					ar[i] = swpc16(x);
				}
				return ar;
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint16_t * swpc16a(std::uint16_t * ar, std::size_t sz)
			{ return swpc16a(ar, 0, sz); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint32_t * swpc32a(std::uint32_t * ar, std::size_t start, std::size_t sz)
			{
				for (std::size_t i = start ; i < sz - start ; i++) {
					std::uint32_t x = ar[i];
					ar[i] = swpc32(x);
				}
				return ar;
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint32_t * swpc32a(std::uint32_t * ar, std::size_t sz)
			{ return swpc32a(ar, 0, sz); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint64_t * swpc64a(std::uint64_t * ar, std::size_t start, std::size_t sz)
			{
				for (std::size_t i = start ; i < sz - start ; i++) {
					std::uint64_t x = ar[i];
					ar[i] = swpc64(x);
				}
				return ar;
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint64_t * swpc64a(std::uint64_t * ar, std::size_t sz)
			{ return swpc64a(ar, 0, sz); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			float * swpfa(float * ar, std::size_t start, std::size_t sz)
			{
				for (std::size_t i = start ; i < sz - start ; i++) {
					float x = ar[i];
					ar[i] = swpf(x);
				}
				return ar;
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			float * swpfa(float * ar, std::size_t sz)
			{ return swpfa(ar, 0, sz); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			double * swpda(double * ar, std::size_t start, std::size_t sz)
			{
				for (std::size_t i = start ; i < sz - start ; i++) {
					double x = ar[i];
					ar[i] = swpd(x);
				}
				return ar;
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			double * swpda(double * ar, std::size_t sz)
			{ return swpda(ar, 0, sz); }

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint16_t r16be_v1(const std::uint8_t (&r)[2])
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[0]) << 8;
				x |= r[1];
				return x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r16be(const std::uint8_t (&r)[2], std::uint16_t & out)
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[0]) << 8;
				x |= r[1];
				out = x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r16be(const std::uint8_t (&r)[2], std::int16_t & out)
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[0]) << 8;
				x |= r[1];
				out = x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint32_t r32be_v1(const std::uint8_t (&r)[4])
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[0]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 8;
				x |= r[3];
				return x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r32be(const std::uint8_t (&r)[4], std::uint32_t & out)
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[0]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 8;
				x |= r[3];
				out = x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r32be(const std::uint8_t (&r)[4], std::int32_t & out)
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[0]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 8;
				x |= r[3];
				out = x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint64_t r64be_v1(const std::uint8_t (&r)[8])
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
				return x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r64be(const std::uint8_t (&r)[8], std::int64_t & out)
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
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint16_t r16le_v1(const std::uint8_t (&r)[2])
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[1]) << 8;
				x |= r[0];
				return x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r16le(const std::uint8_t (&r)[2], std::uint16_t & out)
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[1]) << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r16le(const std::uint8_t (&r)[2], std::int16_t & out)
			{
				std::uint16_t x = 0;
				x |= unsafe_cast<std::uint16_t>(r[1]) << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint32_t r32le_v1(const std::uint8_t (&r)[4])
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[3]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 8;
				x |= r[0];
				return x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r32le(const std::uint8_t (&r)[4], std::uint32_t & out)
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[3]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r32le(const std::uint8_t (&r)[4], std::int32_t & out)
			{
				std::uint32_t x = 0;
				x |= unsafe_cast<std::uint32_t>(r[3]) << 24;
				x |= unsafe_cast<std::uint32_t>(r[2]) << 16;
				x |= unsafe_cast<std::uint32_t>(r[1]) << 8;
				x |= r[0];
				out = x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			std::uint64_t r64le_v1(const std::uint8_t (&r)[8])
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
				return x;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void r64le(const std::uint8_t (&r)[8], std::int64_t & out)
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
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w16be(std::uint16_t in, std::uint8_t (&w)[2])
			{
				w[0] = ((in >> 8) & 0xFF);
				w[1] = (in & 0xFF);
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w16be(std::int16_t in, std::uint8_t (&w)[2])
			{ w16be(unsafe_cast<std::uint16_t>(in), w); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w32be(std::uint32_t in, std::uint8_t (&w)[4])
			{
				w[0] = ((in & 0xFF000000UL) >> 24);
				w[1] = ((in & 0x00FF0000UL) >> 16);
				w[2] = ((in & 0x0000FF00UL) >> 8);
				w[3] = ((in & 0x000000FFUL));
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w32be(std::int32_t in, std::uint8_t (&w)[4])
			{ w32be(unsafe_cast<std::uint32_t>(in), w); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w64be(std::int64_t in, std::uint8_t (&w)[8])
			{ w64be(unsafe_cast<std::uint64_t>(in), w); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void wfbe(float in, std::uint8_t (&w)[4])
			{ w32be(unsafe_cast<std::int32_t>(in), w); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void wdbe(double in, std::uint8_t (&w)[8])
			{ w64be(unsafe_cast<std::int64_t>(in), w); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w16le(std::uint16_t & in, std::uint8_t (&w)[2])
			{
				w[0] = (in & 0xFF);
				w[1] = ((in >> 8) & 0xFF);
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w16le(std::int16_t in, std::uint8_t (&w)[2])
			{ w16le(unsafe_cast<std::uint16_t>(in), w); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w32le(std::uint32_t in, std::uint8_t (&w)[4])
			{
				w[0] = ((in & 0x000000FFUL));
				w[1] = ((in & 0x0000FF00UL) >> 8);
				w[2] = ((in & 0x00FF0000UL) >> 16);
				w[3] = ((in & 0xFF000000UL) >> 24);
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w32le(std::int32_t in, std::uint8_t (&w)[4])
			{ w32le(unsafe_cast<std::uint32_t>(in), w); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void w64le(std::int64_t in, std::uint8_t (&w)[8])
			{ w64le(unsafe_cast<std::uint64_t>(in), w); }

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void wfle(float in, std::uint8_t (&w)[4])
			{ w32le(static_cast<std::int32_t>(in), w); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			void wdle(double in, std::uint8_t (&w)[8])
			{ w64le(static_cast<std::int64_t>(in), w); }
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
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

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			float be2hf(float x)
			{
			#if COCONUT_FPU_LITTLE_ENDIAN
				return swpf(x);
			#else
				return x;
			#endif
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			double be2hd(double x)
			{
			#if COCONUT_FPU_LITTLE_ENDIAN
				return swpd(x);
			#else
				return x;
			#endif
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			float h2bef(float x)
			{
			#if COCONUT_FPU_LITTLE_ENDIAN
				return swpf(x);
			#else
				return x;
			#endif
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			double h2bed(double x)
			{
			#if COCONUT_FPU_LITTLE_ENDIAN
				return swpd(x);
			#else
				return x;
			#endif
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			float le2hf(float x)
			{
			#if COCONUT_FPU_LITTLE_ENDIAN
				return x;
			#else
				return swpf(x);
			#endif
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			double le2hd(double x)
			{
			#if COCONUT_FPU_LITTLE_ENDIAN
				return x;
			#else
				return swpd(x);
			#endif
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			float h2lef(float x)
			{
			#if COCONUT_FPU_LITTLE_ENDIAN
				return x;
			#else
				return swpf(x);
			#endif
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			double h2led(double x)
			{
			#if COCONUT_FPU_LITTLE_ENDIAN
				return x;
			#else
				return swpd(x);
			#endif
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			fswp_t h2fswp(float x)
			{
				union swap { float v; fswp_t sv; } result;
				result.v = x;
			#if COCONUT_FPU_LITTLE_ENDIAN
				result.sv.v = swpc32(result.sv.v);
			#endif
				return result.sv;
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			float fswp2h(fswp_t x)
			{
				union swap { float v; fswp_t sv; } result;
				result.sv = x;
			#if COCONUT_FPU_LITTLE_ENDIAN
				result.sv.v = swpc32(result.sv.v);
			#endif
				return result.v;
			}
			
			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			dswp_t h2dswp(double x)
			{
				union swap { double v; dswp_t sv; } result;
				result.v = x;
			#if COCONUT_FPU_LITTLE_ENDIAN
				result.sv.v = swpc64(result.sv.v);
			#endif
				return result.sv;
			}

			COCONUT_PROTECTED COCONUT_ALWAYS_INLINE
			double dswp2h(dswp_t x)
			{
				union swap { double v; dswp_t sv; } result;
				result.sv = x;
			#if COCONUT_FPU_LITTLE_ENDIAN
				result.sv.v = swpc64(result.sv.v);
			#endif
				return result.v;
			}
		}
	}
}

#endif /* !COCONUT_RUNTIME_BYTEORDER_HPP */

/* EOF */