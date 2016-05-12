//
// nutrt-hexrep.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-defines.hpp>

#ifndef COCONUT_RUNTIME_HEXREP_HPP
#define COCONUT_RUNTIME_HEXREP_HPP

namespace coconut
{ namespace runtime
{ namespace hexrep
{

struct format_option
{
	format_option() :
		u_start(u8""),
		u_stop(u8""),
		u_byte(u8" "),
		u_word(u8"  "),
		u_dword(u8" | "),
		u_ellipsis(u8"..."),
		u_max(std::numeric_limits<std::size_t>::max()),
		u_row(true)
	{ /* NOP */ }
	
	const char * u_start;
	const char * u_stop;
	const char * u_byte;
	const char * u_word;
	const char * u_dword;
	const char * u_ellipsis;
	std::size_t u_max;
	bool u_row;
};
			
namespace {
	format_option default_option{};
}

template <typename IterT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void format(
	std::ostream & os,
	IterT && beg,
	IterT && end,
	format_option * opt
) {
	std::size_t cnt = 0;
	std::ios saved_fmt(nullptr);
	std::ios default_fmt(nullptr);
	saved_fmt.copyfmt(os);
	os.copyfmt(default_fmt);
	if (!opt) { opt = &default_option; }
	os << opt->u_start;
	for (; beg != end; ++beg) {
		std::uint8_t c = weak_cast<std::uint8_t>(*beg);
		os << std::hex << std::setw(2) << std::setfill('0') << (c & 0xff);
		++cnt;
		if (cnt % 16 == 0 && opt->u_row) {
			os << std::endl;
		} else if (cnt % 8 == 0) {
			os << opt->u_dword;
		} else if (cnt % 4 == 0) {
			os << opt->u_word;
		} else {
			os << opt->u_byte;
		}
		if (cnt >= opt->u_max) {
			os << opt->u_ellipsis;
			break;
		}
	}
	os << opt->u_stop;
	os.copyfmt(saved_fmt);
}

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_HEXREP_HPP */

/* EOF */