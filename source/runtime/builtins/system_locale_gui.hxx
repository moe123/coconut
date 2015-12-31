//
// system_locale_gui.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include "unicode/locid.h"
#include "unicode/uloc.h"
#define LOC_BUF_SIZE ULOC_FULLNAME_CAPACITY

namespace coconut
{
	namespace runtime
	{
		namespace builtins
		{
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::string locale_gui_id()
			{
				std::string id;
				char buf[LOC_BUF_SIZE];
			#if defined(__APPLE__)
				CFLocaleRef _loc = CFLocaleCopyCurrent();
				CFStringRef _id = static_cast<CFStringRef>(CFLocaleGetValue(_loc, kCFLocaleIdentifier));
				if (CFStringGetCString(_id, buf, LOC_BUF_SIZE, kCFStringEncodingUTF8)) {
					id = buf;
				} else {
					id = u8"en_US";
				}
				CFRelease(_loc);
			#elif defined(__MICROSOFT__)
				LCID lcid = GetUserDefaultLCID();
				std::int32_t len = uloc_getLocaleForLCID(lcid, buf, LOC_BUF_SIZE, &status);
				buf[len] = 0;
				if (U_SUCCESS(status) && len) {
					id = buf;
				} else {
					id = u8"en_US";
				}
			#else
				std::vector<std::string> lc;
				setlocale(LC_ALL, "");
				char * lang = std::getenv("LANG");
				
				lc.push_back((lang != NULL ? lang : ""));
				lc.push_back(setlocale(LC_ALL, NULL));
				lc.push_back(setlocale(LC_CTYPE, NULL));
				lc.push_back(setlocale(LC_COLLATE, NULL));
				lc.push_back(setlocale(LC_MESSAGES, NULL));
				lc.push_back(setlocale(LC_MONETARY, NULL));
				lc.push_back(setlocale(LC_NUMERIC, NULL));
				lc.push_back(setlocale(LC_TIME, NULL));
				
				for(vector<string>::const_iterator i = lc.begin(); i != lc.end(); ++i) {
					if ((*it).size() >=5 ) {
						std::size_t found = (*it).find_first_of(".");
						if (found != std::string::npos) {
							id = (*it).substr (0, found);
						} else {
							id = (*it);
						}
						break;
					}
				}
				if (!id.size()) {
					id = uloc_getDefault();
				}
				if (id.size() < 5) {
					id = u8"en_US";
				}
			#endif
				return id;
			}
		}
	}
}

/* EOF */