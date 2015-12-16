//
// Object.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Types.hpp>

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
		COCONUT_KTOD kind_ptr copyObject(const_kind_ref ref, CopyOption option);
		COCONUT_KTOD kind_ptr copyObject(const_kind_ptr & ptr, CopyOption option);
		
	public:
	/*
	* iKeyValueCoding compliant.
	*/
		virtual kind_ptr valueForKey(const std::string & utf8_key) const
		COCONUT_OVERRIDE;
		
		virtual void setValueForKey(kind_ptr ptr, const std::string & utf8_key)
		COCONUT_OVERRIDE;
		
		virtual kind_ptr valueForSelectorKey(const std::string & utf8_selkey, kind_ptr arg = {}) const
		COCONUT_OVERRIDE;
		
	protected:
	/*
	* iKeyValueCoding collection operators.
	*/
		kind_ptr sum(const std::string & utf8_key) const;
		kind_ptr min(const std::string & utf8_key) const;
		kind_ptr max(const std::string & utf8_key) const;
		kind_ptr avg(const std::string & utf8_key) const;
		
		kind_ptr distinctUnionOfObjects(const std::string & utf8_key) const;
		kind_ptr unionOfObjects(const std::string & utf8_key) const;
		kind_ptr distinctUnionOfArrays(const std::string & utf8_key) const;
		kind_ptr distinctUnionOfOrderedSets(const std::string & utf8_key) const;
		kind_ptr distinctUnionOfSets(const std::string & utf8_key) const;
		kind_ptr unionOfArrays(const std::string & utf8_key) const;
		kind_ptr unionOfOrderedSets(const std::string & utf8_key) const;
		kind_ptr unionOfSets(const std::string & utf8_key) const;
	};
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_OBJECT_HPP */

/* EOF */