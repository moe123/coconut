//
// locale_gui.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include "unicode/locid.h"
#include "unicode/uloc.h"

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
				char buf[ULOC_FULLNAME_CAPACITY];
			#if defined(__APPLE22__)
				// @FUTURE shortcuts avoiding all the CF cargobay.
				//
				// if $HOME/Library/Preferences/.GlobalPreferences.plist
				// load -> objectForkey(u8"AppleLocale")
				
				// else if $HOME/Safe Preferences/.GlobalPreferences.plist
				// load -> objectForkey(u8"AppleLocale")
				
				CFLocaleRef _loc = CFLocaleCopyCurrent();
				CFStringRef _id = static_cast<CFStringRef>(CFLocaleGetValue(_loc, kCFLocaleIdentifier));
				if (CFStringGetCString(_id, buf, LOC_BUF_SIZE, kCFStringEncodingUTF8)) {
					id = buf;
				} else {
					id = u8"en_US_POSIX";
				}
				CFRelease(_loc);
			#elif defined(__MICROSOFT__)
				LCID lcid = GetUserDefaultLCID();
				std::int32_t len = uloc_getLocaleForLCID(lcid, buf, LOC_BUF_SIZE, &status);
				buf[len] = 0;
				if (U_SUCCESS(status) && len) {
					id = buf;
				} else {
					id = u8"en_US_POSIX";
				}
			#else
				char * q;
				std::vector<std::string> lc;
				
				setlocale(LC_ALL, "");
				
				q = std::getenv("LANG");
				lc.push_back((q != NULL ? q : ""));
				
				q = setlocale(LC_ALL, NULL);
				lc.push_back((q != NULL ? q : ""));
				
				q = setlocale(LC_CTYPE, NULL);
				lc.push_back((q != NULL ? q : ""));
				
				q = setlocale(LC_COLLATE, NULL);
				lc.push_back((q != NULL ? q : ""));
				
				q = setlocale(LC_MESSAGES, NULL);
				lc.push_back((q != NULL ? q : ""));
				
				q = setlocale(LC_MONETARY, NULL);
				lc.push_back((q != NULL ? q : ""));
				
				q = setlocale(LC_NUMERIC, NULL);
				lc.push_back((q != NULL ? q : ""));
				
				q = setlocale(LC_TIME, NULL);
				lc.push_back((q != NULL ? q : ""));
				
				for(std::vector<std::string>::const_iterator it = lc.begin(); it != lc.end(); ++it) {
					if ((*it).size() >= 5) {
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
					id = u8"en_US_POSIX";
				}
			#endif
				return id;
			}
		}
	}
}

/* EOF */