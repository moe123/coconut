//
// nutrt-stream.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-defines.hpp>

#ifndef COCONUT_RUNTIME_STREAM_HPP
#define COCONUT_RUNTIME_STREAM_HPP

namespace coconut
{ namespace runtime
{ namespace stream
{

COCONUT_PRIVATE class COCONUT_VISIBLE ifstream COCONUT_FINAL : public std::ifstream
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.stream.ifstream, stream.ifstream)

public:
	ifstream();
	explicit ifstream(const std::string & utf8_path, std::ios_base::open_mode mode = std::ios_base::in|std::ios_base::binary);
	explicit ifstream(const std::u16string & utf16_path, std::ios_base::open_mode mode = std::ios_base::in|std::ios_base::binary);
	virtual ~ifstream();
	
	void open(const std::string & utf8_path, std::ios_base::open_mode mode = std::ios_base::in|std::ios_base::binary);
	void open(const std::u16string & utf16_path, std::ios_base::open_mode mode = std::ios_base::in|std::ios_base::binary);
};

COCONUT_PRIVATE class COCONUT_VISIBLE ofstream COCONUT_FINAL : public std::ofstream
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.stream.ofstream, stream.ofstream)

public:
	ofstream();
	explicit ofstream(const std::string & utf8_path, std::ios_base::open_mode mode = std::ios_base::out|std::ios_base::binary);
	explicit ofstream(const std::u16string & utf16_path, std::ios_base::open_mode mode = std::ios_base::out|std::ios_base::binary);
	virtual ~ofstream();
	
	void open(const std::string & utf8_path, std::ios_base::open_mode mode = std::ios_base::out|std::ios_base::binary);
	void open(const std::u16string & utf16_path, std::ios_base::open_mode mode = std::ios_base::out|std::ios_base::binary);
};

COCONUT_PRIVATE class COCONUT_VISIBLE fstream COCONUT_FINAL : public std::fstream
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.stream.fstream, stream.fstream)

public:
	fstream();
	explicit fstream(const std::string & utf8_path, std::ios_base::open_mode mode = std::ios_base::in|std::ios_base::out|std::ios_base::binary);
	explicit fstream(const std::u16string & utf16_path, std::ios_base::open_mode mode = std::ios_base::in|std::ios_base::out|std::ios_base::binary);
	virtual ~fstream();
	
	void open(const std::string & utf8_path, std::ios_base::open_mode mode = std::ios_base::in|std::ios_base::out|std::ios_base::binary);
	void open(const std::u16string & utf16_path, std::ios_base::open_mode mode = std::ios_base::in|std::ios_base::out|std::ios_base::binary);
};

COCONUT_PRIVATE class COCONUT_VISIBLE imstreambuf COCONUT_FINAL : public std::streambuf
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.stream.imstreambuf, stream.imstreambuf)

public:
	imstreambuf();
	imstreambuf(imstreambuf &);
	explicit imstreambuf(const char * membytes, std::size_t size);
	explicit imstreambuf(const std::uint8_t * membytes, std::size_t size);
	virtual ~imstreambuf();
	
	void setmem(const char * membytes, std::size_t size);
	void setmem(const std::uint8_t * membytes, std::size_t size);
	
	const char * membytes();
	std::size_t memsize();
	
protected:
	int_type uflow() COCONUT_FINAL_OVERRIDE;
	int_type underflow() COCONUT_FINAL_OVERRIDE;
	std::streamsize showmanyc() COCONUT_FINAL_OVERRIDE;
	int_type pbackfail(int_type ch) COCONUT_FINAL_OVERRIDE;
	std::size_t output_bytes();
	pos_type seekoff
	(
		off_type off,
		std::ios_base::seekdir dir,
		std::ios_base::openmode which = std::ios_base::in|std::ios_base::out
	) COCONUT_FINAL_OVERRIDE;
	
private:
	char * m_head;
	std::size_t m_size;
	char * m_tail;
	char * m_curr;
};

COCONUT_PRIVATE class COCONUT_VISIBLE imstream COCONUT_FINAL : public std::istream
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.stream.imstream, stream.imstream)

public:
	imstream();
	imstream(imstream &);
	explicit imstream(const char * membytes, std::size_t size);
	explicit imstream(const std::uint8_t * membytes, std::size_t size);
	virtual ~imstream();

private:
	imstreambuf m_imstreambuf;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_STREAM_HPP */

/* EOF */