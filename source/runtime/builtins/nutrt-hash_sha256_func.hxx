//
// nutrt-hash_sha256_func.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

namespace coconut
{ namespace runtime
{ namespace builtins
{
	
// //////////////////////////////////////////////////////////
// @based on sha256.cpp
// Copyright (C) 2014 Stephan Brumme. All rights reserved.
// @see http://create.stephan-brumme.com/disclaimer.html
//

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t hash_sha256_rot(std::uint32_t a, std::uint32_t c)
{ return (a >> c) | (a << (32 - c)); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t hash_sha256_f1(std::uint32_t e, std::uint32_t f, std::uint32_t g)
{
	std::uint32_t term1 = hash_sha256_rot(e, 6) ^ hash_sha256_rot(e, 11) ^ hash_sha256_rot(e, 25);
	std::uint32_t term2 = (e & f) ^ (~e & g);
	return term1 + term2;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t hash_sha256_f2(std::uint32_t a, std::uint32_t b, std::uint32_t c)
{
	std::uint32_t term1 = hash_sha256_rot(a, 2) ^ hash_sha256_rot(a, 13) ^ hash_sha256_rot(a, 22);
	std::uint32_t term2 = ((a | b) & c) | (a & b);
	return term1 + term2;
}

}}} /* EONS */

/* EOF */