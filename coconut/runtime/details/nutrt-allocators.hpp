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
	/* this is not the droid you're looking for */
	
	template <typename T> using standard = std::allocator<T>;
	
	template <typename T>
	COCONUT_PRIVATE struct COCONUT_VISIBLE placement COCONUT_FINAL : public standard<T>
	{
		using size_type = typename standard<T>::size_type;
		using difference_type = typename standard<T>::difference_type;
		
		using pointer = typename standard<T>::pointer;
		using const_pointer = typename standard<T>::const_pointer;
		
		using reference = typename standard<T>::reference;
		using const_reference = typename standard<T>::const_reference;
		
		using value_type = typename standard<T>::value_type;
		
		using void_pointer = typename standard<void>::pointer;
		using const_void_pointer = typename standard<const void>::const_pointer;
		
		template<typename T0>
		struct rebind { typedef placement<T0> other; };
		
		using propagate_on_container_move_assignment = typename std::true_type;
		using is_always_equal = typename std::true_type;
		
#if COCONUT_DEBUG
		template <typename T0> using this_parent = standard<T0>;
		template <typename T0> using this_type = placement<T0>;
#endif

		placement(void_pointer p = nullptr) throw() : standard<T>(), m_ref(p) { /* NOP */ }
		placement(const placement & other) throw() : standard<T>(other) { m_ref = other.m_ref; }
		placement(placement && other) throw() : standard<T>(std::move(other)) { m_ref = other.m_ref; }
		
		template <typename T0>
		placement(const placement<T0> & other) throw() : standard<T0>(other) { m_ref = other.m_ref; }
		
		template <typename T0>
		placement(placement<T0> && other) throw() : standard<T0>(other) { m_ref = other.m_ref; }
		
		~placement() throw()
		{
#if COCONUT_DEBUG
			this->~this_parent<T>();
#endif
		}

		pointer allocate(size_type n, const_void_pointer = nullptr)
		{ char * p = new (m_ref) char[n * sizeof(T)]; return weak_cast<T *>(p); }

		void deallocate(pointer p, size_type n) noexcept { /* NOP */ }
		
		size_type max_size() const noexcept {return size_type(~0) / sizeof(T);}
		
		pointer address(reference x) const noexcept { return std::addressof(x); }
		const_pointer address(const_reference x) const noexcept { return address(weak_cast<reference>(x)); }
	
	private:
#if COCONUT_DEBUG
		COCONUT_ALIGNAS(std::max_align_t) void * m_ref;
#else
		void * m_ref;
#endif
	};
	
	template <typename T>
	COCONUT_PRIVATE struct COCONUT_VISIBLE emptiness COCONUT_FINAL
	{
		using size_type = typename standard<T>::size_type;
		using difference_type = typename standard<T>::difference_type;
		
		using pointer = typename standard<T>::pointer;
		using const_pointer = typename standard<T>::const_pointer;
		
		using reference = typename standard<T>::reference;
		using const_reference = typename standard<T>::const_reference;
		
		using value_type = typename standard<T>::value_type;
		
		using void_pointer = typename standard<void>::pointer;
		using const_void_pointer = typename standard<void>::const_pointer;
		
		using propagate_on_container_move_assignment = typename std::true_type;
		using is_always_equal = typename std::true_type;
		
		template<typename T0>
		struct rebind { typedef emptiness<T0> other; };
		
		emptiness(void_pointer p = nullptr) { /* NOP */ }
		emptiness(const emptiness & other) { /* NOP */ }
		emptiness(emptiness && other) { /* NOP */ }
		
		template <typename T0>
		emptiness(const emptiness<T0> & other) { /* NOP */ }
		
		template <typename T0>
		emptiness(emptiness<T0> && other) { /* NOP */ }
		
		~emptiness() { /* NOP */ }
		
		pointer allocate(size_type n, const_void_pointer = nullptr)
		{ return nullptr; }
		
		void deallocate(pointer p, size_type n) noexcept { /* NOP */ }
		
		size_type max_size() const noexcept { return 0; }
		
		pointer address(reference x) const noexcept { return std::addressof(x); }
		const_pointer address(const_reference x) const noexcept { return address(weak_cast<reference>(x)); }
		
		void construct(pointer p, const_reference val) { /* NOP */ }
		
		template <typename U, typename... Args>
		void construct(U * p, Args &&... args) { /* NOP */ }
		
		void destroy(pointer p) { /* NOP */ }
		
		template<class U>
		void destroy(U * p) { /* NOP */ }
	};
	
}}} /* EONS */

namespace coconut
{
	/* trickster */
	
	template <typename T1, typename T2>
	bool operator == (
		const runtime::allocators::standard<T1> &,
		const runtime::allocators::placement<T2> &
	) { return true; }

	template <typename T1, typename T2>
	bool operator == (
		const runtime::allocators::placement<T1> &,
		const runtime::allocators::standard<T2> &
	) { return true; }
	
	template <typename T1, typename T2>
	bool operator != (
		const runtime::allocators::standard<T1> &,
		const runtime::allocators::placement<T2> &
	) { return false; }

	template <typename T1, typename T2>
	bool operator != (
		const runtime::allocators::placement<T1> &,
		const runtime::allocators::standard<T2> &
	) { return false; }
	
	template <typename T1, typename T2>
	bool operator == (
		const runtime::allocators::standard<T1> &,
		const runtime::allocators::emptiness<T2> &
	) { return true; }
	
	template <typename T1, typename T2>
	bool operator == (
		const runtime::allocators::emptiness<T1> &,
		const runtime::allocators::standard<T2> &
	) { return true; }
	
	template <typename T1, typename T2>
	bool operator != (
		const runtime::allocators::standard<T1> &,
		const runtime::allocators::emptiness<T2> &
	) { return false; }
	
	template <typename T1, typename T2>
	bool operator != (
		const runtime::allocators::emptiness<T1> &,
		const runtime::allocators::standard<T2> &
	) { return false; }
	
	template <typename T1, typename T2>
	bool operator == (
		const runtime::allocators::emptiness<T1> &,
		const runtime::allocators::placement<T2> &
	) { return true; }

	template <typename T1, typename T2>
	bool operator == (
		const runtime::allocators::placement<T1> &,
		const runtime::allocators::emptiness<T2> &
	) { return true; }

	template <typename T1, typename T2>
	bool operator != (
		const runtime::allocators::emptiness<T1> &,
		const runtime::allocators::placement<T2> &
	) { return false; }

	template <typename T1, typename T2>
	bool operator != (
		const runtime::allocators::placement<T1> &,
		const runtime::allocators::emptiness<T2> &
	) { return false; }
	
} /* EONS */

#endif /* !COCONUT_RUNTIME_ALLOCATORS_HPP */

/* EOF */