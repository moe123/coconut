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
				const char * b_sep = " ",
				const char * w_sep = "  ",
				const char * lw_sep = " | ",
				const char * e_sep = "...",
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
						os << lw_sep;
					} else if (cnt % 4 == 0) {
						os << w_sep;
					} else {
						os << b_sep;
					}
					if (cnt > max_dump) {
						os << e_sep;
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