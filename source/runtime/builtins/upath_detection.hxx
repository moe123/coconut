//
// upath_detection.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

namespace coconut
{
	namespace runtime
	{
		namespace builtins
		{
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool upath_iswin(std::string & utf8_in, std::string & utf8_drive, dirsep_option & dsep) {
				try {
					std::smatch match_win;
					std::ssub_match sub_match;
					std::regex regex_win{R"(^([a-zA-z]:)(\\|/)(.*)$)"};
					if (std::regex_match(utf8_in, match_win, regex_win)) {
						if (match_win.size() == 4) {
							std::smatch match_ntfs;
							sub_match = match_win[1];
							utf8_drive.assign(sub_match.str());
							
							sub_match = match_win[2];
							if (sub_match.str() == "/") {
								dsep = dirsep_whack;
							} else {
								dsep = dirsep_slack;
							}
							
							regex_win.assign(R"(^[a-zA-Z]:(\\|/)(((?![<>:\"/\\|?*]).)*[^ ](\\|/))*((?![<>:\"/\\|?*]).)*[^ ](\\|/)?$)");
							if (std::regex_match(utf8_in, match_ntfs, regex_win)) {
								return true;
							}
						}
					}
				} catch (std::regex_error e) { /* NOP */ }
				
				return false;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			dirsep_option upath_validate(std::string & utf8_in, std::string & utf8_root, bool & abs, bool & good)
			{
				dirsep_option dsep = dirsep_none;
				abs = false;
				good = false;
				if (utf8_in.size()) {
					try {
						std::smatch match_win;
						std::smatch match_posix;
						std::ssub_match sub_match;
						std::regex regex_win{R"(^([a-zA-z]:)(\\|/)(.*)$)"};
						std::regex regex_posix{R"(^(/)?([^/\0]+(/)?)+$)"};
						if (std::regex_match(utf8_in, match_win, regex_win)) {
							if (match_win.size() == 4) {
								std::smatch match_ntfs;
								
								abs = true;
								sub_match = match_win[1];
								utf8_root.assign(sub_match.str());
								
								sub_match = match_win[2];
								if (sub_match.str() == "/") {
									dsep = dirsep_whack;
								} else {
									dsep = dirsep_slack;
								}
								
								regex_win.assign(R"(^[a-zA-Z]:(\\|/)(((?![<>:\"/\\|?*]).)*[^ ](\\|/))*((?![<>:\"/\\|?*]).)*[^ ](\\|/)?$)");
								if (std::regex_match(utf8_in, match_ntfs, regex_win)) {
									good = true;
								}
							}
						} else if (std::regex_match(utf8_in, match_posix, regex_posix)) {
							sub_match = match_posix[1];
							utf8_root.assign(sub_match.str());
							if (sub_match.str() == "/") {
								abs = true;
								good = true;
							}
							dsep = dirsep_whack;
						}
						if (dsep == dirsep_none) {
							std::size_t n0 = std::count(utf8_in.cbegin(), utf8_in.cend(), '\\');
							std::size_t n1 = std::count(utf8_in.cbegin(), utf8_in.cend(), '/');
							dsep = (n1 >= n0) ? dirsep_whack : dirsep_slack;
						}
					} catch (std::regex_error e) { /* NOP */ }
				}
				return dsep;
			}
		}
	}
}

/* EOF */