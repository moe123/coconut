//
// URL.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_URL_HPP
#define COCONUT_FOUNDATION_URL_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE URL COCONUT_FINAL : public Object
	{
	COCONUT_CLASSDECLARE(coconut.URL, Object.URL)
		
	public:
		URL();
		URL(const URL & url);
		URL & operator = (const URL & url) = default;
		URL(URL && url) noexcept;
		URL(const Path & path);
		URL(const String & in);
		URL(const String & in, const URL & base_url);
		URL(const String & scheme, const String & host, const String & path);
		URL(const char * utf8_str);
		virtual ~URL();
		
		COCONUT_CLASSMETHOD const String percentEscapesEncode(const String & in, bool space_as_plus = false);
		COCONUT_CLASSMETHOD const String percentEscapesDecode(const String & in, bool plus_as_space = false);
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		bool isFileURL() const;
		
		const URL normalizedURL() const;
		
		const String specifier() const;
		const String scheme() const;
		const String host() const;
		std::size_t port() const;
		const String user() const;
		const String password() const;
		const String path() const;
		const String parameter() const;
		const String query() const;
		const String fragment() const;
		
		const Dictionary queryParameters() const;
		const Path fileSystemRepresentation() const;
	
	protected:
		friend class Array;
		friend class Data;
		friend class Dictionary;
		
	protected:
		typedef runtime::traits::uri impl_trait;
		
	private:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_URL_HPP */

/* EOF */