//
// Types.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/algorithm.hpp>
#include <coconut/runtime/detail/core/async.hpp>
#include <coconut/runtime/detail/core/byteorder.hpp>
#include <coconut/runtime/detail/core/hash.hpp>
#include <coconut/runtime/detail/core/iterator.hpp>
#include <coconut/runtime/detail/core/spinlock.hpp>
#include <coconut/runtime/detail/core/stream.hpp>
#include <coconut/runtime/detail/core/unicode.hpp>

#include <coconut/runtime/detail/proxy/bytebuf.hpp>
#include <coconut/runtime/detail/proxy/datetime.hpp>
#include <coconut/runtime/detail/proxy/formatter.hpp>
#include <coconut/runtime/detail/proxy/indexpath.hpp>
#include <coconut/runtime/detail/proxy/indexset.hpp>
#include <coconut/runtime/detail/proxy/irange.hpp>
#include <coconut/runtime/detail/proxy/locale.hpp>
#include <coconut/runtime/detail/proxy/mapbuf.hpp>
#include <coconut/runtime/detail/proxy/numeric.hpp>
#include <coconut/runtime/detail/proxy/timezone.hpp>
#include <coconut/runtime/detail/proxy/upath.hpp>
#include <coconut/runtime/detail/proxy/uri.hpp>
#include <coconut/runtime/detail/proxy/ustring.hpp>

#include <coconut/runtime/detail/nucleus.hpp>
#include <coconut/runtime/detail/zombie.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_TYPES_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_TYPES_HPP

namespace coconut
{
	using runtime::kind_ptr;
	using runtime::const_kind_ptr;
	
	using runtime::kind_raw_ptr;
	using runtime::const_kind_raw_ptr;
	
	using runtime::kind_ref;
	using runtime::const_kind_ref;
	
	using runtime::ClassKind;
	using runtime::ComparisonResult;
	using runtime::NotFound;
	using runtime::MaxFound;
	
	enum
	{
		ObjectClass = runtime::classkind_object,
		ProxyClass,
		
		ArrayClass,
		DataClass,
		DateClass,
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
		SortDescriptorClass,
		StackClass,
		StringClass,
		URLClass
	};
	
	COCONUT_DCL_PTR(Array)
	COCONUT_DCL_PTR(Data)
	COCONUT_DCL_PTR(Date)
	COCONUT_DCL_PTR(Dictionary)
	COCONUT_DCL_PTR(Dim)
	COCONUT_DCL_PTR(Empty)
	COCONUT_DCL_PTR(Error)
	COCONUT_DCL_PTR(IndexPath)
	COCONUT_DCL_PTR(MutableArray)
	COCONUT_DCL_PTR(MutableData)
	COCONUT_DCL_PTR(MutableDictionary)
	COCONUT_DCL_PTR(MutableOrderedSet)
	COCONUT_DCL_PTR(MutablePath)
	COCONUT_DCL_PTR(MutableRange)
	COCONUT_DCL_PTR(MutableSet)
	COCONUT_DCL_PTR(MutableString)
	COCONUT_DCL_PTR(None)
	COCONUT_DCL_PTR(Number)
	COCONUT_DCL_PTR(OrderedSet)
	COCONUT_DCL_PTR(Path)
	COCONUT_DCL_PTR(Point)
	COCONUT_DCL_PTR(Queue)
	COCONUT_DCL_PTR(Range)
	COCONUT_DCL_PTR(Rect)
	COCONUT_DCL_PTR(Set)
	COCONUT_DCL_PTR(SortDescriptor)
	COCONUT_DCL_PTR(Stack)
	COCONUT_DCL_PTR(String)
	COCONUT_DCL_PTR(URL)
	
	COCONUT_OPT(OrderedOption)
	{
		OrderedAscending = runtime::cmp_ascending,
		OrderedSame = runtime::cmp_same,
		OrderedDescending = runtime::cmp_descending
	};
	
