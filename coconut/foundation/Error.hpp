//
// Error.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Dictionary.hpp>
#include <coconut/foundation/String.hpp>

#ifndef COCONUT_FOUNDATION_ERROR_HPP
#define COCONUT_FOUNDATION_ERROR_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Error COCONUT_FINAL : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Error, Object.Error)
		
	public:
		Error();
		Error(const Error & err);
		Error & operator = (const Error & err) = default;
		Error(Error && err) noexcept;
		Error(std::size_t code);
		Error(const String & domain, std::size_t code);
		Error(const String & domain, std::size_t code, const Dictionary & userInfo);
		virtual ~Error();
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		std::size_t code() const;
		const String domain() const;
		const Dictionary userInfo() const;
		
	public:
		typedef std::tuple<String, std::size_t, Dictionary> impl_trait;
		
	protected:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_ERROR_HPP */

/* EOF */