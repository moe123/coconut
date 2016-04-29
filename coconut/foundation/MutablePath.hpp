//
// MutablePath.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Path.hpp>

#ifndef COCONUT_FOUNDATION_MUTABLEPATH_HPP
#define COCONUT_FOUNDATION_MUTABLEPATH_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE MutablePath COCONUT_FINAL : public Object
	{
	COCONUT_CLASSDECLARE(coconut.MutablePath, Object.MutablePath)

	public:
		MutablePath();
		MutablePath(const MutablePath & path);
		MutablePath & operator = (const MutablePath & path) = default;
		MutablePath(const Path & path);		
		MutablePath(const String & str);
		MutablePath(const char * utf8_path);
		MutablePath(const char16_t * utf16_path);
		virtual ~MutablePath();
		
		MutablePath & append(const Path & path);
		MutablePath & appendComponents(const Array & components);
		
		MutablePath & removeLastComponent();
	};
}

#endif /* !COCONUT_FOUNDATION_MUTABLEPATH_HPP */

/* EOF */