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
			struct format_option
			{
				format_option() :
					m_start_delim(""),
					m_end_delim(""),
					m_byte_sep(" "),
					m_word_sep("  "),
					m_dword_sep(" | "),
					m_ellipsis_sep("..."),
					m_max_dump(std::numeric_limits<std::size_t>::max()),
					m_row_jump(true)
				{ /* NOP */ }
				
				const char * m_start_delim;
				const char * m_end_delim;
				const char * m_byte_sep;
				const char * m_word_sep;
				const char * m_dword_sep;
				const char * m_ellipsis_sep;
				std::size_t m_max_dump;
				bool m_row_jump;
			};
			
			template <typename IterT>
			inline void format(
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
				if (!opt) { return; }
				os << opt->m_start_delim;
				for (; beg != end; ++beg) {
					std::uint8_t c = unsafe_cast<std::uint8_t>(*beg);
					os << std::hex << std::setw(2) << std::setfill('0') << (c & 0xff);
					++cnt;
					if (cnt % 16 == 0 && opt->m_row_jump) {
						os << std::endl;
					} else if (cnt % 8 == 0) {
						os <<  opt->m_dword_sep;
					} else if (cnt % 4 == 0) {
						os << opt->m_word_sep;
					} else {
						os << opt->m_byte_sep;
					}
					if (cnt >= opt->m_max_dump) {
						os << opt->m_ellipsis_sep;
						break;
					}
				}
				os << opt->m_end_delim;
				os.copyfmt(saved_fmt);
			}
		}
	}
}

#endif /* !COCONUT_RUNTIME_HEXREP_HPP */

/* EOF */