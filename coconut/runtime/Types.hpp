//
// Types.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#if defined(COCONUT_HAVE_PRAGMA_ONCE) && COCONUT_HAVE_PRAGMA_ONCE
	#pragma once
#endif

#include <coconut/runtime/detail/core/algorithm.hpp>
#include <coconut/runtime/detail/core/async.hpp>
#include <coconut/runtime/detail/core/byteorder.hpp>
#include <coconut/runtime/detail/core/hash.hpp>
#include <coconut/runtime/detail/core/hexrep.hpp>
#include <coconut/runtime/detail/core/iterators.hpp>
#include <coconut/runtime/detail/core/spinlock.hpp>
#include <coconut/runtime/detail/core/stream.hpp>
#include <coconut/runtime/detail/core/unicode.hpp>

#include <coconut/runtime/detail/traits/bytebuf.hpp>
#include <coconut/runtime/detail/traits/datetime.hpp>
#include <coconut/runtime/detail/traits/formatter.hpp>
#include <coconut/runtime/detail/traits/indexpath.hpp>
#include <coconut/runtime/detail/traits/indexset.hpp>
#include <coconut/runtime/detail/traits/irange.hpp>
#include <coconut/runtime/detail/traits/islice.hpp>
#include <coconut/runtime/detail/traits/locale.hpp>
#include <coconut/runtime/detail/traits/mapbuf.hpp>
#include <coconut/runtime/detail/traits/numeric.hpp>
#include <coconut/runtime/detail/traits/timezone.hpp>
#include <coconut/runtime/detail/traits/upath.hpp>
#include <coconut/runtime/detail/traits/uri.hpp>
#include <coconut/runtime/detail/traits/ustring.hpp>

#include <coconut/runtime/detail/nucleus.hpp>
#include <coconut/runtime/detail/zombie.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_TYPES_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_TYPES_HPP

namespace coconut
{	
	using ::coconut::runtime::Owning;
	using ::coconut::runtime::Any;
	
	using ::coconut::runtime::ClassKind;
	using ::coconut::runtime::ComparisonResult;
	using ::coconut::runtime::NotFound;
	using ::coconut::runtime::MaxFound;
	
	COCONUT_OPT_TYPED(_classkind_opt, std::uint16_t)
	{
		ObjectClass = ::coconut::runtime::classkind_object,
		ProxyClass,
		
		ArrayClass,
		DataClass,
		DateClass,
		DequeClass,
		DictionaryClass,
		DimClass,
		EmptyClass,
		ErrorClass,
		IndexPathClass,
		MutableArrayClass,
		MutableDataClass,
		MutableDictionaryClass,
		MutableOrderedSetClass,
		MutablePathClass,
		MutableRangeClass,
		MutableSetClass,
		MutableStringClass,
		NoneClass,
		NumberClass,
		OrderedSetClass,
		PathClass,
		PointClass,
		QueueClass,
		RangeClass,
		RectClass,
		SetClass,
		SliceClass,
		SortDescriptorClass,
		StackClass,
		StringClass,
		URLClass
	};
	
