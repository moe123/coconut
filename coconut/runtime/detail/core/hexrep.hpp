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
					m_start(R"()"),
					m_stop(R"()"),
					m_byte(R"( )"),
					m_word(R"(  )"),
					m_dword(R"( | )"),
					m_ellipsis(R"(...)"),
					m_max(std::numeric_limits<std::size_t>::max()),
					m_row(true)
				{ /* NOP */ }
				
				const char * m_start;
				const char * m_stop;
				const char * m_byte;
				const char * m_word;
				const char * m_dword;
				const char * m_ellipsis;
				std::size_t m_max;
				bool m_row;
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
				os << opt->m_start;
				for (; beg != end; ++beg) {
					std::uint8_t c = unsafe_cast<std::uint8_t>(*beg);
					os << std::hex << std::setw(2) << std::setfill('0') << (c & 0xff);
					++cnt;
					if (cnt % 16 == 0 && opt->m_row) {
						os << std::endl;
					} else if (cnt % 8 == 0) {
						os <<  opt->m_dword;
					} else if (cnt % 4 == 0) {
						os << opt->m_word;
					} else {
						os << opt->m_byte;
					}
					if (cnt >= opt->m_max) {
						os << opt->m_ellipsis;
						break;
					}
				}
				os << opt->m_stop;
				os.copyfmt(saved_fmt);
			}
		}
	}
}

#endif /* !COCONUT_RUNTIME_HEXREP_HPP */

/* EOF */