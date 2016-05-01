//
// hash-sha256.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/hash.hpp>
#include <coconut/runtime/detail/core/byteorder.hpp>

using namespace coconut::runtime;

#include <source/runtime/builtins/hash_sha256_func.hxx>

hash::sha256::sha256() :
	sha_base(512 / 8, 8)
{ reset(); }

hash::sha256::~sha256()
{ /* NOP */ }

#pragma mark -

void hash::sha256::reset()
{
	m_nbytes = 0;
	m_bufsize = 0;
	m_hash[0] = 0x6a09e667;
	m_hash[1] = 0xbb67ae85;
	m_hash[2] = 0x3c6ef372;
	m_hash[3] = 0xa54ff53a;
	m_hash[4] = 0x510e527f;
	m_hash[5] = 0x9b05688c;
	m_hash[6] = 0x1f83d9ab;
	m_hash[7] = 0x5be0cd19;
}

#pragma mark -

void hash::sha256::process_block(const void * block)
{
	const std::uint32_t * input = weak_cast<const std::uint32_t *>(block);
	std::uint32_t words[64];
	std::size_t i;
	std::uint32_t x, y;
	
	std::uint32_t a = m_hash[0];
	std::uint32_t b = m_hash[1];
	std::uint32_t c = m_hash[2];
	std::uint32_t d = m_hash[3];
	std::uint32_t e = m_hash[4];
	std::uint32_t f = m_hash[5];
	std::uint32_t g = m_hash[6];
	std::uint32_t h = m_hash[7];
	
	for (i = 0; i < 16; i++) {
		words[i] = runtime::byteorder::h2be32(input[i]);
	}
	
	x = h + builtins::hash_sha256_f1(e, f, g) + 0x428a2f98 + words[0]; y = builtins::hash_sha256_f2(a, b, c); d += x; h = x + y;
	x = g + builtins::hash_sha256_f1(d, e, f) + 0x71374491 + words[1]; y = builtins::hash_sha256_f2(h, a, b); c += x; g = x + y;
	x = f + builtins::hash_sha256_f1(c, d, e) + 0xb5c0fbcf + words[2]; y = builtins::hash_sha256_f2(g, h, a); b += x; f = x + y;
	x = e + builtins::hash_sha256_f1(b, c, d) + 0xe9b5dba5 + words[3]; y = builtins::hash_sha256_f2(f, g, h); a += x; e = x + y;
	x = d + builtins::hash_sha256_f1(a, b, c) + 0x3956c25b + words[4]; y = builtins::hash_sha256_f2(e, f, g); h += x; d = x + y;
	x = c + builtins::hash_sha256_f1(h, a, b) + 0x59f111f1 + words[5]; y = builtins::hash_sha256_f2(d, e, f); g += x; c = x + y;
	x = b + builtins::hash_sha256_f1(g, h, a) + 0x923f82a4 + words[6]; y = builtins::hash_sha256_f2(c, d, e); f += x; b = x + y;
	x = a + builtins::hash_sha256_f1(f, g, h) + 0xab1c5ed5 + words[7]; y = builtins::hash_sha256_f2(b, c, d); e += x; a = x + y;
	
	x = h + builtins::hash_sha256_f1(e, f, g) + 0xd807aa98 + words[8]; y = builtins::hash_sha256_f2(a, b, c); d += x; h = x + y;
	x = g + builtins::hash_sha256_f1(d, e, f) + 0x12835b01 + words[9]; y = builtins::hash_sha256_f2(h, a, b); c += x; g = x + y;
	x = f + builtins::hash_sha256_f1(c, d, e) + 0x243185be + words[10]; y = builtins::hash_sha256_f2(g, h, a); b += x; f = x + y;
	x = e + builtins::hash_sha256_f1(b, c, d) + 0x550c7dc3 + words[11]; y = builtins::hash_sha256_f2(f, g, h); a += x; e = x + y;
	x = d + builtins::hash_sha256_f1(a, b, c) + 0x72be5d74 + words[12]; y = builtins::hash_sha256_f2(e, f, g); h += x; d = x + y;
	x = c + builtins::hash_sha256_f1(h, a, b) + 0x80deb1fe + words[13]; y = builtins::hash_sha256_f2(d, e, f); g += x; c = x + y;
	x = b + builtins::hash_sha256_f1(g, h, a) + 0x9bdc06a7 + words[14]; y = builtins::hash_sha256_f2(c, d, e); f += x; b = x + y;
	x = a + builtins::hash_sha256_f1(f, g, h) + 0xc19bf174 + words[15]; y = builtins::hash_sha256_f2(b, c, d); e += x; a = x + y;
	
	for (; i < 24; i++) {
		words[i] = words[i - 16] + (builtins::hash_sha256_rot(words[i - 15], 7) ^ builtins::hash_sha256_rot(words[i - 15], 18) ^ (words[i - 15] >> 3)) +
		words[i-7] + (builtins::hash_sha256_rot(words[i - 2], 17) ^ builtins::hash_sha256_rot(words[i - 2], 19) ^ (words[i - 2] >> 10));
	}
	
	x = h + builtins::hash_sha256_f1(e, f, g) + 0xe49b69c1 + words[16]; y = builtins::hash_sha256_f2(a, b, c); d += x; h = x + y;
	x = g + builtins::hash_sha256_f1(d, e, f) + 0xefbe4786 + words[17]; y = builtins::hash_sha256_f2(h, a, b); c += x; g = x + y;
	x = f + builtins::hash_sha256_f1(c, d, e) + 0x0fc19dc6 + words[18]; y = builtins::hash_sha256_f2(g, h, a); b += x; f = x + y;
	x = e + builtins::hash_sha256_f1(b, c, d) + 0x240ca1cc + words[19]; y = builtins::hash_sha256_f2(f, g, h); a += x; e = x + y;
	x = d + builtins::hash_sha256_f1(a, b, c) + 0x2de92c6f + words[20]; y = builtins::hash_sha256_f2(e, f, g); h += x; d = x + y;
	x = c + builtins::hash_sha256_f1(h, a, b) + 0x4a7484aa + words[21]; y = builtins::hash_sha256_f2(d, e, f); g += x; c = x + y;
	x = b + builtins::hash_sha256_f1(g, h, a) + 0x5cb0a9dc + words[22]; y = builtins::hash_sha256_f2(c, d, e); f += x; b = x + y;
	x = a + builtins::hash_sha256_f1(f, g, h) + 0x76f988da + words[23]; y = builtins::hash_sha256_f2(b, c, d); e += x; a = x + y;
	
	for (; i < 32; i++) {
		words[i] = words[i - 16] + (builtins::hash_sha256_rot(words[i - 15], 7) ^ builtins::hash_sha256_rot(words[i - 15], 18) ^ (words[i - 15] >> 3)) +
		words[i-7] + (builtins::hash_sha256_rot(words[i - 2], 17) ^ builtins::hash_sha256_rot(words[i - 2], 19) ^ (words[i - 2] >> 10));
	}
	
	x = h + builtins::hash_sha256_f1(e, f, g) + 0x983e5152 + words[24]; y = builtins::hash_sha256_f2(a, b, c); d += x; h = x + y;
	x = g + builtins::hash_sha256_f1(d, e, f) + 0xa831c66d + words[25]; y = builtins::hash_sha256_f2(h, a, b); c += x; g = x + y;
	x = f + builtins::hash_sha256_f1(c, d, e) + 0xb00327c8 + words[26]; y = builtins::hash_sha256_f2(g, h, a); b += x; f = x + y;
	x = e + builtins::hash_sha256_f1(b, c, d) + 0xbf597fc7 + words[27]; y = builtins::hash_sha256_f2(f, g, h); a += x; e = x + y;
	x = d + builtins::hash_sha256_f1(a, b, c) + 0xc6e00bf3 + words[28]; y = builtins::hash_sha256_f2(e, f, g); h += x; d = x + y;
	x = c + builtins::hash_sha256_f1(h, a, b) + 0xd5a79147 + words[29]; y = builtins::hash_sha256_f2(d, e, f); g += x; c = x + y;
	x = b + builtins::hash_sha256_f1(g, h, a) + 0x06ca6351 + words[30]; y = builtins::hash_sha256_f2(c, d, e); f += x; b = x + y;
	x = a + builtins::hash_sha256_f1(f, g, h) + 0x14292967 + words[31]; y = builtins::hash_sha256_f2(b, c, d); e += x; a = x + y;
	
	for (; i < 40; i++) {
		words[i] = words[i - 16] + (builtins::hash_sha256_rot(words[i - 15], 7) ^ builtins::hash_sha256_rot(words[i - 15], 18) ^ (words[i - 15] >> 3)) +
		words[i - 7] + (builtins::hash_sha256_rot(words[i - 2], 17) ^ builtins::hash_sha256_rot(words[i - 2], 19) ^ (words[i - 2] >> 10));
	}
	
	x = h + builtins::hash_sha256_f1(e, f, g) + 0x27b70a85 + words[32]; y = builtins::hash_sha256_f2(a, b, c); d += x; h = x + y;
	x = g + builtins::hash_sha256_f1(d, e, f) + 0x2e1b2138 + words[33]; y = builtins::hash_sha256_f2(h, a, b); c += x; g = x + y;
	x = f + builtins::hash_sha256_f1(c, d, e) + 0x4d2c6dfc + words[34]; y = builtins::hash_sha256_f2(g, h, a); b += x; f = x + y;
	x = e + builtins::hash_sha256_f1(b, c, d) + 0x53380d13 + words[35]; y = builtins::hash_sha256_f2(f, g, h); a += x; e = x + y;
	x = d + builtins::hash_sha256_f1(a, b, c) + 0x650a7354 + words[36]; y = builtins::hash_sha256_f2(e, f, g); h += x; d = x + y;
	x = c + builtins::hash_sha256_f1(h, a, b) + 0x766a0abb + words[37]; y = builtins::hash_sha256_f2(d, e, f); g += x; c = x + y;
	x = b + builtins::hash_sha256_f1(g, h, a) + 0x81c2c92e + words[38]; y = builtins::hash_sha256_f2(c, d, e); f += x; b = x + y;
	x = a + builtins::hash_sha256_f1(f, g, h) + 0x92722c85 + words[39]; y = builtins::hash_sha256_f2(b, c, d); e += x; a = x + y;
	
	for (; i < 48; i++) {
		words[i] = words[i - 16] + (builtins::hash_sha256_rot(words[i - 15], 7) ^ builtins::hash_sha256_rot(words[i - 15], 18) ^ (words[i - 15] >> 3)) +
		words[i-7] + (builtins::hash_sha256_rot(words[i - 2], 17) ^ builtins::hash_sha256_rot(words[i - 2], 19) ^ (words[i - 2] >> 10));
	}
	
	x = h + builtins::hash_sha256_f1(e, f, g) + 0xa2bfe8a1 + words[40]; y = builtins::hash_sha256_f2(a, b, c); d += x; h = x + y;
	x = g + builtins::hash_sha256_f1(d, e, f) + 0xa81a664b + words[41]; y = builtins::hash_sha256_f2(h, a, b); c += x; g = x + y;
	x = f + builtins::hash_sha256_f1(c, d, e) + 0xc24b8b70 + words[42]; y = builtins::hash_sha256_f2(g, h, a); b += x; f = x + y;
	x = e + builtins::hash_sha256_f1(b, c, d) + 0xc76c51a3 + words[43]; y = builtins::hash_sha256_f2(f, g, h); a += x; e = x + y;
	x = d + builtins::hash_sha256_f1(a, b, c) + 0xd192e819 + words[44]; y = builtins::hash_sha256_f2(e, f, g); h += x; d = x + y;
	x = c + builtins::hash_sha256_f1(h, a, b) + 0xd6990624 + words[45]; y = builtins::hash_sha256_f2(d, e, f); g += x; c = x + y;
	x = b + builtins::hash_sha256_f1(g, h, a) + 0xf40e3585 + words[46]; y = builtins::hash_sha256_f2(c, d, e); f += x; b = x + y;
	x = a + builtins::hash_sha256_f1(f, g, h) + 0x106aa070 + words[47]; y = builtins::hash_sha256_f2(b, c, d); e += x; a = x + y;
	
	for (; i < 56; i++) {
		words[i] = words[i - 16] + (builtins::hash_sha256_rot(words[i - 15], 7) ^ builtins::hash_sha256_rot(words[i - 15], 18) ^ (words[i - 15] >> 3)) +
		words[i-7] + (builtins::hash_sha256_rot(words[i - 2], 17) ^ builtins::hash_sha256_rot(words[i - 2], 19) ^ (words[i - 2] >> 10));
	}
	
	x = h + builtins::hash_sha256_f1(e, f, g) + 0x19a4c116 + words[48]; y = builtins::hash_sha256_f2(a, b, c); d += x; h = x + y;
	x = g + builtins::hash_sha256_f1(d, e, f) + 0x1e376c08 + words[49]; y = builtins::hash_sha256_f2(h, a, b); c += x; g = x + y;
	x = f + builtins::hash_sha256_f1(c, d, e) + 0x2748774c + words[50]; y = builtins::hash_sha256_f2(g, h, a); b += x; f = x + y;
	x = e + builtins::hash_sha256_f1(b, c, d) + 0x34b0bcb5 + words[51]; y = builtins::hash_sha256_f2(f, g, h); a += x; e = x + y;
	x = d + builtins::hash_sha256_f1(a, b, c) + 0x391c0cb3 + words[52]; y = builtins::hash_sha256_f2(e, f, g); h += x; d = x + y;
	x = c + builtins::hash_sha256_f1(h, a, b) + 0x4ed8aa4a + words[53]; y = builtins::hash_sha256_f2(d, e, f); g += x; c = x + y;
	x = b + builtins::hash_sha256_f1(g, h, a) + 0x5b9cca4f + words[54]; y = builtins::hash_sha256_f2(c, d, e); f += x; b = x + y;
	x = a + builtins::hash_sha256_f1(f, g, h) + 0x682e6ff3 + words[55]; y = builtins::hash_sha256_f2(b, c, d); e += x; a = x + y;
	
	for (; i < 64; i++) {
		words[i] = words[i - 16] + (builtins::hash_sha256_rot(words[i - 15], 7) ^ builtins::hash_sha256_rot(words[i - 15], 18) ^ (words[i - 15] >> 3)) +
		words[i-7] + (builtins::hash_sha256_rot(words[i - 2], 17) ^ builtins::hash_sha256_rot(words[i - 2], 19) ^ (words[i - 2] >> 10));
	}
	
	x = h + builtins::hash_sha256_f1(e, f, g) + 0x748f82ee + words[56]; y = builtins::hash_sha256_f2(a, b, c); d += x; h = x + y;
	x = g + builtins::hash_sha256_f1(d, e, f) + 0x78a5636f + words[57]; y = builtins::hash_sha256_f2(h, a, b); c += x; g = x + y;
	x = f + builtins::hash_sha256_f1(c, d, e) + 0x84c87814 + words[58]; y = builtins::hash_sha256_f2(g, h, a); b += x; f = x + y;
	x = e + builtins::hash_sha256_f1(b, c, d) + 0x8cc70208 + words[59]; y = builtins::hash_sha256_f2(f, g, h); a += x; e = x + y;
	x = d + builtins::hash_sha256_f1(a, b, c) + 0x90befffa + words[60]; y = builtins::hash_sha256_f2(e, f, g); h += x; d = x + y;
	x = c + builtins::hash_sha256_f1(h, a, b) + 0xa4506ceb + words[61]; y = builtins::hash_sha256_f2(d, e, f); g += x; c = x + y;
	x = b + builtins::hash_sha256_f1(g, h, a) + 0xbef9a3f7 + words[62]; y = builtins::hash_sha256_f2(c, d, e); f += x; b = x + y;
	x = a + builtins::hash_sha256_f1(f, g, h) + 0xc67178f2 + words[63]; y = builtins::hash_sha256_f2(b, c, d); e += x; a = x + y;
	
	m_hash[0] += a;
	m_hash[1] += b;
	m_hash[2] += c;
	m_hash[3] += d;
	m_hash[4] += e;
	m_hash[5] += f;
	m_hash[6] += g;
	m_hash[7] += h;
}

/* EOF */