//
// stream.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/stream.hpp>
#include <coconut/runtime/detail/core/types.hpp>
#include <coconut/runtime/detail/core/unicode.hpp>

#include <source/runtime/builtins/stream_convpath.hxx>

using namespace coconut::runtime;

stream::ifstream::ifstream() :
	std::ifstream()
{ /* NOP */ }

stream::ifstream::ifstream(const std::string & utf8_path, std::ios_base::open_mode mode) :
	std::ifstream(builtins::stream_convpath(utf8_path).c_str(), mode)
{ /* NOP */ }

stream::ifstream::ifstream(const std::u16string & utf16_path, std::ios_base::open_mode mode) :
	std::ifstream(builtins::stream_convpath(utf16_path).c_str(), mode)
{ /* NOP */ }

stream::ifstream::~ifstream()
{ /* NOP */ }

void stream::ifstream::open(const std::string & utf8_path, std::ios_base::open_mode mode)
{
	std::ifstream::open(builtins::stream_convpath(utf8_path).c_str(), mode);
}

void stream::ifstream::open(const std::u16string & utf16_path, std::ios_base::open_mode mode)
{
	std::ifstream::open(builtins::stream_convpath(utf16_path).c_str(), mode);
}

#pragma mark -

stream::ofstream::ofstream() :
	std::ofstream()
{ /* NOP */ }

stream::ofstream::ofstream(const std::string & utf8_path, std::ios_base::open_mode mode) :
	std::ofstream(builtins::stream_convpath(utf8_path).c_str(), mode)
{ /* NOP */ }

stream::ofstream::ofstream(const std::u16string & utf16_path, std::ios_base::open_mode mode) :
	std::ofstream(builtins::stream_convpath(utf16_path).c_str(), mode)
{ /* NOP */ }

stream::ofstream::~ofstream()
{ /* NOP */ }

void stream::ofstream::open(const std::string & utf8_path, std::ios_base::open_mode mode)
{
	std::ofstream::open(builtins::stream_convpath(utf8_path).c_str(), mode);
}

void stream::ofstream::open(const std::u16string & utf16_path, std::ios_base::open_mode mode)
{
	std::ofstream::open(builtins::stream_convpath(utf16_path).c_str(), mode);
}

#pragma mark -

stream::fstream::fstream() :
	std::fstream()
{ /* NOP */ }

stream::fstream::fstream(const std::string & utf8_path, std::ios_base::open_mode mode) :
	std::fstream(builtins::stream_convpath(utf8_path).c_str(), mode)
{ /* NOP */ }

stream::fstream::fstream(const std::u16string & utf16_path, std::ios_base::open_mode mode) :
	std::fstream(builtins::stream_convpath(utf16_path).c_str(), mode)
{ /* NOP */ }

stream::fstream::~fstream()
{ /* NOP */ }

void stream::fstream::open(const std::string & utf8_path, std::ios_base::open_mode mode)
{
	std::fstream::open(builtins::stream_convpath(utf8_path).c_str(), mode);
}

void stream::fstream::open(const std::u16string & utf16_path, std::ios_base::open_mode mode)
{
	std::fstream::open(builtins::stream_convpath(utf16_path).c_str(), mode);
}

#pragma mark -

stream::imstreambuf::imstreambuf() :
	std::streambuf(),
	m_begin(0),
	m_size(0),
	m_end(0),
	m_current(0)
{ /* NOP */ }

stream::imstreambuf::imstreambuf(imstreambuf &) :
	std::streambuf(),
	m_begin(0),
	m_size(0),
	m_end(0),
	m_current(0)
{ /* NOP */ }

stream::imstreambuf::imstreambuf(const char * membytes, std::size_t size) :
	std::streambuf(),
	m_begin(unsafe_cast<char *>(membytes)),
	m_size(size),
	m_end(m_begin + size),
	m_current(m_begin)
{ setg(m_begin, m_current, m_end); }

stream::imstreambuf::imstreambuf(const std::uint8_t * membytes, std::size_t size) :
	std::streambuf(),
	m_begin(unsafe_cast<char *>(membytes)),
	m_size(size),
	m_end(m_begin + size),
	m_current(m_begin)
{ setg(m_begin, m_current, m_end); }

stream::imstreambuf::~imstreambuf()
{ 
	m_begin = nullptr;
	m_size = 0;
	m_end = nullptr;
	m_current = nullptr;
}

void stream::imstreambuf::setmem(const char * membytes, std::size_t size)
{
	m_begin = unsafe_cast<char *>(membytes);
	m_size = size;
	m_end = m_begin + size;
	m_current = m_begin;
	setg(m_begin, m_current, m_end);
}

void stream::imstreambuf::setmem(const std::uint8_t * membytes, std::size_t size)
{
	m_begin = unsafe_cast<char *>(membytes);
	m_size = size;
	m_end = m_begin + size;
	m_current = m_begin;
	setg(m_begin, m_current, m_end);
}

const char * stream::imstreambuf::membytes()
{
	return m_begin;
}

std::size_t stream::imstreambuf::memsize()
{
	return m_size;
}

std::streambuf::int_type stream::imstreambuf::uflow()
{
	if (m_current == m_end) {
		return std::streambuf::traits_type::eof();
	}
	return *m_current++;
}

std::streambuf::int_type stream::imstreambuf::underflow()
{
	if (m_current == m_end) {
		return std::streambuf::traits_type::eof();
	}
	return *m_current;
}

std::streamsize stream::imstreambuf::showmanyc()
{
	// assert(std::less_equal<const char *>()(m_current, m_end));
	return m_end - m_current;
}

std::streambuf::int_type stream::imstreambuf::pbackfail(std::streambuf::int_type ch)
{
	if (m_current == m_begin || (ch != std::streambuf::traits_type::eof() && ch != m_current[-1])) {
		return std::streambuf::traits_type::eof();
	}
	return *--m_current;
}

std::size_t stream::imstreambuf::output_bytes() {
	return static_cast<std::size_t>(pptr() - pbase());
}

std::streambuf::pos_type stream::imstreambuf::seekoff(std::streambuf::off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which)
{
	COCONUT_UNUSED(which);
	off_type offset = (std::ios::beg == dir) ? off : (std::ios::end == dir) ? (static_cast<off_type>(m_size) - off) : (gptr() - m_begin) + off;
	setg(m_begin, m_begin + offset, m_begin + m_size);
	return gptr() - m_begin;
}

#pragma mark -

stream::imstream::imstream() :
	std::istream(&m_imstreambuf),
	m_imstreambuf(unsafe_cast<std::uint8_t *>(nullptr), 0)
{ /* NOP */ }

stream::imstream::imstream(imstream & im) :
	std::istream(&m_imstreambuf),
	m_imstreambuf()
{ m_imstreambuf.setmem(im.m_imstreambuf.membytes(), im.m_imstreambuf.memsize()); }

stream::imstream::imstream(const char * membytes, std::size_t size) :
	std::istream(&m_imstreambuf),
	m_imstreambuf(membytes, size)
{ /* NOP */ }

stream::imstream::imstream(const std::uint8_t * membytes, std::size_t size) :
	std::istream(&m_imstreambuf),
	m_imstreambuf(membytes, size)
{ /* NOP */ }

stream::imstream::~imstream()
{ /* NOP */ }

/* EOF */