	COCONUT_OPT(JobPolicyOption)
	{
		JobPolicyAsync = runtime::launch_async,
		JobPolicyDeferred = runtime::launch_deferred,
		JobPolicyAny = runtime::launch_any
	};
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(JobPolicyOption option, FuncT && func, ArgsT &&... args)
		-> decltype(runtime::async::exec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...))
	{ return runtime::async::exec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(FuncT && func, ArgsT &&... args)
		-> decltype(runtime::async::exec(JobPolicyAsync, std::forward<FuncT>(func), std::forward<ArgsT>(args)...))
	{ return runtime::async::exec(JobPolicyAsync, std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
		
	template <typename FuncT, typename... ArgsT>
	inline void JobDetach(FuncT && func, ArgsT &&... args)
	{ runtime::async::detach(std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename RetT, typename ErrT>
	struct OptionalReturn
	{
		operator bool () const { return valid; }

		RetT success;
		ErrT error;
		bool valid;
	};
		
	COCONUT_OPT(StringEncodingOption)
	{
		StringEncodingAuto = runtime::encoding_auto,
		StringEncodingUniversal = runtime::encoding_universal,
		StringEncodingUnicode = runtime::encoding_unicode,
		
		StringEncodingUTF8 = runtime::encoding_utf8,
		
		StringEncodingUTF16 = runtime::encoding_utf16,
		StringEncodingUTF16BE = runtime::encoding_utf16be,
		StringEncodingUTF16LE = runtime::encoding_utf16le,
		
		StringEncodingUTF32 = runtime::encoding_utf32,
		StringEncodingUTF32BE = runtime::encoding_utf32be,
		StringEncodingUTF32LE = runtime::encoding_utf32le,
		
		StringEncodingUCS2 = runtime::encoding_ucs2,
		StringEncodingUCS2BE = runtime::encoding_ucs2be,
		StringEncodingUCS2LE = runtime::encoding_ucs2le,
		
		StringEncodingUCS4 = runtime::encoding_ucs4,
		StringEncodingUCS4BE = runtime::encoding_ucs4be,
		StringEncodingUCS4LE = runtime::encoding_ucs4le,
		
		StringEncodingSHIFTJIS = runtime::encoding_shiftjis,
		
		StringEncodingISO2022JP = runtime::encoding_iso2022jp,
		StringEncodingISO2022CN = runtime::encoding_iso2022cn,
		StringEncodingISO2022KR = runtime::encoding_iso2022kr,
		
		StringEncodingGB18030 = runtime::encoding_gb18030,
		StringEncodingBIG5 = runtime::encoding_big5,
		
		StringEncodingEUCJP = runtime::encoding_eucjp,
		StringEncodingEUCKR = runtime::encoding_euckr,
		
		StringEncodingISO88591 = runtime::encoding_iso88591,
		StringEncodingISO88592 = runtime::encoding_iso88592,
		StringEncodingISO88595 = runtime::encoding_iso88595,
		StringEncodingISO88596 = runtime::encoding_iso88596,
		StringEncodingISO88597 = runtime::encoding_iso88597,
		StringEncodingISO88598 = runtime::encoding_iso88598,
		StringEncodingISO88598I = runtime::encoding_iso88598i,
		StringEncodingISO88599 = runtime::encoding_iso88599,
		
		StringEncodingWINDOWS1250 = runtime::encoding_windows1250,
		StringEncodingWINDOWS1251 = runtime::encoding_windows1251,
		StringEncodingWINDOWS1252 = runtime::encoding_windows1252,
		StringEncodingWINDOWS1253 = runtime::encoding_windows1253,
		StringEncodingWINDOWS1254 = runtime::encoding_windows1254,
		StringEncodingWINDOWS1255 = runtime::encoding_windows1255,
		StringEncodingWINDOWS1256 = runtime::encoding_windows1256,
		
		StringEncodingKOI8R = runtime::encoding_koi8r,
		
		StringEncodingIBM420 = runtime::encoding_ibm420,
		StringEncodingIBM420LTR = runtime::encoding_ibm420ltr,
		StringEncodingIBM420RTL = runtime::encoding_ibm420rtl,
		
		StringEncodingIBM424 = runtime::encoding_ibm424,
		StringEncodingIBM424LTR = runtime::encoding_ibm424ltr,
		StringEncodingIBM424RTL = runtime::encoding_ibm424rtl
	};
	
	COCONUT_OPT(StringSearchOptions)
	{
		StringSearchDefault = runtime::search_default,
		StringSearchBinary = runtime::search_binary,
		StringSearchLiteral = runtime::search_literal,
		StringSearchWidthInsensitive = runtime::search_nowidth,
		StringSearchCaseInsensitive = runtime::search_insensitive,
		StringSearchDiacriticInsensitive = runtime::search_diacritic,
		StringSearchBackwards= runtime::search_backwards,
		StringSearchForcedOrdering = runtime::search_forceorder,
		StringSearchAnchored = runtime::search_anchored,
		StringSearchNumeric = runtime::search_numeric
	};
		
	COCONUT_OPT(ChunkSplitOption)
	{
		ChunkSplitNone = runtime::chunksplit_none,
		ChunkSplit64CRLF = runtime::chunksplit_64crlf,
		ChunkSplit64LF = runtime::chunksplit_64lf,
		ChunkSplit76CRLF = runtime::chunksplit_76crlf,
		ChunkSplit76LF = runtime::chunksplit_76lf
	};
	
	COCONUT_OPT(NumberType)
	{
		NumberZero = runtime::numeric_zero,
		NumberFloat = runtime::numeric_float,
		NumberDouble = runtime::numeric_double,
		NumberLongDouble = runtime::numeric_long_double,
		NumberBool = runtime::numeric_bool,
		NumberChar = runtime::numeric_char,
		NumberShort = runtime::numeric_short,
		NumberInt = runtime::numeric_int,
		NumberLong = runtime::numeric_long,
		NumberLongLong = runtime::numeric_longlong,
		NumberUnsignedChar = runtime::numeric_unsigned_char,
		NumberUnsignedShort = runtime::numeric_unsigned_short,
		NumberUnsignedInt = runtime::numeric_unsigned_int,
		NumberUnsignedLong = runtime::numeric_unsigned_long,
		NumberUnsignedLongLong = runtime::numeric_unsigned_longlong
	};
	
	COCONUT_OPT(DataPackingOption)
	{
		DataPackingBigEndian = runtime::packing_bigendian,
		DataPackingLittleEndian = runtime::packing_littleendian
	};
		
	COCONUT_OPT(DataUnpackingOption)
	{
		DataUnpackingBigEndian = runtime::unpacking_bigendian,
		DataUnpackingLittleEndian = runtime::unpacking_littleendian
	};
	
	COCONUT_OPT(ByteOrderType)
	{
		ByteOrderBigEndian = 0ULL,
		ByteOrderLittleEndian,
		ByteOrderUnknown
	};
	
	using SwappedFloat = runtime::byteorder::fswp_t;
	using SwappedDouble = runtime::byteorder::dswp_t;
	
	COCONUT_OPT(DirectorySeparatorOption)
	{
		DirectorySeparatorAuto = runtime::dirsep_auto,
		DirectorySeparatorBackslash = runtime::dirsep_slack,
		DirectorySeparatorSlash = runtime::dirsep_whack,
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
		SortConcurrent = (1ULL << 2),
		SortStable = (1ULL << 4),
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
		TimeUnitPlainSeconds = runtime::timeunit_plainseconds,
		TimeUnitDoubleSeconds = runtime::timeunit_doubleseconds,
		TimeUnitMilliSeconds = runtime::timeunit_milliseconds,
		TimeUnitMicroSeconds = runtime::timeunit_microseconds,
		TimeUnitNanoSeconds = runtime::timeunit_nanoseconds
	};
	
	COCONUT_OPT(TimeReferenceOption)
	{
		TimeReferenceSinceCurrentTime = runtime::timeref_since_now,
		TimeReferenceSinceReferenceDate = runtime::timeref_since_ref,
		TimeReferenceSinceJanuary1970 = runtime::timeref_since_1970
	};
	
	COCONUT_OPT(TimestampOption)
	{
		TimestampSinceReferenceDate = runtime::timeref_since_ref,
		TimestampSinceJanuary1970 = runtime::timeref_since_1970
	};
	
	typedef double TimeInterval;
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_TYPES_HPP */

/* EOF */