//
// MutablePath.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Path.hpp>

#ifndef COCONUT_FOUNDATION_MUTABLEPATH_HPP
#define COCONUT_FOUNDATION_MUTABLEPATH_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT MutablePath COCONUT_FINAL : public Object
	{
	COCONUT_KDCL(coconut.MutablePath, Object.MutablePath)

	public:
		MutablePath();
		MutablePath(const MutablePath & path);
		MutablePath(const Path & path);
		MutablePath(const String & str, DirectorySeparatorOption = DirectorySeparatorAuto);
		MutablePath(const std::string & str, StringEncodingOption encoding = StringEncodingUTF8, DirectorySeparatorOption separator = DirectorySeparatorAuto);
		MutablePath(const std::u16string & str, StringEncodingOption encoding = StringEncodingUTF16, DirectorySeparatorOption separator = DirectorySeparatorAuto);
		virtual ~MutablePath();
		
		COCONUT_KTOR Owning<Path> with();
		COCONUT_KTOR Owning<Path> with(const MutablePath & path);
		COCONUT_KTOR Owning<Path> with(const Path & path);
		COCONUT_KTOR Owning<Path> with(const String & str, DirectorySeparatorOption separator = DirectorySeparatorAuto);
		COCONUT_KTOR Owning<Path> with(const std::string & str, StringEncodingOption encoding = StringEncodingUTF8, DirectorySeparatorOption separator = DirectorySeparatorAuto);
		COCONUT_KTOR Owning<Path> with(const std::u16string & str, StringEncodingOption encoding = StringEncodingUTF16, DirectorySeparatorOption separator = DirectorySeparatorAuto);
		COCONUT_KTOR Owning<Path> with(const std::u32string & str, StringEncodingOption encoding = StringEncodingUTF32, DirectorySeparatorOption separator = DirectorySeparatorAuto);
		
		void append(const MutablePath & path);
		void append(const Path & path);
		void append(const String & component);
		void append(const std::string & str, StringEncodingOption encoding = StringEncodingUTF8);
		void append(const std::u16string & str, StringEncodingOption encoding = StringEncodingUTF16);
		void append(const Array & components);
		
		void removeLastComponent();
	};
}

#endif /* !COCONUT_FOUNDATION_MUTABLEPATH_HPP */

/* EOF */