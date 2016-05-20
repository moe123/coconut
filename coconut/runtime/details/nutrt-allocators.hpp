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
	template <typename T> using mallocator = std::allocator<T>;
	
	template <typename T>
	COCONUT_PRIVATE struct COCONUT_VISIBLE placement COCONUT_FINAL : public mallocator<T>
	{
		using size_type = typename mallocator<T>::size_type;
		using difference_type = typename mallocator<T>::difference_type;
		
		using pointer = typename mallocator<T>::pointer;
		using const_pointer = typename mallocator<T>::const_pointer;
		
		using reference = typename mallocator<T>::reference;
		using const_reference = typename mallocator<T>::const_reference;
		
		using value_type = typename mallocator<T>::value_type;
		
		using void_pointer = typename mallocator<void>::pointer;
		using const_void_pointer = typename mallocator<void>::const_pointer;
		
		template<typename T0>
		struct rebind { typedef placement<T0> other; };
		
#if COCONUT_DEBUG
		template <typename T0> using this_parent = mallocator<T0>;
		template <typename T0> using this_type = placement<T0>;
#endif

		placement(void_pointer p = nullptr) throw() : mallocator<T>(), m_ref(p) { /* NOP */ }
		placement(const placement & other) throw() : mallocator<T>(other) { m_ref = other.m_ref; }
		placement(placement && other) throw() : mallocator<T>(std::move(other)) { m_ref = other.m_ref; }
		~placement() throw()
		{
#if COCONUT_DEBUG
			this->~this_parent<T>();
#endif
		}

		pointer allocate(size_type n, const_void_pointer = nullptr)
		{ char * p = new (m_ref) char[n * sizeof(T)]; return weak_cast<T *>(p); }

		void deallocate(pointer p, size_type n) noexcept { /* NOP */ }

		pointer address(reference x) const noexcept { return std::addressof(x); }
		const_pointer address(const_reference x) const noexcept { return address(weak_cast<reference>(x)); }
	
	private:
#if COCONUT_DEBUG
		COCONUT_ALIGNAS(std::max_align_t) void * m_ref;
#else
		void * m_ref;
#endif
	};
	
}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ALLOCATORS_HPP */

/* EOF */