	COCONUT_CLASSFORWARD_DCL(Array)
	COCONUT_CLASSFORWARD_DCL(Data)
	COCONUT_CLASSFORWARD_DCL(Date)
	COCONUT_CLASSFORWARD_DCL(Deque)
	COCONUT_CLASSFORWARD_DCL(Dictionary)
	COCONUT_CLASSFORWARD_DCL(Dim)
	COCONUT_CLASSFORWARD_DCL(Empty)
	COCONUT_CLASSFORWARD_DCL(Error)
	COCONUT_CLASSFORWARD_DCL(IndexPath)
	COCONUT_CLASSFORWARD_DCL(MutableArray)
	COCONUT_CLASSFORWARD_DCL(MutableData)
	COCONUT_CLASSFORWARD_DCL(MutableDictionary)
	COCONUT_CLASSFORWARD_DCL(MutableOrderedSet)
	COCONUT_CLASSFORWARD_DCL(MutablePath)
	COCONUT_CLASSFORWARD_DCL(MutableRange)
	COCONUT_CLASSFORWARD_DCL(MutableSet)
	COCONUT_CLASSFORWARD_DCL(MutableString)
	COCONUT_CLASSFORWARD_DCL(None)
	COCONUT_CLASSFORWARD_DCL(Number)
	COCONUT_CLASSFORWARD_DCL(OrderedSet)
	COCONUT_CLASSFORWARD_DCL(Path)
	COCONUT_CLASSFORWARD_DCL(Point)
	COCONUT_CLASSFORWARD_DCL(Queue)
	COCONUT_CLASSFORWARD_DCL(Range)
	COCONUT_CLASSFORWARD_DCL(Rect)
	COCONUT_CLASSFORWARD_DCL(Set)
	COCONUT_CLASSFORWARD_DCL(Slice)
	COCONUT_CLASSFORWARD_DCL(SortDescriptor)
	COCONUT_CLASSFORWARD_DCL(Stack)
	COCONUT_CLASSFORWARD_DCL(String)
	COCONUT_CLASSFORWARD_DCL(URL)
	
	COCONUT_OPT_TYPED(ComparisonResultAlias, int)
	{
		OrderedAscending = ::coconut::runtime::cmp_ascending,
		OrderedSame = ::coconut::runtime::cmp_same,
		OrderedDescending = ::coconut::runtime::cmp_descending
	};
		
	COCONUT_OPT(JobPolicyOption)
	{
		JobPolicyAsync = ::coconut::runtime::launch_async,
		JobPolicyDeferred = ::coconut::runtime::launch_deferred,
		JobPolicyAny = ::coconut::runtime::launch_any
	};
	
	COCONUT_OPT(StringEncodingOption)
	{
		StringEncodingAuto = ::coconut::runtime::encoding_auto,
		StringEncodingUniversal = ::coconut::runtime::encoding_universal,
		StringEncodingUnicode = ::coconut::runtime::encoding_unicode,
		
		StringEncodingUTF8 = ::coconut::runtime::encoding_utf8,
		
		StringEncodingUTF16 = ::coconut::runtime::encoding_utf16,
		StringEncodingUTF16BE = ::coconut::runtime::encoding_utf16be,
		StringEncodingUTF16LE = ::coconut::runtime::encoding_utf16le,
		
		StringEncodingUTF32 = ::coconut::runtime::encoding_utf32,
		StringEncodingUTF32BE = ::coconut::runtime::encoding_utf32be,
		StringEncodingUTF32LE = ::coconut::runtime::encoding_utf32le,
		
		StringEncodingUCS2 = ::coconut::runtime::encoding_ucs2,
		StringEncodingUCS2BE = ::coconut::runtime::encoding_ucs2be,
		StringEncodingUCS2LE = ::coconut::runtime::encoding_ucs2le,
		
		StringEncodingUCS4 = ::coconut::runtime::encoding_ucs4,
		StringEncodingUCS4BE = ::coconut::runtime::encoding_ucs4be,
		StringEncodingUCS4LE = ::coconut::runtime::encoding_ucs4le,
		
		StringEncodingSHIFTJIS = ::coconut::runtime::encoding_shiftjis,
		
		StringEncodingISO2022JP = ::coconut::runtime::encoding_iso2022jp,
		StringEncodingISO2022CN = ::coconut::runtime::encoding_iso2022cn,
		StringEncodingISO2022KR = ::coconut::runtime::encoding_iso2022kr,
		
		StringEncodingGB18030 = ::coconut::runtime::encoding_gb18030,
		StringEncodingBIG5 = ::coconut::runtime::encoding_big5,
		
		StringEncodingEUCJP = ::coconut::runtime::encoding_eucjp,
		StringEncodingEUCKR = ::coconut::runtime::encoding_euckr,
		
		StringEncodingISO88591 = ::coconut::runtime::encoding_iso88591,
		StringEncodingISO88592 = ::coconut::runtime::encoding_iso88592,
		StringEncodingISO88595 = ::coconut::runtime::encoding_iso88595,
		StringEncodingISO88596 = ::coconut::runtime::encoding_iso88596,
		StringEncodingISO88597 = ::coconut::runtime::encoding_iso88597,
		StringEncodingISO88598 = ::coconut::runtime::encoding_iso88598,
		StringEncodingISO88598I = ::coconut::runtime::encoding_iso88598i,
		StringEncodingISO88599 = ::coconut::runtime::encoding_iso88599,
		
		StringEncodingWINDOWS1250 = ::coconut::runtime::encoding_windows1250,
		StringEncodingWINDOWS1251 = ::coconut::runtime::encoding_windows1251,
		StringEncodingWINDOWS1252 = ::coconut::runtime::encoding_windows1252,
		StringEncodingWINDOWS1253 = ::coconut::runtime::encoding_windows1253,
		StringEncodingWINDOWS1254 = ::coconut::runtime::encoding_windows1254,
		StringEncodingWINDOWS1255 = ::coconut::runtime::encoding_windows1255,
		StringEncodingWINDOWS1256 = ::coconut::runtime::encoding_windows1256,
		
		StringEncodingKOI8R = ::coconut::runtime::encoding_koi8r,
		
		StringEncodingIBM420 = ::coconut::runtime::encoding_ibm420,
		StringEncodingIBM420LTR = ::coconut::runtime::encoding_ibm420ltr,
		StringEncodingIBM420RTL = ::coconut::runtime::encoding_ibm420rtl,
		
		StringEncodingIBM424 = ::coconut::runtime::encoding_ibm424,
		StringEncodingIBM424LTR = ::coconut::runtime::encoding_ibm424ltr,
		StringEncodingIBM424RTL = ::coconut::runtime::encoding_ibm424rtl
	};
	
