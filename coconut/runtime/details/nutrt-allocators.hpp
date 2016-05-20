//
// nutrt-allocators.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_ALLOCATORS_HPP
#define COCONUT_RUNTIME_ALLOCATORS_HPP

namespace coconut
{ namespace runtime
{ namespace allocators
{
	template <typename InnerT> using mallocator = std::allocator<InnerT>;
	
	template <typename T>
	COCONUT_PRIVATE struct COCONUT_VISIBLE placement COCONUT_FINAL : public mallocator<T>
	{
#if COCONUT_DEBUG
		template <typename T0> using this_parent = mallocator<T0>;
#endif

		placement(void * p = nullptr) throw() : mallocator<T>(), m_stackmem(p) { /* NOP */ }
		placement(const placement & other) throw() : mallocator<T>(other) { m_stackmem = other.m_stackmem; }
		placement(placement && other) throw() : mallocator<T>(std::move(other)) { m_stackmem = other.m_stackmem; }
		~placement() throw()
		{
#if COCONUT_DEBUG
			this->~this_parent<T>();
#endif
		}

		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T * pointer;
		typedef const T * const_pointer;
		typedef T & reference;
		typedef const T & const_reference;
		typedef T value_type;

		template<typename T1>
		struct rebind { typedef placement<T1> other; };

		pointer allocate(size_type n, mallocator<void>::const_pointer = nullptr)
		{ char * dummy = ::new (m_stackmem) char[n * sizeof(T)]; return weak_cast<T *>(dummy); }

		void deallocate(pointer p, size_type n) noexcept { /* NOP */ }

		pointer address(reference x) const noexcept { return std::addressof(x); }
		const_pointer address(const_reference x) const noexcept { return address(weak_cast<reference>(x)); }
	
	private:
		COCONUT_ALIGNAS(sizeof(T *)) void * m_stackmem;
	};
	
}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ALLOCATORS_HPP */

/* EOF */