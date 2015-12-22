//
// Object.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Features.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_OBJECT_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_OBJECT_HPP

namespace coconut
{
	COCONUT_ABSTRACT class COCONUT_EXPORT Object : public runtime::nucleus
	{
	COCONUT_KDCL(coconut.Object, nucleus.Object)
		
	protected:
	/*
	* Bridge adapter late and early runtime bindings @see nucleus.
	*/
		Object();
		Object(const Object & obj);
		Object & operator = (const Object & obj);
		explicit Object(ClassKind kind);
		virtual ~Object();
	
	public:
		COCONUT_KTOD Owning<Any> copyObject(const Any & ref, CopyOption option);
		COCONUT_KTOD Owning<Any> copyObject(const Owning<Any> & ptr, CopyOption option);
		
	public:
	/*
	* iKeyValueCoding compliant.
	*/
		virtual Owning<Any> valueForKey(const std::string & utf8_key) const
		COCONUT_OVERRIDE;
		
		virtual void setValueForKey(Owning<Any> ptr, const std::string & utf8_key)
		COCONUT_OVERRIDE;
		
		virtual Owning<Any> valueForSelectorKey(const std::string & utf8_selkey, Owning<Any> arg = {}) const
		COCONUT_OVERRIDE;
		
	protected:
	/*
	* iKeyValueCoding collection operators.
	*/
		Owning<Any> sum(const std::string & utf8_key) const;
		Owning<Any> min(const std::string & utf8_key) const;
		Owning<Any> max(const std::string & utf8_key) const;
		Owning<Any> avg(const std::string & utf8_key) const;
		
		Owning<Any> distinctUnionOfObjects(const std::string & utf8_key) const;
		Owning<Any> unionOfObjects(const std::string & utf8_key) const;
		Owning<Any> distinctUnionOfArrays(const std::string & utf8_key) const;
		Owning<Any> distinctUnionOfOrderedSets(const std::string & utf8_key) const;
		Owning<Any> distinctUnionOfSets(const std::string & utf8_key) const;
		Owning<Any> unionOfArrays(const std::string & utf8_key) const;
		Owning<Any> unionOfOrderedSets(const std::string & utf8_key) const;
		Owning<Any> unionOfSets(const std::string & utf8_key) const;
	};
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_OBJECT_HPP */

/* EOF */