	COCONUT_OPT(StringSearchOptions)
	{
		StringSearchLiteral = ::coconut::runtime::search_literal,
		StringSearchWidthInsensitive = ::coconut::runtime::search_nowidth,
		StringSearchCaseInsensitive = ::coconut::runtime::search_insensitive,
		StringSearchDiacriticInsensitive = ::coconut::runtime::search_diacritic,
		StringSearchBackwards = ::coconut::runtime::search_backwards,
		StringSearchForcedOrdering = ::coconut::runtime::search_forceorder,
		StringSearchAnchored = ::coconut::runtime::search_anchored,
		StringSearchNumeric = ::coconut::runtime::search_numeric
	};
		
	COCONUT_OPT(ChunkSplitOption)
	{
		ChunkSplitNone = ::coconut::runtime::chunksplit_none,
		ChunkSplit64CRLF = ::coconut::runtime::chunksplit_64crlf,
		ChunkSplit64LF = ::coconut::runtime::chunksplit_64lf,
		ChunkSplit76CRLF = ::coconut::runtime::chunksplit_76crlf,
		ChunkSplit76LF = ::coconut::runtime::chunksplit_76lf
	};
	
	COCONUT_OPT_TYPED(NumberType, std::uint16_t)
	{
		NumberZero = ::coconut::runtime::numeric_zero,
		NumberFloat = ::coconut::runtime::numeric_float,
		NumberDouble = ::coconut::runtime::numeric_double,
		NumberLongDouble = ::coconut::runtime::numeric_long_double,
		NumberBool = ::coconut::runtime::numeric_bool,
		NumberChar = ::coconut::runtime::numeric_char,
		NumberShort = ::coconut::runtime::numeric_short,
		NumberInt = ::coconut::runtime::numeric_int,
		NumberLong = ::coconut::runtime::numeric_long,
		NumberLongLong = ::coconut::runtime::numeric_longlong,
		NumberUnsignedChar = ::coconut::runtime::numeric_unsigned_char,
		NumberUnsignedShort = ::coconut::runtime::numeric_unsigned_short,
		NumberUnsignedInt = ::coconut::runtime::numeric_unsigned_int,
		NumberUnsignedLong = ::coconut::runtime::numeric_unsigned_long,
		NumberUnsignedLongLong = ::coconut::runtime::numeric_unsigned_longlong
	};
	
