//
// Serialization.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_SERIALIZATION_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_SERIALIZATION_HPP

namespace coconut
{
	COCONUT_ABSTRACT class COCONUT_VISIBLE Serialization : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Object.Serialization, Object.Serialization)
	
	protected:
		Serialization();
		Serialization(const Serialization &) = delete;
		virtual ~Serialization();
		
	public:
		COCONUT_CLASSMETHOD OptionalReturn< Owning<Data>, Owning<Error> > dataWithCollection(const Any & collection, SerializationFormatOption format);
		COCONUT_CLASSMETHOD OptionalReturn< Owning<Any>, Owning<Error> > collectionWithData(const Data & dt, SerializationReadOption option, SerializationFormatOption format);
	};
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_SERIALIZATION_HPP */

/* EOF */