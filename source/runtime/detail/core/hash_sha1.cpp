//
// hash-sha1.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/hash.hpp>
#include <coconut/runtime/detail/core/byteorder.hpp>

#include <source/runtime/builtins/hash_sha1_func.hxx>

using namespace coconut::runtime;

hash::sha1::sha1() :
	sha_base(512 / 8, 5)
{ reset(); }

hash::sha1::~sha1()
{ /* NOP */ }

#pragma mark -

void hash::sha1::reset()
{
	m_nbytes = 0;
	m_bufsize = 0;
	m_hash[0] = 0x67452301;
	m_hash[1] = 0xefcdab89;
	m_hash[2] = 0x98badcfe;
	m_hash[3] = 0x10325476;
	m_hash[4] = 0xc3d2e1f0;
}

#pragma mark -

void hash::sha1::process_block(const void * block)
{
	const std::uint32_t * input = unsafe_cast<const std::uint32_t *>(block);
	std::uint32_t words[80];
	std::size_t i;
	std::uint32_t a = m_hash[0];
	std::uint32_t b = m_hash[1];
	std::uint32_t c = m_hash[2];
	std::uint32_t d = m_hash[3];
	std::uint32_t e = m_hash[4];
	
	for (i = 0; i < 16; i++) {
		words[i] = runtime::byteorder::h2be32(input[i]);
	}
	
	for (i = 16; i < 80; i++) {
		words[i] = builtins::hash_sha1_rot(words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16], 1);
	}
	
	for (i = 0; i < 4; i++) {
		std::size_t offset = 5 * i;
		e += builtins::hash_sha1_rot(a, 5) + builtins::hash_sha1_f1(b, c, d) + words[offset] + 0x5a827999; b = builtins::hash_sha1_rot(b, 30);
		d += builtins::hash_sha1_rot(e, 5) + builtins::hash_sha1_f1(a, b, c) + words[offset + 1] + 0x5a827999; a = builtins::hash_sha1_rot(a, 30);
		c += builtins::hash_sha1_rot(d, 5) + builtins::hash_sha1_f1(e, a, b) + words[offset + 2] + 0x5a827999; e = builtins::hash_sha1_rot(e, 30);
		b += builtins::hash_sha1_rot(c, 5) + builtins::hash_sha1_f1(d, e, a) + words[offset + 3] + 0x5a827999; d = builtins::hash_sha1_rot(d, 30);
		a += builtins::hash_sha1_rot(b, 5) + builtins::hash_sha1_f1(c, d, e) + words[offset + 4] + 0x5a827999; c = builtins::hash_sha1_rot(c, 30);
	}
	
	for (i = 4; i < 8; i++) {
		std::size_t offset = 5 * i;
		e += builtins::hash_sha1_rot(a, 5) + builtins::hash_sha1_f2(b, c, d) + words[offset] + 0x6ed9eba1; b = builtins::hash_sha1_rot(b, 30);
		d += builtins::hash_sha1_rot(e, 5) + builtins::hash_sha1_f2(a, b, c) + words[offset + 1] + 0x6ed9eba1; a = builtins::hash_sha1_rot(a, 30);
		c += builtins::hash_sha1_rot(d, 5) + builtins::hash_sha1_f2(e, a, b) + words[offset + 2] + 0x6ed9eba1; e = builtins::hash_sha1_rot(e, 30);
		b += builtins::hash_sha1_rot(c, 5) + builtins::hash_sha1_f2(d, e, a) + words[offset + 3] + 0x6ed9eba1; d = builtins::hash_sha1_rot(d, 30);
		a += builtins::hash_sha1_rot(b, 5) + builtins::hash_sha1_f2(c, d, e) + words[offset + 4] + 0x6ed9eba1; c = builtins::hash_sha1_rot(c, 30);
	}
	
	for (i = 8; i < 12; i++) {
		std::size_t offset = 5 * i;
		e += builtins::hash_sha1_rot(a, 5) + builtins::hash_sha1_f3(b, c, d) + words[offset] + 0x8f1bbcdc; b = builtins::hash_sha1_rot(b, 30);
		d += builtins::hash_sha1_rot(e, 5) + builtins::hash_sha1_f3(a, b, c) + words[offset + 1] + 0x8f1bbcdc; a = builtins::hash_sha1_rot(a, 30);
		c += builtins::hash_sha1_rot(d, 5) + builtins::hash_sha1_f3(e, a, b) + words[offset + 2] + 0x8f1bbcdc; e = builtins::hash_sha1_rot(e, 30);
		b += builtins::hash_sha1_rot(c, 5) + builtins::hash_sha1_f3(d, e, a) + words[offset + 3] + 0x8f1bbcdc; d = builtins::hash_sha1_rot(d, 30);
		a += builtins::hash_sha1_rot(b, 5) + builtins::hash_sha1_f3(c, d, e) + words[offset + 4] + 0x8f1bbcdc; c = builtins::hash_sha1_rot(c, 30);
	}
	
	for (i = 12; i < 16; i++) {
		std::size_t offset = 5 * i;
		e += builtins::hash_sha1_rot(a, 5) + builtins::hash_sha1_f2(b, c, d) + words[offset] + 0xca62c1d6; b = builtins::hash_sha1_rot(b, 30);
		d += builtins::hash_sha1_rot(e, 5) + builtins::hash_sha1_f2(a, b, c) + words[offset + 1] + 0xca62c1d6; a = builtins::hash_sha1_rot(a, 30);
		c += builtins::hash_sha1_rot(d, 5) + builtins::hash_sha1_f2(e, a, b) + words[offset + 2] + 0xca62c1d6; e = builtins::hash_sha1_rot(e, 30);
		b += builtins::hash_sha1_rot(c, 5) + builtins::hash_sha1_f2(d, e, a) + words[offset + 3] + 0xca62c1d6; d = builtins::hash_sha1_rot(d, 30);
		a += builtins::hash_sha1_rot(b, 5) + builtins::hash_sha1_f2(c, d, e) + words[offset + 4] + 0xca62c1d6; c = builtins::hash_sha1_rot(c, 30);
	}
	
	m_hash[0] += a;
	m_hash[1] += b;
	m_hash[2] += c;
	m_hash[3] += d;
	m_hash[4] += e;
}

/* EOF */