	COCONUT_OPT(DataPackingOption)
	{
		DataPackingBigEndian = ::coconut::runtime::packing_bigendian,
		DataPackingLittleEndian = ::coconut::runtime::packing_littleendian
	};
		
	COCONUT_OPT(DataUnpackingOption)
	{
		DataUnpackingBigEndian = ::coconut::runtime::unpacking_bigendian,
		DataUnpackingLittleEndian = ::coconut::runtime::unpacking_littleendian
	};
	
	COCONUT_OPT(ByteOrderType)
	{
		ByteOrderUnknown = 0ULL,
		ByteOrderBigEndian,
		ByteOrderLittleEndian
	};
	
	using SwappedFloat = ::coconut::runtime::byteorder::fswp_t;
	using SwappedDouble = ::coconut::runtime::byteorder::dswp_t;
	
	COCONUT_OPT(DirectorySeparatorOption)
	{
		DirectorySeparatorAuto = ::coconut::runtime::dirsep_auto,
		DirectorySeparatorBackslash = ::coconut::runtime::dirsep_slack,
		DirectorySeparatorSlash = ::coconut::runtime::dirsep_whack,
	};
	
	COCONUT_OPT(CopyOption)
	{
		CopyNone = 0ULL,
		CopyMutable,
		CopyImmutable,
		CopyKind
	};
	
	COCONUT_OPT(IterationOption)
	{
		IterationAscending = 0ULL,
		IterationDescending,
		IterationAsyncAscending,
		IterationAsyncDescending,
	};
	
	COCONUT_OPT(EnumerationOptions)
	{
		EnumerationDefault = 0ULL,
		EnumerationConcurrent = (1ULL << 2),
		EnumerationReverse = (1ULL << 4),
	};
	
	COCONUT_OPT(SortOptions)
	{
		SortDefault = 0ULL,
		SortConcurrent = (1ULL << 3),
		SortStable = (1ULL << 5),
	};
	
	COCONUT_OPT(SerializationReadOption)
	{
		SerializationReadImmutable = 0ULL,
		SerializationReadMutableContainers,
		SerializationReadMutableContainersAndLeaves
	};
	
	COCONUT_OPT(SerializationFormatOption)
	{
		SerializationFormatJSON = 0ULL,
		SerializationFormatExtendedJSON,
		SerializationFormatXMLPlist,
		SerializationFormatExtendedXMLPlist
	};
	
	COCONUT_OPT(TimeUnitOption)
	{
		TimeUnitPlainSeconds = ::coconut::runtime::timeunit_plainseconds,
		TimeUnitDoubleSeconds = ::coconut::runtime::timeunit_doubleseconds,
		TimeUnitMilliSeconds = ::coconut::runtime::timeunit_milliseconds,
		TimeUnitMicroSeconds = ::coconut::runtime::timeunit_microseconds,
		TimeUnitNanoSeconds = ::coconut::runtime::timeunit_nanoseconds
	};
	
	COCONUT_OPT(TimeReferenceOption)
	{
		TimeReferenceSinceCurrentTime = ::coconut::runtime::timeref_since_now,
		TimeReferenceSinceReferenceDate = ::coconut::runtime::timeref_since_ref,
		TimeReferenceSinceJanuary1970 = ::coconut::runtime::timeref_since_1970
	};
	
	COCONUT_OPT(TimestampOption)
	{
		TimestampSinceReferenceDate = ::coconut::runtime::timeref_since_ref,
		TimestampSinceJanuary1970 = ::coconut::runtime::timeref_since_1970
	};
	
	typedef double TimeInterval;
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_TYPES_HPP */

/* EOF */