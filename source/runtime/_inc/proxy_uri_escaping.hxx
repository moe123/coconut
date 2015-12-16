//
// proxy_uri_escaping.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

namespace coconut
{
	namespace runtime
	{
		namespace _inc
		{
		__COCONUT_BEGIN_DECLS
			#include "uriparser/Uri.h"
		__COCONUT_END_DECLS
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::string uri_escape(const std::string & in, bool space_as_plus)
			{
				std::string result;
				std::vector<char> vecbuf(in.size() * 6 + 1);
				if (uriEscapeA(in.c_str(), vecbuf.data(), space_as_plus ? URI_TRUE : URI_FALSE, URI_FALSE)) {
					result.assign(vecbuf.data());
					if (result.back() == '\0') { result.pop_back(); }
				} else {
					result.assign(in);
				}
				vecbuf.clear();
				return result;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::string uri_unescape(const std::string & in, bool plus_as_space)
			{
				std::string result;
				std::vector<char> vecbuf;
				vecbuf.assign(in.begin(), in.end());
				vecbuf.push_back('\0');
				if (uriUnescapeInPlaceExA(vecbuf.data(), plus_as_space ? URI_TRUE : URI_FALSE, URI_BR_TO_LF)) {
					result.assign(vecbuf.data());
					if (result.back() == '\0') { result.pop_back(); }
				} else {
					result.assign(in);
				}
				vecbuf.clear();
				return result;
			}
		}
	}
}

/* EOF */