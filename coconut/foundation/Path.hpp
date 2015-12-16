//
// Path.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_PATH_HPP
#define COCONUT_FOUNDATION_PATH_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT Path : public Object
	{
	COCONUT_KDCL(coconut.Path, Object.Path)
		
	public:
		Path();
		Path(const Path & path);
		Path & operator = (const Path & path) = default;
		
		Path(const String & path, DirectorySeparatorOption option = DirectorySeparatorAuto);
		Path(const std::string & utf8_path, DirectorySeparatorOption option = DirectorySeparatorAuto);
		Path(const std::u16string & utf16_path, DirectorySeparatorOption option = DirectorySeparatorAuto);
		
		Path(const char * utf8_path);
		Path(const char16_t * utf16_path);
		
		virtual ~Path();
		
		COCONUT_KTOR PathPtr with();
		COCONUT_KTOR PathPtr with(const Path & path);
		COCONUT_KTOR PathPtr with(const String & path, DirectorySeparatorOption option = DirectorySeparatorAuto);
		COCONUT_KTOR PathPtr with(const std::string & utf8_path, DirectorySeparatorOption option = DirectorySeparatorAuto);
		COCONUT_KTOR PathPtr with(const std::u16string & utf16_path, DirectorySeparatorOption option = DirectorySeparatorAuto);
		COCONUT_KTOR PathPtr with(const char * utf8_path);
		COCONUT_KTOR PathPtr with(const char16_t * utf16_path);

		virtual kind_ptr copy() const
		COCONUT_FINAL_OVERRIDE;
		
		// virtual kind_ptr mutableCopy() const
		// COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const_kind_ref ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::u16string string16Value() const
		COCONUT_FINAL_OVERRIDE;
		
		const Array components() const;
		
		const Path absolute(DirectorySeparatorOption option = DirectorySeparatorAuto);
		const Path basename() const;
		const Path dirname(DirectorySeparatorOption option = DirectorySeparatorAuto) const;

		const std::string UTF8String(DirectorySeparatorOption option = DirectorySeparatorAuto) const;
		const std::u16string UTF16String(DirectorySeparatorOption option = DirectorySeparatorAuto) const;

	protected:
		friend class Array;
		friend class Data;
		friend class Dictionary;
		
	public:
		typedef runtime::upath impl_type;
	
	protected:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_PATH_HPP */

/* EOF */