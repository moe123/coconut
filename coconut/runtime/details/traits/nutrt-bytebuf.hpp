//
// nutrt-bytebuf.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>
#include <coconut/runtime/details/nutrt-stream.hpp>

#ifndef COCONUT_RUNTIME_BYTEBUF_HPP
#define COCONUT_RUNTIME_BYTEBUF_HPP

namespace coconut
{ namespace runtime
{ namespace traits
{

COCONUT_CLASSFORWARD_DCL(upath)
COCONUT_CLASSFORWARD_DCL(uri)

/**
 * The bytebuf class provides methods and properties to optimize reading,
 * writing while working with binary data: a safe representation of an 
 * in-memory packed array which is mutable. It does own the underlying
 * data.
 */
COCONUT_PRIVATE class COCONUT_VISIBLE bytebuf COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.bytebuf, bytebuf)

public:
	bytebuf();
	bytebuf(const bytebuf & dat);
	bytebuf(bytebuf && dat) noexcept;
	
	bytebuf(const bytebuf & dat, bool b64dec);
	bytebuf(bytebuf && dat, bool b64dec) noexcept;
	
	bytebuf(std::size_t capacity);
	
	bytebuf(const std::uint8_t * membytes, std::size_t length, bool b64dec = false);
	bytebuf(const char * membytes, std::size_t length, bool b64dec = false);
	
	template <typename InputIterT>
	bytebuf(InputIterT && first, InputIterT && last, bool b64dec)
	: m_bytes()
	{ InputIterT it = first; while (it != last) { push_back((*it)); ++it; } if (b64dec) { b64_decode(); } }
	
	bytebuf(const std::uint16_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	bytebuf(const std::uint32_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	bytebuf(const std::uint64_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	
	bytebuf(const std::int16_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	bytebuf(const std::int32_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	bytebuf(const std::int64_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	
	template <typename InputIterT>
	bytebuf(InputIterT && first, InputIterT && last, packing_option option)
	: m_bytes()
	{ InputIterT it = first; while (it != last) { push_back((*it), option); ++it; } }
	
	template <typename InputIterT>
	bytebuf(InputIterT && first, InputIterT && last)
	: m_bytes()
	{ InputIterT it = first; while (it != last) { push_back((*it)); ++it; } }
	
	bytebuf(stream::fstream & in_binary);
	bytebuf(stream::ifstream & in_binary);
	bytebuf(stream::imstream & in_binary);
	
	bytebuf(const upath & path, bool b64dec = false);
	bytebuf(const uri & url, bool b64dec = false);
	bytebuf(const std::string & utf8_path, bool b64dec = false);
	bytebuf(const std::u16string & utf16_path, bool b64dec = false);
	
	bytebuf(stream::fstream & in_binary, std::size_t location, std::size_t length);
	bytebuf(stream::ifstream & in_binary, std::size_t location, std::size_t length);
	bytebuf(stream::imstream & in_binary, std::size_t location, std::size_t length);
	
	bytebuf(const std::string & utf8_path, std::size_t location, std::size_t length);
	bytebuf(const std::u16string & utf16_path, std::size_t location, std::size_t length);	
	~bytebuf();

public:
	COCONUT_CLASSMETHOD void unpack(const std::uint8_t (&in)[2], std::uint16_t & out, unpacking_option option);
	COCONUT_CLASSMETHOD void unpack(const std::uint8_t (&in)[4], std::uint32_t & out, unpacking_option option);
	COCONUT_CLASSMETHOD void unpack(const std::uint8_t (&in)[8], std::uint64_t & out, unpacking_option option);
	
	COCONUT_CLASSMETHOD void unpack(const std::uint8_t (&in)[2], std::int16_t & out, unpacking_option option);
	COCONUT_CLASSMETHOD void unpack(const std::uint8_t (&in)[4], std::int32_t & out, unpacking_option option);
	COCONUT_CLASSMETHOD void unpack(const std::uint8_t (&in)[8], std::int64_t & out, unpacking_option option);

	COCONUT_CLASSMETHOD void pack(const std::uint16_t & in, std::uint8_t (&out)[2], packing_option option);
	COCONUT_CLASSMETHOD void pack(const std::uint32_t & in, std::uint8_t (&out)[4], packing_option option);
	COCONUT_CLASSMETHOD void pack(const std::uint64_t & in, std::uint8_t (&out)[8], packing_option option);
	
	COCONUT_CLASSMETHOD void pack(const std::int16_t & in, std::uint8_t (&out)[2], packing_option option);
	COCONUT_CLASSMETHOD void pack(const std::int32_t & in, std::uint8_t (&out)[4], packing_option option);
	COCONUT_CLASSMETHOD void pack(const std::int64_t & in, std::uint8_t (&out)[8], packing_option option);
	
private:
	bool rb_fin(stream::fstream & in_binary);
	bool rb_fin(stream::ifstream & in_binary);
	bool rb_fin(stream::imstream & in_binary);
	
	bool rb_fin(stream::fstream & in_binary, std::size_t location, std::size_t length);
	bool rb_fin(stream::ifstream & in_binary, std::size_t location, std::size_t length);
	bool rb_fin(stream::imstream & in_binary, std::size_t location, std::size_t length);
	
	bool wb_fout(stream::fstream & out_binary) const;
	bool wb_fout(stream::ofstream & out_binary) const;
	bool wb_fout(stream::ofstream & out_binary, std::size_t location, std::size_t length) const;
	
public:
	bytebuf & operator = (const bytebuf & dat);
	int compare(const bytebuf & other_dat) const;
	
	void set(std::uint8_t v);
	void set(char v);
	
	void set(std::uint16_t v, packing_option option = packing_bigendian);
	void set(std::uint32_t v, packing_option option = packing_bigendian);
	void set(std::uint64_t v, packing_option option = packing_bigendian);
	
	void set(std::int16_t v, packing_option option = packing_bigendian);
	void set(std::int32_t v, packing_option option = packing_bigendian);
	void set(std::int64_t v, packing_option option = packing_bigendian);
	
	void set(const std::uint8_t * membytes, std::size_t length, bool b64dec = false);
	void set(const char * membytes, std::size_t length, bool b64dec = false);
	
	template <typename InputIterT>
	void set(InputIterT && first, InputIterT && last, bool b64dec)
	{ InputIterT it = first; clear(); while (it != last) { push_back((*it)); ++it; } if (b64dec) { b64_decode(); } }
	
	void set(const std::uint16_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void set(const std::uint32_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void set(const std::uint64_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	
	void set(const std::int16_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void set(const std::int32_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void set(const std::int64_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	
	template <typename InputIterT>
	void set(InputIterT && first, InputIterT && last, packing_option option)
	{ InputIterT it = first; clear(); while (it != last) { push_back((*it), option); ++it; } }
	
	void put(const std::uint8_t v, std::size_t index);
	void put(const char v, std::size_t index);
	
	const std::uint8_t at(std::size_t index) const;
	
	std::size_t size() const;
	
	std::uint8_t * raw() const;
	const std::vector<std::uint8_t> & bytes() const;
	
	bool get_raw(std::uint8_t * membytes, std::size_t length) const;
	bool get_raw(std::uint8_t * membytes, std::size_t location, std::size_t length) const;
	
	bool get_raw(char * membytes, std::size_t length) const;
	bool get_raw(char * membytes, std::size_t location, std::size_t length) const;
	
	bool get_bytes(std::vector<std::uint8_t> & bv) const;
	bool get_bytes(std::vector<std::uint8_t> & bv, std::size_t length) const;
	bool get_bytes(std::vector<std::uint8_t> & bv, std::size_t location, std::size_t length) const;
	
	void push_front(std::uint8_t v);
	void push_front(char v);
	
	void push_front(std::uint16_t v, packing_option option = packing_bigendian);
	void push_front(std::uint32_t v, packing_option option = packing_bigendian);
	void push_front(std::uint64_t v, packing_option option = packing_bigendian);
	
	void push_front(std::int16_t v, packing_option option = packing_bigendian);
	void push_front(std::int32_t v, packing_option option = packing_bigendian);
	void push_front(std::int64_t v, packing_option option = packing_bigendian);
	
	void push_front(const std::uint8_t * membytes, std::size_t length);
	void push_front(const char * membytes, std::size_t length);
	
	void push_front(const std::uint16_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void push_front(const std::uint32_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void push_front(const std::uint64_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	
	void push_front(const std::int16_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void push_front(const std::int32_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void push_front(const std::int64_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	
	void push_back(std::uint8_t v);
	void push_back(char v);
	
	void push_back(std::uint16_t v, packing_option option = packing_bigendian);
	void push_back(std::uint32_t v, packing_option option = packing_bigendian);
	void push_back(std::uint64_t v, packing_option option = packing_bigendian);
	
	void push_back(std::int16_t v, packing_option option = packing_bigendian);
	void push_back(std::int32_t v, packing_option option = packing_bigendian);
	void push_back(std::int64_t v, packing_option option = packing_bigendian);
	
	void push_back(const std::uint8_t * membytes, std::size_t length);
	void push_back(const char * membytes, std::size_t length);
	
	void push_back(const std::uint16_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void push_back(const std::uint32_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void push_back(const std::uint64_t * membytes, std::size_t length, packing_option option = packing_bigendian);

	void push_back(const std::int16_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void push_back(const std::int32_t * membytes, std::size_t length, packing_option option = packing_bigendian);
	void push_back(const std::int64_t * membytes, std::size_t length, packing_option option = packing_bigendian);

	void replace(const std::uint8_t * membytes, std::size_t location, std::size_t length);
	
	void remove(std::size_t index);
	void remove(std::size_t location, std::size_t length);
	void remove_last();
	
	void reverse();
	
	std::string to_string() const;
	std::size_t hash_code() const;
	
	std::string to_b64string(chunksplit_option option = chunksplit_none) const;
	void b64_encode(chunksplit_option option = chunksplit_none);
	void b64_decode();
	bool get_base64(std::vector<char> & out, chunksplit_option option = chunksplit_none) const;
	
	std::string hash_sha1() const;
	std::string hash_sha256() const;
	
	void clear();
	void reset();

public:
	bool write(stream::fstream & out_binary) const;
	bool write(stream::ofstream & out_binary) const;
	
	bool write(const std::string & utf8_path, bool atomically = true) const;
	bool write(const std::u16string & utf16_path, bool atomically = true) const;

public:
	const std::uint8_t & operator [] (std::size_t index) const;
	
	bytebuf & operator + (std::uint8_t v);
	bytebuf & operator += (std::uint8_t v);
	
	bytebuf & operator + (char v);
	bytebuf & operator += (char v);

private:
	typedef std::vector<std::uint8_t> container_type;
	
public:
	/* type_traits */
	
	typedef container_type::iterator iterator;
	typedef container_type::const_iterator const_iterator;

	typedef container_type::reverse_iterator reverse_iterator;
	typedef container_type::const_reverse_iterator const_reverse_iterator;

	typedef container_type::value_type value_type;
	typedef container_type::size_type size_type;
	typedef container_type::difference_type difference_type;
	
	typedef container_type::reference reference;
	typedef container_type::const_reference const_reference;
	typedef container_type::pointer pointer;
	typedef container_type::const_pointer const_pointer;
	
public:
	/* type_iterator */
	
	iterator begin();
	iterator end();
	
	const_iterator begin() const;
	const_iterator end() const;
	
	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

private:
	container_type m_bytes;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_BYTEBUF_HPP */

/* EOF */