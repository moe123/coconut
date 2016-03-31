//
// hash-sha_base.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

// //////////////////////////////////////////////////////////
// @based on sha1.cpp, sha256.cpp
// Copyright (c) 2014 Stephan Brumme. All rights reserved.
// @see http://create.stephan-brumme.com/disclaimer.html
//

#include <coconut/runtime/detail/core/hash.hpp>
#include <coconut/runtime/detail/core/byteorder.hpp>

#include <source/runtime/builtins/hash_sha_base.hxx>

using namespace coconut::runtime;

#pragma mark -

hash::sha_base::sha_base() :
	m_blocksize(0),
	m_digestsize(0),
	m_nbytes(0),
	m_bufsize(0),
	m_buf(nullptr),
	m_bufextra(nullptr),
	m_hash(nullptr)
{ /* NOP */ }

hash::sha_base::sha_base(std::size_t blocksize, std::size_t digestsize) :
	m_blocksize(blocksize),
	m_digestsize(digestsize),
	m_nbytes(0),
	m_bufsize(0),
	m_buf(nullptr),
	m_bufextra(nullptr),
	m_hash(nullptr)
{
	m_buf = new std::uint8_t[m_blocksize];
	m_bufextra = new std::uint8_t[m_blocksize];
	m_hash = new std::uint32_t[m_digestsize];
}

hash::sha_base::~sha_base()
{
	if (m_buf) {
		delete [] m_buf;
		m_buf = nullptr;
	}
	if (m_bufextra) {
		delete [] m_bufextra;
		m_bufextra = nullptr;
	}
	if (m_hash) {
		delete [] m_hash;
		m_hash = nullptr;
	}
}

#pragma mark -

void hash::sha_base::add(const void * bytes, std::size_t length)
{
	const std::uint8_t * current = unsafe_cast<const std::uint8_t *>(bytes);

	if (m_bufsize > 0) {
		while (length > 0 && m_bufsize < m_blocksize) {
			m_buf[m_bufsize++] = *current++;
			length--;
		}
	}

	if (m_bufsize == m_blocksize) {
		process_block(m_buf);
		m_nbytes += m_blocksize;
		m_bufsize = 0;
	}
	
	if (length == 0) {
		return;
	}

	while (length >= m_blocksize) {
		process_block(current);
		current += m_blocksize;
		m_nbytes += m_blocksize;
		length -= m_blocksize;
	}

	while (length > 0) {
		m_buf[m_bufsize++] = *current++;
		length--;
	}
}

const std::vector<char> hash::sha_base::hex()
{
	std::string result;
	static const char dec2hex[16 + 1] = "0123456789abcdef";
	std::vector<std::uint32_t> old_hash(m_digestsize);
	std::vector<char> hash_buf(m_digestsize * 8 + 1);
	std::size_t offset = 0;
	
	for (std::size_t i = 0; i < m_digestsize; i++) {
		old_hash[i] = m_hash[i];
	}
	
	process_buffer();
	
	for (std::size_t i = 0; i < m_digestsize; i++) {
		hash_buf[offset++] = dec2hex[(m_hash[i] >> 28) & 15];
		hash_buf[offset++] = dec2hex[(m_hash[i] >> 24) & 15];
		hash_buf[offset++] = dec2hex[(m_hash[i] >> 20) & 15];
		hash_buf[offset++] = dec2hex[(m_hash[i] >> 16) & 15];
		hash_buf[offset++] = dec2hex[(m_hash[i] >> 12) & 15];
		hash_buf[offset++] = dec2hex[(m_hash[i] >> 8) & 15];
		hash_buf[offset++] = dec2hex[(m_hash[i] >> 4) & 15];
		hash_buf[offset++] = dec2hex[m_hash[i] & 15];
		m_hash[i] = old_hash[i];
	}
	hash_buf[offset] = 0;
	hash_buf.resize(offset);
	hash_buf.pop_back();
	
	return hash_buf;
}

const std::vector<std::uint8_t> hash::sha_base::raw()
{
	std::vector<std::uint32_t> old_hash(m_digestsize);
	std::vector<std::uint8_t> hash_buf(m_digestsize * sizeof(std::uint32_t));
	std::size_t offset = 0;
	std::size_t i;
	
	for (i = 0; i < m_digestsize; i++) {
		old_hash[i] = m_hash[i];
	}
	
	process_buffer();

	for (i = 0 ; i < m_digestsize ; i++) {
		std::uint32_t v = m_hash[i];
		hash_buf[offset + 0] = (v & 0xFF000000) >> 24;
		hash_buf[offset + 1] = (v & 0x00FF0000) >> 16;
		hash_buf[offset + 2] = (v & 0x0000FF00) >> 8;
		hash_buf[offset + 3] = (v & 0x000000FF);
		offset += sizeof(std::uint32_t);
	}

	for (i = 0; i < m_digestsize; i++) {
		m_hash[i] = old_hash[i];
	}

	return hash_buf;
}

