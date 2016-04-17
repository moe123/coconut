//
// hash_sha1_func.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

// //////////////////////////////////////////////////////////
// @based on sha1.cpp
// Copyright (C) 2014 Stephan Brumme. All rights reserved.
// @see http://create.stephan-brumme.com/disclaimer.html
//

namespace coconut { namespace runtime { namespace builtins {
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t hash_sha1_rot(std::uint32_t a, std::uint32_t c)
{ return (a << c) | (a >> (32 - c)); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t hash_sha1_f1(std::uint32_t b, std::uint32_t c, std::uint32_t d)
{ return d ^ (b & (c ^ d)); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t hash_sha1_f2(std::uint32_t b, std::uint32_t c, std::uint32_t d)
{ return b ^ c ^ d; }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t hash_sha1_f3(std::uint32_t b, std::uint32_t c, std::uint32_t d)
{ return (b & c) | (b & d) | (c & d); }

}}} /* EONS */

/* EOF */