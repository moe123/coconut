//
// nutrt-stream.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-stream.hpp>
#include <coconut/runtime/details/nutrt-types.hpp>
#include <coconut/runtime/details/nutrt-unicode.hpp>

using namespace coconut::runtime;

#include <source/runtime/builtins/nutrt-unicode_wide.hxx>
#include <source/runtime/builtins/nutrt-stream_convpath.hxx>

stream::ifstream::ifstream()
: std::ifstream()
{ /* NOP */ }

stream::ifstream::ifstream(const std::string & utf8_path, std::ios_base::open_mode mode)
: std::ifstream(builtins::stream_convpath(utf8_path).c_str(), mode)
{ /* NOP */ }

stream::ifstream::ifstream(const std::u16string & utf16_path, std::ios_base::open_mode mode)
: std::ifstream(builtins::stream_convpath(utf16_path).c_str(), mode)
{ /* NOP */ }

stream::ifstream::~ifstream()
{ /* NOP */ }

void stream::ifstream::open(const std::string & utf8_path, std::ios_base::open_mode mode)
{ std::ifstream::open(builtins::stream_convpath(utf8_path).c_str(), mode); }

void stream::ifstream::open(const std::u16string & utf16_path, std::ios_base::open_mode mode)
{ std::ifstream::open(builtins::stream_convpath(utf16_path).c_str(), mode); }

#pragma mark -

stream::ofstream::ofstream()
: std::ofstream()
{ /* NOP */ }

stream::ofstream::ofstream(const std::string & utf8_path, std::ios_base::open_mode mode)
: std::ofstream(builtins::stream_convpath(utf8_path).c_str(), mode)
{ /* NOP */ }

stream::ofstream::ofstream(const std::u16string & utf16_path, std::ios_base::open_mode mode)
: std::ofstream(builtins::stream_convpath(utf16_path).c_str(), mode)
{ /* NOP */ }

stream::ofstream::~ofstream()
{ /* NOP */ }

void stream::ofstream::open(const std::string & utf8_path, std::ios_base::open_mode mode)
{ std::ofstream::open(builtins::stream_convpath(utf8_path).c_str(), mode); }

void stream::ofstream::open(const std::u16string & utf16_path, std::ios_base::open_mode mode)
{ std::ofstream::open(builtins::stream_convpath(utf16_path).c_str(), mode); }

#pragma mark -

stream::fstream::fstream() :
	std::fstream()
{ /* NOP */ }

stream::fstream::fstream(const std::string & utf8_path, std::ios_base::open_mode mode)
: std::fstream(builtins::stream_convpath(utf8_path).c_str(), mode)
{ /* NOP */ }

stream::fstream::fstream(const std::u16string & utf16_path, std::ios_base::open_mode mode)
: std::fstream(builtins::stream_convpath(utf16_path).c_str(), mode)
{ /* NOP */ }

stream::fstream::~fstream()
{ /* NOP */ }

void stream::fstream::open(const std::string & utf8_path, std::ios_base::open_mode mode)
{ std::fstream::open(builtins::stream_convpath(utf8_path).c_str(), mode); }

void stream::fstream::open(const std::u16string & utf16_path, std::ios_base::open_mode mode)
{ std::fstream::open(builtins::stream_convpath(utf16_path).c_str(), mode); }

#pragma mark -

stream::imstreambuf::imstreambuf()
: std::streambuf()
, m_head(0)
, m_size(0)
, m_tail(0)
, m_curr(0)
{ /* NOP */ }

stream::imstreambuf::imstreambuf(imstreambuf &)
: std::streambuf()
, m_head(0)
, m_size(0)
, m_tail(0)
, m_curr(0)
{ /* NOP */ }

stream::imstreambuf::imstreambuf(const char * membytes, std::size_t size)
: std::streambuf()
, m_head(weak_cast<char *>(membytes))
, m_size(size)
, m_tail(m_head + size)
, m_curr(m_head)
{ setg(m_head, m_curr, m_tail); }

stream::imstreambuf::imstreambuf(const std::uint8_t * membytes, std::size_t size)
: std::streambuf()
, m_head(weak_cast<char *>(membytes))
, m_size(size)
, m_tail(m_head + size)
, m_curr(m_head)
{ setg(m_head, m_curr, m_tail); }

stream::imstreambuf::~imstreambuf()
{ 
	m_head = nullptr;
	m_size = 0;
	m_tail = nullptr;
	m_curr = nullptr;
}

void stream::imstreambuf::setmem(const char * membytes, std::size_t size)
{
	m_head = weak_cast<char *>(membytes);
	m_size = size;
	m_tail = m_head + size;
	m_curr = m_head;
	setg(m_head, m_curr, m_tail);
}

void stream::imstreambuf::setmem(const std::uint8_t * membytes, std::size_t size)
{
	m_head = weak_cast<char *>(membytes);
	m_size = size;
	m_tail = m_head + size;
	m_curr = m_head;
	setg(m_head, m_curr, m_tail);
}

const char * stream::imstreambuf::membytes()
{ return m_head; }

std::size_t stream::imstreambuf::memsize()
{ return m_size; }

std::streambuf::int_type stream::imstreambuf::uflow()
{
	if (m_curr == m_tail) {
		return std::streambuf::traits_type::eof();
	}
	return *m_curr++;
}

std::streambuf::int_type stream::imstreambuf::underflow()
{
	if (m_curr == m_tail) {
		return std::streambuf::traits_type::eof();
	}
	return *m_curr;
}

std::streamsize stream::imstreambuf::showmanyc()
{
	// assert(std::less_equal<const char *>()(m_curr, m_tail));
	return m_tail - m_curr;
}

std::streambuf::int_type stream::imstreambuf::pbackfail(std::streambuf::int_type ch)
{
	if (m_curr == m_head || (ch != std::streambuf::traits_type::eof() && ch != m_curr[-1])) {
		return std::streambuf::traits_type::eof();
	}
	return *--m_curr;
}

std::size_t stream::imstreambuf::output_bytes()
{ return weak_cast<std::size_t>(pptr() - pbase()); }

std::streambuf::pos_type stream::imstreambuf::seekoff(
	std::streambuf::off_type off,
	std::ios_base::seekdir dir,
	std::ios_base::openmode which
) {
	COCONUT_UNUSED(which);
	off_type offset = (std::ios::beg == dir) ? off :
		(std::ios::end == dir) ? (weak_cast<off_type>(m_size) - off) : (gptr() - m_head) + off;
	setg(m_head, m_head + offset, m_head + m_size);
	return gptr() - m_head;
}

#pragma mark -

stream::imstream::imstream()
: std::istream(&m_imstreambuf)
, m_imstreambuf(weak_cast<std::uint8_t *>(nullptr), 0)
{ /* NOP */ }

stream::imstream::imstream(imstream & im)
: std::istream(&m_imstreambuf)
, m_imstreambuf()
{ m_imstreambuf.setmem(im.m_imstreambuf.membytes(), im.m_imstreambuf.memsize()); }

stream::imstream::imstream(const char * membytes, std::size_t size)
: std::istream(&m_imstreambuf)
, m_imstreambuf(membytes, size)
{ /* NOP */ }

stream::imstream::imstream(const std::uint8_t * membytes, std::size_t size)
: std::istream(&m_imstreambuf)
, m_imstreambuf(membytes, size)
{ /* NOP */ }

stream::imstream::~imstream()
{ /* NOP */ }

/* EOF */