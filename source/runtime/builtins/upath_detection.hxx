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
			bool upath_isposix(const std::string & utf8_in, std::string & utf8_drive, dirsep_option & dsep, bool & isabs)
			{
				try {
					std::smatch match_posix;
					std::ssub_match sub_match;
					dsep = dirsep_none;
					std::regex regex_posix{R"(^(/)?([^/\0]+(/)?)+$)"};
					if (std::regex_match(utf8_in, match_posix, regex_posix)) {
						sub_match = match_posix[1];
						utf8_drive.assign(sub_match.str());
						if (sub_match.str() == "/") {
							isabs = true;
						}
						dsep = dirsep_whack;
					}
				} catch (std::regex_error e) { /* NOP */ }
				
				return false;
			}
				
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool upath_isntfs(const std::string & utf8_in, std::string & utf8_drive, dirsep_option & dsep, bool & popfirst, bool & isabs)
			{
				try {
					std::smatch match_win;
					std::ssub_match sub_match;
					dsep = dirsep_none;
					popfirst = false;
					isabs = false;
					std::regex regex_win{R"(^(\\|/|)([a-zA-z]:)(\\|/)(.*)$)"};
					std::regex regex_win_rel{R"(^(\\)?([^\\\0]+(\\)?)+$)"};
					if (std::regex_match(utf8_in, match_win, regex_win)) {
						if (match_win.size() == 5) {
							std::smatch match_ntfs;
							
							isabs = true;
							
							sub_match = match_win[1];
							if (sub_match.str().size()) {
								popfirst = true;
							}
							
							sub_match = match_win[2];
							utf8_drive.assign(sub_match.str());
							
							sub_match = match_win[3];
							if (sub_match.str() == "/") {
								dsep = dirsep_whack;
							} else {
								dsep = dirsep_slack;
							}
							
							regex_win.assign(R"(^(\\|/|)[a-zA-Z]:(\\|/)(((?![<>:\"/\\|?*]).)*[^ ](\\|/))*((?![<>:\"/\\|?*]).)*[^ ](\\|/)?$)");
							if (std::regex_match(utf8_in, match_ntfs, regex_win)) {
								return true;
							}
						}
					} else if (std::regex_match(utf8_in, match_win, regex_win_rel)) {
						dsep = dirsep_slack;
						return true;
					}
				} catch (std::regex_error e) { /* NOP */ }
				
				return false;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			dirsep_option upath_match(std::string & utf8_in, std::string & utf8_root, bool & isabs)
			{
				dirsep_option dsep = dirsep_none;
				isabs = false;
				if (utf8_in.size()) {
					bool popfirst = false;
					if (upath_isntfs(utf8_in, utf8_root, dsep, popfirst, isabs)) {
						if (popfirst) {
							utf8_in.erase(0, 1);
							if (dirsep_slack == dsep && utf8_in.back() == '\\') {
								utf8_in.pop_back();
							} else if (dirsep_whack == dsep && utf8_in.back() == '/') {
								utf8_in.pop_back();
							}
						}
					} else if (upath_isposix(utf8_in, utf8_root, dsep, isabs)) {
						if (utf8_in.back() == '/') {
							utf8_in.pop_back();
						}
					}
				}
				return dsep;
			}
		}
	}
}

/* EOF */