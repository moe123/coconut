//
// Serialization.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_SERIALIZATION_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_SERIALIZATION_HPP

namespace coconut
{
	COCONUT_ABSTRACT class COCONUT_EXPORT Serialization : public Object
	{
	COCONUT_KDCL(coconut.Object.Serialization, Object.Serialization)
	
	protected:
		Serialization();
		Serialization(const Serialization &) = delete;
		virtual ~Serialization();
		
	public:
		COCONUT_KTOD OptionalReturn<DataPtr, ErrorPtr> dataWithCollection(const Any & collection, SerializationFormatOption format);
		COCONUT_KTOD OptionalReturn<Owning<Any>, ErrorPtr> collectionWithData(const Data & dt, SerializationReadOption option, SerializationFormatOption format);
	};
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_SERIALIZATION_HPP */

/* EOF */