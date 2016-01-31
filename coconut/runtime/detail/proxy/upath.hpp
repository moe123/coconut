//
// upath.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_UPATH_HPP
#define COCONUT_RUNTIME_UPATH_HPP

namespace coconut
{
	namespace runtime
	{
		class ustring;
		
		COCONUT_PRIVATE class COCONUT_EXPORT upath COCONUT_FINAL
		{
		COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.upath, upath)
			
		public:
			upath();
			upath(const upath & path);
			upath(const ustring & path, dirsep_option option = dirsep_auto);
			upath(const std::string & str_path, encoding_option encoding = encoding_utf8, dirsep_option option = dirsep_auto);
			upath(const std::u16string & str_path, encoding_option encoding = encoding_utf16, dirsep_option option = dirsep_auto);
			virtual ~upath();
			
		public:
			upath & operator = (const upath & path);
			int compare(const upath & other_path) const;
			
			std::string to_string() const;
			
			const upath absolute(dirsep_option option = dirsep_auto) const;
			const upath basename() const;
			const upath dirname(dirsep_option option = dirsep_auto) const;
			
			const std::vector<std::string> components() const;
			
			const std::string to_utf8_string(dirsep_option option = dirsep_auto) const;
			const std::u16string to_utf16_string(dirsep_option option = dirsep_auto) const;
			
		private:
			std::vector<std::string> m_components;
		};
	}
}

#endif /* !COCONUT_RUNTIME_UPATH_HPP */

/* EOF */