#pragma mark -

void hash::sha_base::process_buffer()
{
	std::size_t padded_len;
	std::size_t i;
	std::size_t lower11bits;
	std::uint64_t msgbits;
	std::uint8_t * add_len;
	
	padded_len = m_bufsize * 8;
	padded_len++;
	lower11bits = padded_len & 511;

	std::memset(m_bufextra, 0, m_blocksize);
	
	if (lower11bits <= 448) {
		padded_len += 448 - lower11bits;
	} else {
		padded_len += 512 + 448 - lower11bits;
	}
	padded_len /= 8;
	
	if (m_bufsize < m_blocksize) {
		m_buf[m_bufsize] = 128;
	} else {
		m_bufextra[0] = 128;
	}
	
	for (i = m_bufsize + 1; i < m_blocksize; i++) {
		m_buf[i] = 0;
	}
	
	for (; i < padded_len; i++) {
		m_bufextra[i - m_blocksize] = 0;
	}
	
	msgbits = 8 * (m_nbytes + m_bufsize);
	
	if (padded_len < m_blocksize) {
		add_len = m_buf + padded_len;
	} else {
		add_len = m_bufextra + padded_len - m_blocksize;
	}
	
	*add_len++ = (msgbits >> 56) & 0xFF;
	*add_len++ = (msgbits >> 48) & 0xFF;
	*add_len++ = (msgbits >> 40) & 0xFF;
	*add_len++ = (msgbits >> 32) & 0xFF;
	*add_len++ = (msgbits >> 24) & 0xFF;
	*add_len++ = (msgbits >> 16) & 0xFF;
	*add_len++ = (msgbits >> 8) & 0xFF;
	*add_len = msgbits & 0xFF;

	process_block(m_buf);

	if (padded_len > m_blocksize) {
		process_block(m_bufextra);
	}
}

const std::vector<char> hash::sha1_hex(const void * bytes, std::size_t len)
{
	sha1 h;
	h.add(bytes, len);
	return h.hex();
}

const std::vector<char> hash::sha1_hex(stream::imstream & in_binary)
{
	sha1 h;
	builtins::hash_sha_hex(in_binary, &h);
	return h.hex();
}

const std::vector<char> hash::sha1_hex(stream::ifstream & in_binary)
{
	sha1 h;
	if (in_binary.is_open()) {
		builtins::hash_sha_hex(in_binary, &h);
	}
	return h.hex();
}

#pragma mark -

const std::vector<std::uint8_t> hash::sha1_raw(const void * bytes, std::size_t len)
{
	sha1 h;
	h.add(bytes, len);
	return h.raw();
}

const std::vector<std::uint8_t> hash::sha1_raw(stream::imstream & in_binary)
{
	sha1 h;
	builtins::hash_sha_hex(in_binary, &h);
	return h.raw();
}

const std::vector<std::uint8_t> hash::sha1_raw(stream::ifstream & in_binary)
{
	sha1 h;
	if (in_binary.is_open()) {
		builtins::hash_sha_hex(in_binary, &h);
	}
	return h.raw();
}

#pragma mark -

const std::vector<char> hash::sha256_hex(const void * bytes, std::size_t len)
{
	sha256 h;
	h.add(bytes, len);
	return h.hex();
}

const std::vector<char> hash::sha256_hex(stream::imstream & in_binary)
{
	sha256 h;
	builtins::hash_sha_hex(in_binary, &h);
	return h.hex();
}

const std::vector<char> hash::sha256_hex(stream::ifstream & in_binary)
{
	sha256 h;
	if (in_binary.is_open()) {
		builtins::hash_sha_hex(in_binary, &h);
	}
	return h.hex();
}

#pragma mark -

const std::vector<std::uint8_t> hash::sha256_raw(const void * bytes, std::size_t len)
{
	sha256 h;
	h.add(bytes, len);
	return h.raw();
}

const std::vector<std::uint8_t> hash::sha256_raw(stream::imstream & in_binary)
{
	sha256 h;
	builtins::hash_sha_hex(in_binary, &h);
	return h.raw();
}

const std::vector<std::uint8_t> hash::sha256_raw(stream::ifstream & in_binary)
{
	sha256 h;
	if (in_binary.is_open()) {
		builtins::hash_sha_hex(in_binary, &h);
	}
	return h.raw();
}

/* EOF */