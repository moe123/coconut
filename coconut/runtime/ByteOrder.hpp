//
// ByteOrder.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Types.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_BYTEORDER_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_BYTEORDER_HPP

namespace coconut
{
	COCONUT_ALWAYS_INLINE
	ByteOrderType HostByteOrder(void)
	{
	#if COCONUT_ARCH_BIG_ENDIAN
		return ByteOrderBigEndian;
	#elif COCONUT_ARCH_LITTLE_ENDIAN
		return ByteOrderLittleEndian;
	#else
		return ByteOrderUnknown;
	#endif
	}
	
	COCONUT_ALWAYS_INLINE
	void ReadBigInt16(const std::uint8_t (&r)[2], std::uint16_t & out)
	{ runtime::byteorder::r16be(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadBigInt16(const std::uint8_t (&r)[2], std::int16_t & out)
	{ runtime::byteorder::rs16be(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadBigInt32(const std::uint8_t (&r)[4], std::uint32_t & out)
	{ return runtime::byteorder::r32be(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadBigInt32(const std::uint8_t (&r)[4], std::int32_t & out)
	{ return runtime::byteorder::rs32be(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadBigInt64(const std::uint8_t (&r)[8], std::uint64_t & out)
	{ return runtime::byteorder::r64be(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadBigInt64(const std::uint8_t (&r)[8], std::int64_t & out)
	{ return runtime::byteorder::rs64be(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void WriteBigInt16(const std::uint16_t & in, std::uint8_t (&w)[2])
	{ runtime::byteorder::w16be(in, w); }

	COCONUT_ALWAYS_INLINE
	void WriteBigInt16(const std::int16_t & in, std::uint8_t (&w)[2])
	{ runtime::byteorder::w16be(in, w); }
	
	COCONUT_ALWAYS_INLINE
	void WriteBigInt32(const std::uint32_t & in, std::uint8_t (&w)[4])
	{ runtime::byteorder::w32be(in, w); }
	
	COCONUT_ALWAYS_INLINE
	void WriteBigInt32(const std::int32_t & in, std::uint8_t (&w)[4])
	{ runtime::byteorder::w32be(in, w); }
	
	COCONUT_ALWAYS_INLINE
	void WriteBigInt64(const std::uint64_t & in, std::uint8_t (&w)[8])
	{ runtime::byteorder::w64be(in, w); }
	
	COCONUT_ALWAYS_INLINE
	void WriteBigInt64(const std::int64_t & in, std::uint8_t (&w)[8])
	{ runtime::byteorder::w64be(in, w); }
	
	COCONUT_ALWAYS_INLINE
	void ReadLittleInt16(const std::uint8_t (&r)[2], std::uint16_t & out)
	{ runtime::byteorder::r16le(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadLittleInt16(const std::uint8_t (&r)[2], std::int16_t & out)
	{ runtime::byteorder::rs16le(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadLittleInt32(const std::uint8_t (&r)[4], std::uint32_t & out)
	{ runtime::byteorder::r32le(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadLittleInt32(const std::uint8_t (&r)[4], std::int32_t & out)
	{ runtime::byteorder::rs32le(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadLittleInt64(const std::uint8_t (&r)[8], std::uint64_t & out)
	{ runtime::byteorder::r64le(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void ReadLittleInt64(const std::uint8_t (&r)[8], std::int64_t & out)
	{ runtime::byteorder::rs64le(r, out); }
	
	COCONUT_ALWAYS_INLINE
	void WriteLittleInt16(const std::uint16_t & in, std::uint8_t (&w)[2])
	{ runtime::byteorder::w16le(in, w); }

	COCONUT_ALWAYS_INLINE
	void WriteLittleInt16(const std::int16_t & in, std::uint8_t (&w)[2])
	{ runtime::byteorder::w16le(in, w); }
	
	COCONUT_ALWAYS_INLINE
	void WriteLittleInt32(const std::uint32_t & in, std::uint8_t (&w)[4])
	{ runtime::byteorder::w32le(in, w); }

	COCONUT_ALWAYS_INLINE
	void WriteLittleInt32(const std::int32_t & in, std::uint8_t (&w)[4])
	{ runtime::byteorder::w32le(in, w); }
	
	COCONUT_ALWAYS_INLINE
	void WriteLittleInt64(const std::uint64_t & in, std::uint8_t (&w)[8])
	{ runtime::byteorder::w64le(in, w); }
	
	COCONUT_ALWAYS_INLINE
	void WriteLittleInt64(const std::int64_t & in, std::uint8_t (&w)[8])
	{ runtime::byteorder::w64le(in, w); }
	
	COCONUT_ALWAYS_INLINE
	std::uint16_t SwapInt16(std::uint16_t & x)
	{ return runtime::byteorder::swpc16(x); }

	COCONUT_ALWAYS_INLINE
	std::int16_t SwapSInt16(std::int16_t & x)
	{ return runtime::byteorder::swpcs16(x); }
	
	COCONUT_ALWAYS_INLINE
	std::uint32_t SwapInt32(std::uint32_t & x)
	{ return runtime::byteorder::swpc32(x); }

	COCONUT_ALWAYS_INLINE
	std::int32_t SwapSInt32(std::int32_t & x)
	{ return runtime::byteorder::swpcs32(x); }
	
	COCONUT_ALWAYS_INLINE
	std::uint64_t SwapInt64(std::uint64_t & x)
	{ return runtime::byteorder::swpc64(x); }
	
	COCONUT_ALWAYS_INLINE
	std::int64_t SwapSInt64(std::int64_t & x)
	{ return runtime::byteorder::swpcs64(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned short SwapShort(unsigned short x)
	{ return runtime::byteorder::swpc16(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned int SwapInt(unsigned int x)
	{ return runtime::byteorder::swpc32(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned long SwapLong(unsigned long x)
	{
	#if __LP64__
		return runtime::byteorder::swpc64(x);
	#else
		return runtime::byteorder::swpc32(x);
	#endif
	}
	
	COCONUT_ALWAYS_INLINE
	unsigned long long SwapLongLong(unsigned long long x)
	{ return runtime::byteorder::swpc64(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned short SwapBigShortToHost(unsigned short x)
	{ return runtime::byteorder::be2h16(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned int SwapBigIntToHost(unsigned int x)
	{ return runtime::byteorder::be2h32(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned long SwapBigLongToHost(unsigned long x)
	{
	#if __LP64__
		return runtime::byteorder::be2h64(x);
	#else
		return runtime::byteorder::be2h32(x);
	#endif
	}
	
	COCONUT_ALWAYS_INLINE
	unsigned long long SwapBigLongLongToHost(unsigned long long x)
	{ return runtime::byteorder::be2h64(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned short SwapHostShortToBig(unsigned short x)
	{ return runtime::byteorder::h2be16(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned int SwapHostIntToBig(unsigned int x)
	{ return runtime::byteorder::h2be32(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned long SwapHostLongToBig(unsigned long x)
	{
	#if __LP64__
		return runtime::byteorder::h2be64(x);
	#else
		return runtime::byteorder::h2be32(x);
	#endif
	}
	
	COCONUT_ALWAYS_INLINE
	unsigned long long SwapHostLongLongToBig(unsigned long long x)
	{ return runtime::byteorder::h2be64(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned short SwapLittleShortToHost(unsigned short x)
	{ return runtime::byteorder::le2h16(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned int SwapLittleIntToHost(unsigned int x)
	{ return runtime::byteorder::le2h32(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned long SwapLittleLongToHost(unsigned long x) {
	#if __LP64__
		return runtime::byteorder::le2h64(x);
	#else
		return runtime::byteorder::le2h32(x);
	#endif
	}
	
	COCONUT_ALWAYS_INLINE
	unsigned long long SwapLittleLongLongToHost(unsigned long long x)
	{ return runtime::byteorder::le2h64(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned short SwapHostShortToLittle(unsigned short x)
	{ return runtime::byteorder::h2le16(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned int SwapHostIntToLittle(unsigned int x)
	{ return runtime::byteorder::h2le32(x); }
	
	COCONUT_ALWAYS_INLINE
	unsigned long SwapHostLongToLittle(unsigned long x)
	{
	#if __LP64__
		return runtime::byteorder::h2le64(x);
	#else
		return runtime::byteorder::h2le32(x);
	#endif
	}
	
	COCONUT_ALWAYS_INLINE
	unsigned long long SwapHostLongLongToLittle(unsigned long long x)
	{ return runtime::byteorder::h2le64(x); }
	
	COCONUT_ALWAYS_INLINE
	SwappedFloat ConvertHostFloatToSwapped(float x)
	{
		union nv { float n; SwappedFloat v; };
		return (weak_cast<union nv *>(&x))->v;
	}
	
	COCONUT_ALWAYS_INLINE
	float ConvertSwappedFloatToHost(SwappedFloat x)
	{
		union nv { float n; SwappedFloat v; };
		return (weak_cast<union nv *>(&x))->n;
	}
	
	COCONUT_ALWAYS_INLINE
	SwappedDouble ConvertHostDoubleToSwapped(double x)
	{
		union nv { double n; SwappedDouble v; };
		return (weak_cast<union nv *>(&x))->v;
	}
	
	COCONUT_ALWAYS_INLINE
	double ConvertSwappedDoubleToHost(SwappedDouble x)
	{
		union nv { double n; SwappedDouble v; };
		return (weak_cast<union nv *>(&x))->n;
	}
	
	COCONUT_ALWAYS_INLINE
	SwappedFloat SwapFloat(SwappedFloat x)
	{ x.v = SwapInt(x.v); return x; }
	
	COCONUT_ALWAYS_INLINE
	SwappedDouble SwapDouble(SwappedDouble x)
	{ x.v = SwapLongLong(x.v); return x; }

	COCONUT_ALWAYS_INLINE	
	float SwapBigFloatToHost(SwappedFloat x)
	{
	#if COCONUT_ARCH_BIG_ENDIAN
		return ConvertSwappedFloatToHost(x);
	#elif COCONUT_ARCH_LITTLE_ENDIAN
		return ConvertSwappedFloatToHost(SwapFloat(x));
	#else
		return 0;
	#endif
	}

	COCONUT_ALWAYS_INLINE	
	double SwapBigDoubleToHost(SwappedDouble x)
	{
	#if COCONUT_ARCH_BIG_ENDIAN
		return ConvertSwappedDoubleToHost(x);
	#elif COCONUT_ARCH_LITTLE_ENDIAN
		return ConvertSwappedDoubleToHost(SwapDouble(x));
	#else
		return 0;
	#endif
	}

	COCONUT_ALWAYS_INLINE
	SwappedFloat SwapHostFloatToBig(float x)
	{
	#if COCONUT_ARCH_BIG_ENDIAN
		return ConvertHostFloatToSwapped(x);
	#elif COCONUT_ARCH_LITTLE_ENDIAN
		return SwapFloat(ConvertHostFloatToSwapped(x));
	#else
		return { 0 };
	#endif
	}

	COCONUT_ALWAYS_INLINE	
	SwappedDouble SwapHostDoubleToBig(double x)
	{
	#if COCONUT_ARCH_BIG_ENDIAN
		return ConvertHostDoubleToSwapped(x);
	#elif COCONUT_ARCH_LITTLE_ENDIAN
		return SwapDouble(ConvertHostDoubleToSwapped(x));
	#else
		return { 0 };
	#endif
	}

	COCONUT_ALWAYS_INLINE
	float SwapLittleFloatToHost(SwappedFloat x)
	{
	#if COCONUT_ARCH_BIG_ENDIAN
		return ConvertSwappedFloatToHost(SwapFloat(x));
	#elif COCONUT_ARCH_LITTLE_ENDIAN
		return ConvertSwappedFloatToHost(x);
	#else
		return 0;
	#endif
	}

	COCONUT_ALWAYS_INLINE	
	double SwapLittleDoubleToHost(SwappedDouble x)
	{
	#if COCONUT_ARCH_BIG_ENDIAN
		return ConvertSwappedDoubleToHost(SwapDouble(x));
	#elif COCONUT_ARCH_LITTLE_ENDIAN
		return ConvertSwappedDoubleToHost(x);
	#else
		return 0;
	#endif
	}

	COCONUT_ALWAYS_INLINE
	SwappedFloat SwapHostFloatToLittle(float x)
	{
	#if COCONUT_ARCH_BIG_ENDIAN
		return SwapFloat(ConvertHostFloatToSwapped(x));
	#elif COCONUT_ARCH_LITTLE_ENDIAN
		return ConvertHostFloatToSwapped(x);
	#else
		return { 0 };
	#endif
	}

	COCONUT_ALWAYS_INLINE	
	SwappedDouble SwapHostDoubleToLittle(double x)
	{
	#if COCONUT_ARCH_BIG_ENDIAN
		return SwapDouble(ConvertHostDoubleToSwapped(x));
	#elif COCONUT_ARCH_LITTLE_ENDIAN
		return ConvertHostDoubleToSwapped(x);
	#else
		return { 0 };
	#endif
	}
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_BYTEORDER_HPP */

/* EOF */