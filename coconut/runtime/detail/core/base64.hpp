//
// base64.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/defines.hpp>

#ifndef COCONUT_RUNTIME_BASE64_HPP
#define COCONUT_RUNTIME_BASE64_HPP

namespace coconut {
	namespace runtime {
		namespace base64 {

namespace
{
	struct lookup_table
	{
		const char ascii[64] =
		{
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
			'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
			'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
			'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
			'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
			'w', 'x', 'y', 'z', '0', '1', '2', '3',
			'4', '5', '6', '7', '8', '9', '+', '/'
		};
		
		const char * ascii_beg = ascii;
		const char * ascii_end = ascii + sizeof(ascii);
	
		const char bin[128] =
		{
			-1, -1, -1, -1, -1, -1, -1, -1, // 0
			-1, -1, -1, -1, -1, -1, -1, -1, // 8
			-1, -1, -1, -1, -1, -1, -1, -1, // 16
			-1, -1, -1, -1, -1, -1, -1, -1, // 24
			-1, -1, -1, -1, -1, -1, -1, -1, // 32
			-1, -1, -1, 62, -1, -1, -1, 63, // 40
			52, 53, 54, 55, 56, 57, 58, 59, // 48
			60, 61, -1, -1, -1,  0, -1, -1, // 56
			-1,  0,  1,  2,  3,  4,  5,  6, // 64
			7,  8,  9, 10, 11, 12, 13, 14,  // 72
			15, 16, 17, 18, 19, 20, 21, 22, // 80
			23, 24, 25, -1, -1, -1, -1, -1, // 88
			-1, 26, 27, 28, 29, 30, 31, 32, // 96
			33, 34, 35, 36, 37, 38, 39, 40, // 104
			41, 42, 43, 44, 45, 46, 47, 48, // 112
			49, 50, 51, -1, -1, -1, -1, -1  // 120
		};
	};
}
			
namespace {
	const lookup_table lt{};
}

// //////////////////////////////////////////////////////////
// @based on base64.hpp, base64.cpp
// Copyright (C) 2002 Ryan Petrie. All rights reserved.
// @see http://www.flipcode.com/archives/Base64_Encoder_Decoder.shtml
//
			
template <typename IterInT, typename IterOutT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void encode(IterInT && beg, IterInT && end, IterOutT && out, chunksplit_option option = chunksplit_none)
{
	IterInT it = beg;
	std::size_t chunk_size = 0, line_size = 0;
	std::int32_t bytes = 0;
	bool have_cr = false, have_lf = false;
	
	switch (option)
	{
		case chunksplit_64crlf :
			chunk_size = 64;
			have_cr = true;
			have_lf = true;
			break;
		case chunksplit_64lf :
			chunk_size = 64;
			have_lf = true;
			break;
		case chunksplit_76crlf :
			chunk_size = 76;
			have_cr = true;
			have_lf = true;
			break;
		case chunksplit_76lf :
			chunk_size = 76;
			have_lf = true;
			break;
	}
	
	do {
		std::uint32_t input = 0;
		bytes = 0;
		for (; (bytes < 3) && (it != end); ++bytes, ++it) {
			input <<= 8; input += static_cast<std::uint8_t>(*it);
		}
		std::int32_t bits = bytes * CHAR_BIT;
		while (bits > 0) {
			bits -= 6;
			const std::uint8_t index = ((bits < 0) ? input << -bits : input >> bits) & 0x3F;
			*out = lt.ascii[index]; ++out;
			if (chunk_size) { ++line_size; }
		}
		if (line_size >= chunk_size) {
			if (have_cr) { *out = 13; ++out; }
			if (have_lf) { *out = 10; ++out; }
			line_size = 0;
		}
	} while (bytes == 3);

	if (bytes > 0) {
		for (std::int32_t i = bytes; i < 3; ++i) {
			*out = '=';
			++out;
		}
	}
}

template <typename IterInT, typename IterOutT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void decode(IterInT && beg, IterInT && end, IterOutT && out)
{
	IterInT it = beg;
	std::int32_t chars;
	
	do {
		char input[4] = { 0, 0, 0, 0 };
		chars = 0;
		while ((chars < 4) && (it != end)) {
			char c = unsafe_cast<char>(*it);
			if (c == '=') { break; } ++it;
			//if (c == 13 || c == 10) { continue; }
			if (std::find(lt.ascii_beg, lt.ascii_end, c) != lt.ascii_end) {
				input[chars] = lt.bin[c]; chars++;
			}
		}
		if (chars >= 2) {
			*out = (input[0] << 2) + (input[1] >> 4); ++out;
			if (chars >= 3) {
				*out = (input[1] << 4) + (input[2] >> 2); ++out;
				if (chars >= 4) {
					*out = (input[2] << 6) + input[3]; ++out;
				}
			}
		}
	} while (chars == 4);
}

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_BASE64_HPP */

/* EOF */