//
// hexrep.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/defines.hpp>

#ifndef COCONUT_RUNTIME_HEXREP_HPP
#define COCONUT_RUNTIME_HEXREP_HPP

namespace coconut
{
	namespace runtime
	{
		namespace hexrep
		{
			template <typename IterInT>
			inline void dump(
				std::ostream & os,
				IterInT && beg,
				IterInT && end,
				std::size_t max_dump = std::numeric_limits<std::size_t>::max(),
				std::string ellipses = "...",
				std::string byte_sep = " ",
				std::string halfword_sep = "  ",
				std::string word_sep = " | ",
				bool row_jump = true
			) {
				std::size_t cnt = 0;
				std::ios ios_fmt(nullptr);
				ios_fmt.copyfmt(os);
				for (; beg != end; ++beg) {
					std::uint8_t c = unsafe_cast<std::uint8_t>(*beg);
					os << std::hex << std::setw(2) << std::setfill('0') << (c & 0xff);
					++cnt;
					if (cnt % 16 == 0 && row_jump) {
						os << std::endl;
					} else if (cnt % 8 == 0) {
						os << word_sep;
					} else if (cnt % 4 == 0) {
						os << halfword_sep;
					} else {
						os << byte_sep;
					}
					if (cnt > max_dump) {
						os << ellipses;
						break;
					}
				}
				if (row_jump) {
					os << std::endl;
				}
				os.copyfmt(ios_fmt);
			}
		}
	}
}

#endif /* !COCONUT_RUNTIME_HEXREP_HPP */

/* EOF */