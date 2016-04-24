//
// types.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/defines.hpp>
#include <coconut/runtime/detail/core/spinlock.hpp>
#include <coconut/runtime/detail/core/stream.hpp>

#ifndef COCONUT_RUNTIME_TYPES_HPP
#define COCONUT_RUNTIME_TYPES_HPP

namespace coconut {

template <typename T1, typename T2>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
T1 unsafe_cast(T2 && r)
{ return (T1)r; }

template <typename T1, typename T2>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
T1 & ref_cast(T2 && r)
{ return (T1 &)r; }

template <typename T> using ptr_declare = std::shared_ptr<T>;

template <typename T1, typename... T2>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
ptr_declare<T1> ptr_create(T2 &&... args)
{ return std::make_shared<T1>(std::forward<T2>(args)...); }

template <typename T1, typename T2>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
ptr_declare<T1> ptr_snatch(T2 && ptr)
{ return std::shared_ptr<T1>(unsafe_cast<T1 *>(ptr), [](T1 *) -> void { /* NOP */ }); }

template <typename T1, typename T2>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
ptr_declare<T1> ptr_static_cast(ptr_declare<T2> const & r)
{ return std::static_pointer_cast<T1>(r); }

template <typename T1, typename T2>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
ptr_declare<T1> ptr_dynamic_cast(ptr_declare<T2> const & r)
{ return std::dynamic_pointer_cast<T1>(r); }

template <typename T1, typename T2>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
ptr_declare<T1> ptr_cast(ptr_declare<T2> const & r)
{ return std::dynamic_pointer_cast<T1>(r); }

} /* EONS */

namespace coconut {
	namespace runtime {
	
COCONUT_OPT_TYPED(ComparisonResult, int)
{
	cmp_ascending = -1,
	cmp_same = 0,
	cmp_descending = 1
};

static constexpr std::size_t NotFound = std::numeric_limits<std::size_t>::max();
static constexpr std::size_t MaxFound = (NotFound - 1);

COCONUT_OPT_TYPED(ClassKind, std::uint16_t)
{
	classkind_anon = 0,
	classkind_zombie = 1,
	classkind_nucleus = 2,
	classkind_object = 10,
};

COCONUT_OPT(encoding_option)
{
	encoding_auto = 0ULL,
	
	encoding_utf8 = 1ULL,
	encoding_universal = 1ULL,
	
	encoding_utf16 = 2ULL,
	encoding_unicode = 2ULL,
	
	encoding_utf16be,
	encoding_utf16le,
	
	encoding_utf32,
	encoding_utf32be,
	encoding_utf32le,
	
	encoding_ucs2,
	encoding_ucs2be,
	encoding_ucs2le,
	
	encoding_ucs4,
	encoding_ucs4be,
	encoding_ucs4le,
	
	encoding_shiftjis,
	
	encoding_iso2022jp,
	encoding_iso2022cn,
	encoding_iso2022kr,
	
	encoding_gb18030,
	
	encoding_big5,
	encoding_eucjp,
	encoding_euckr,
	
	encoding_iso88591,
	encoding_iso88592,
	encoding_iso88595,
	encoding_iso88596,
	encoding_iso88597,
	encoding_iso88598,
	encoding_iso88598i,
	encoding_iso88599,
	
	encoding_windows1250,
	encoding_windows1251,
	encoding_windows1252,
	encoding_windows1253,
	encoding_windows1254,
	encoding_windows1255,
	encoding_windows1256,
	
	encoding_koi8r,
	
	encoding_ibm420,
	encoding_ibm420ltr,
	encoding_ibm420rtl,
	
	encoding_ibm424,
	encoding_ibm424ltr,
	encoding_ibm424rtl,
};

COCONUT_OPT(search_options)
{
	search_default = 0ULL,
	search_literal = (1ULL << 3),
	search_nowidth = (1ULL << 5),
	search_insensitive = (1ULL << 7),
	search_diacritic = (1ULL << 9),
	search_backwards = (1ULL << 11),
	search_forceorder = (1ULL << 13),
	search_anchored = (1ULL << 15),
	search_numeric = (1ULL << 17)
};

COCONUT_OPT_TYPED(numeric_option, std::uint16_t)
{
	numeric_zero = 0,
	numeric_float,
	numeric_double,
	numeric_long_double,
	numeric_bool,
	numeric_char,
	numeric_short,
	numeric_int,
	numeric_long,
	numeric_longlong,
	numeric_unsigned_char,
	numeric_unsigned_short,
	numeric_unsigned_int,
	numeric_unsigned_long,
	numeric_unsigned_longlong
};

COCONUT_OPT(unpacking_option)
{
	unpacking_bigendian = 0ULL,
	unpacking_littleendian
};

COCONUT_OPT(packing_option)
{
	packing_bigendian = 0ULL,
	packing_littleendian
};

COCONUT_OPT(chunksplit_option)
{
	chunksplit_none = 0ULL,
	chunksplit_64crlf,
	chunksplit_64lf,
	chunksplit_76crlf,
	chunksplit_76lf
};

COCONUT_OPT(dirsep_option)
{
	dirsep_none = 0ULL,
	dirsep_auto,
	dirsep_slack,
	dirsep_whack
};

COCONUT_OPT(timeunit_option)
{
	timeunit_plainseconds = 0ULL,
	timeunit_doubleseconds,
	timeunit_milliseconds,
	timeunit_microseconds,
	timeunit_nanoseconds
};

COCONUT_OPT(timeref_option)
{
	timeref_since_now = 0ULL,
	timeref_since_ref,
	timeref_since_1970
};

COCONUT_OPT(datekind_option)
{
	datekind_default = 0ULL,
	datekind_calendar
};

COCONUT_OPT(launch_option)
{
	launch_async = 0ULL,
	launch_deferred,
	launch_any
};

COCONUT_CLASSFORWARD_DCL(nucleus)
using Any = nucleus;
template <typename T> using Owning = ptr_declare<T>;

}} /* EONS */

#endif /* !COCONUT_RUNTIME_TYPES_HPP */

/* EOF */