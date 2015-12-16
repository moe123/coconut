//
// Error.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Dictionary.hpp>
#include <coconut/foundation/String.hpp>

#ifndef COCONUT_FOUNDATION_ERROR_HPP
#define COCONUT_FOUNDATION_ERROR_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT Error : public Object
	{
	COCONUT_KDCL(coconut.Error, Object.Error)
		
	public:
		Error();
		Error(const Error & err);
		Error & operator = (const Error & err) = default;
		
		Error(Error && err);
		
		Error(std::size_t code);
		Error(const String & domain, std::size_t code);
		Error(const String & domain, std::size_t code, const Dictionary & userInfo);
		
		virtual ~Error();
		
		COCONUT_KTOR ErrorPtr with();
		COCONUT_KTOR ErrorPtr with(const Error & err);
		COCONUT_KTOR ErrorPtr with(Error && err);
		COCONUT_KTOR ErrorPtr with(std::size_t code);
		COCONUT_KTOR ErrorPtr with(const String & domain, std::size_t code);
		COCONUT_KTOR ErrorPtr with(const String & domain, std::size_t code, const Dictionary & userInfo);

		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual kind_ptr copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const_kind_ref ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		std::size_t code() const;
		const String domain() const;
		const Dictionary userInfo() const;

	public:
		friend inline std::ostream & operator << (std::ostream & os, const ErrorPtr ptr)
		{ if (ptr) { os << ptr->stringValue(); } return os; }
		
	public:
		typedef std::tuple<String, std::size_t, Dictionary> impl_type;
		
	protected:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_ERROR_HPP */

/* EOF */