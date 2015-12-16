//
// coconut_test_attrs.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation.hpp>

static inline void test_attr_and_custom(void)
{
	using namespace coconut;
	
	// unlike in cocoa, you can't extend from an Object
	// class directly, you must use a proxy-object class.
	// usually foundation types are not to be extended.
	
	// attributes are key-value pair dynamically added to a container:
	//   - where key is a std::string, value is a ref-counted kind_ptr
	//   - key must be prefixed with the $ sign
	//   - they can be only set/get thru the KVC interface.
	//   - this extension must be used carefully and only when necessary, e.g this is greedy.
	
	
	class Container;
	typedef ptr_declare<Container> ContainerPtr;
	
	class Container final : public Proxy
	{
	public:
		Container() : Proxy() {}
		Container(const Container & other) : Proxy(other) { /* super class conveying attributes */ }
		virtual ~Container() {}
		
	// ref-counted ctors
		static ContainerPtr with()
		{ return ptr_create<Container>(); }
		
		static ContainerPtr with(const Container & other)
		{ return ptr_create<Container>(other); }
	
	// copyable
		virtual kind_ptr copy() const override final
		{ return ptr_create<Container>(*this); }

	};
	
	ContainerPtr c = Container::with();
	
	c->setValueForKey(
		String::with(u8"Robert"),
		u8"$firstname"
	);
	
	c->setValueForKey(
		String::with(u8"Johan"),
		u8"$lastname"
	);
	
	std::cerr << "+ firstname : " << c->valueForKey(u8"$firstname") << std::endl;
	std::cerr << "+ lastname : " << c->valueForKey(u8"$lastname") << std::endl;
	
	class Person;
	
	// declaring a ref-counted pointer to Person.
	typedef ptr_declare<Person> PersonPtr;
	
	class Person : public Proxy
	{
	public:
		Person() = delete;
		Person(const Person & p) :
			Proxy()
		{
			setValueForKey(
				p.valueForKey(u8"$firstname"),
				u8"$firstname"
			);
			setValueForKey(
				p.valueForKey(u8"$lastname"),
				u8"$lastname"
			);
			setValueForKey(
				p.valueForKey(u8"$fullname"),
				u8"$fullname"
			);
			setValueForKey(
				p.valueForKey(u8"$age"),
				u8"$age"
			);
		}
		
		explicit Person
		(
			const std::string & firstname,
			const std::string & lastname,
			std::size_t age
		) : Proxy()
		{
			setValueForKey(
				String::with(firstname),
				u8"$firstname"
			);
			setValueForKey(
				String::with(lastname),
				u8"$lastname"
			);
			setValueForKey(
				String::with(firstname + u8" " + lastname),
				u8"$fullname"
			);
			setValueForKey(
				Number::with(age),
				u8"$age"
			);
		}
		
		// `with` constructor is a convention which must be respected.
		static PersonPtr with
		(
			const std::string & firstname,
			const std::string & lastname,
			std::size_t age
		)
		{
			// creating and returning a ref-counted pointer
			return ptr_create<Person>(firstname, lastname, age);
		}
		
		virtual kind_ptr copy() const override final
		{
			// making this object copyable, overloading.
			// creating and returning a ref-counted pointer
			return ptr_create<Person>(*this);
		}
		
		/**
		 * implementing a getter interface
		 */
		const std::string lastname() const
		{
			// returning std::string on an Object (String)
			auto v = valueForKey(u8"$lastname");
			// if (v && v->isMemberOf(String{})) {
			if (v && v->isMemberOf(StringClass)) {
				return v->stringValue();
			}
			throw;
			return u8"";
		}
		
		std::size_t age() const
		{
			// returning std::size_t on an Object (Number)
			auto v = valueForKey(u8"$age");
			if (v && v->isMemberOf(NumberClass)) {
				return v->unsignedLongLongValue();
			}
			throw;
			return 0ULL;
		}
		
		/**
		 * implementing a setter interface
		 */
		void setLastname(const std::string & lastname)
		{
			setValueForKey(String::with(lastname), u8"$lastname");
		}
		
		void setAge(std::size_t age)
		{
			setValueForKey(Number::with(age), u8"$age");
		}
		
		virtual ~Person() {}
	};
	
	Person bill(u8"William", u8"Doe", 20);
	{
		std::cerr << "+ bill lastname : " << bill.lastname() << std::endl;
		std::cerr << "+ bill age : " << bill.age() << std::endl;
	}
}
/* EOF */