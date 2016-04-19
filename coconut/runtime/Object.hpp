//
// Object.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#if defined(COCONUT_HAVE_PRAGMA_ONCE) && COCONUT_HAVE_PRAGMA_ONCE
	#pragma once
#endif

#include <coconut/runtime/Types.hpp>
#include <coconut/runtime/Features.hpp>
#include <coconut/runtime/JobBroker.hpp>
#include <coconut/runtime/Printifier.hpp>
#include <coconut/runtime/ByteOrder.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_OBJECT_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_OBJECT_HPP

namespace coconut
{
	COCONUT_PROTECTED class COCONUT_ABSTRACT COCONUT_VISIBLE Object : public Any
	{
	COCONUT_CLASSDECLARE(coconut.Object, Any.Object)
		
	public:
	/*
	* Bridge adapter late and early runtime bindings.
	*/
		Object();
		virtual ~Object();
		
	protected:
		Object(const Object & obj);
		Object & operator = (const Object & obj);
		explicit Object(ClassKind kind);
	
	public:
		COCONUT_CLASSMETHOD Owning<Any> copyObject(const Any & obj, CopyOption option);
		COCONUT_CLASSMETHOD Owning<Any> copyObject(const Owning<Any> & obj, CopyOption option);
	
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
		
	private:
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