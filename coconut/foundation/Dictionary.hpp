//
// Dictionary.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>
#include <coconut/runtime/Serialization.hpp>

#ifndef COCONUT_FOUNDATION_DICTIONARY_HPP
#define COCONUT_FOUNDATION_DICTIONARY_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Dictionary : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Dictionary, Object.Dictionary)
		
	public:
		Dictionary();
		Dictionary(const Dictionary & dict);
		Dictionary & operator = (const Dictionary & dict) = default;
		Dictionary(const Dictionary & dict, CopyOption option);
		Dictionary(Dictionary && dict) noexcept;
		Dictionary(const std::initializer_list< std::pair< Owning<Any>, Owning<Any> > > & args);
		Dictionary(const std::initializer_list< std::pair<Any *, Any *> > & args);
		
		template <typename InputIterT>
		Dictionary(InputIterT && first, InputIterT && last) :
			Dictionary(std::forward<InputIterT>(first), std::forward<InputIterT>(last), CopyNone)
		{ /* NOP */ }
		
		template <typename InputIterT>
		Dictionary(InputIterT && first, InputIterT && last, CopyOption option) :
			Object(DictionaryClass),
			m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
			{ return (a->compare(*b) == OrderedAscending); })
		{
			for (; first != last; ++first) {
				if ((*first).first && (*first).second) {
					if (option != CopyNone) {
						Owning<Any> kcpy = Object::copyObject((*first).first, CopyImmutable);
						Owning<Any> vcpy = Object::copyObject((*first).second, option);
						if (kcpy && vcpy) { m_impl.insert(std::make_pair(kcpy, vcpy)); }
					} else {
						m_impl.insert(std::make_pair((*first).first, (*first).second));
					}
				}
			}
		}
		
		template <typename IterKeyT, typename IterValT>
		Dictionary(IterKeyT && first_key, IterKeyT && last_key, IterValT && first_val, IterValT && last_val, CopyOption option = CopyNone) :
			Object(DictionaryClass),
			m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
			{ return (a->compare(*b) == OrderedAscending); })
		{
			using key_diff_t = typename IterKeyT::difference_type;
			using val_diff_t = typename IterValT::difference_type;
			
			key_diff_t dist_k = std::distance<typename std::decay<IterKeyT>::type>(first_key, last_key);
			val_diff_t dist_v = std::distance<typename std::decay<IterValT>::type>(first_val, last_val);
			
			typedef std::pair<
				typename std::decay<IterKeyT>::type,
				typename std::decay<IterValT>::type
			> pair_iterator;
			
			if (dist_k <= dist_v) {
				for (pair_iterator it(first_key, first_val); it.first != last_key; ++it.first, ++it.second) {
					if ((*it.first) && (*it.second)) {
						if (option != CopyNone) {
							Owning<Any> kcpy = Object::copyObject((*it.first), CopyImmutable);
							Owning<Any> vcpy = Object::copyObject((*it.second), option);
							if (kcpy && vcpy) { m_impl.insert(std::make_pair(kcpy, vcpy)); }
						} else {
							m_impl.insert(std::make_pair((*it.first), (*it.second)));
						}
					}
				}
			}
		}
		
		Dictionary(const Path & path);
		Dictionary(const URL & url);
		virtual ~Dictionary();

		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> mutableCopy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual bool doesContain(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> valueForKey(const std::string & utf8_key) const
		COCONUT_FINAL_OVERRIDE;
		
		const Array makeKeysPerformSelectorKey(const std::string & utf8_selkey, Owning<Any> arg = {}) const;
		
		void enumerateKeysAndObjectsUsingFunction(const std::function<void(const Owning<Any> & key, const Owning<Any> & obj, bool & stop)> & func) const;
		void enumerateKeysAndObjectsUsingFunction(const std::function<void(const Owning<Any> & key, const Owning<Any> & obj, bool & stop)> & func, EnumerationOptions options) const;

		bool containsKey(const std::string & utf8_key) const;
		bool containsKey(const Any & key) const;
		bool containsKey(const Owning<Any> & key) const;
		
		const Owning<Any> objectForKey(const std::string & utf8_key) const;
		const Owning<Any> objectForKey(const Any & key) const;
		const Owning<Any> objectForKey(const Owning<Any> & key) const;
		
		const Owning<Any> objectForCaseInsensitiveKey(const std::string & utf8_key) const;
		const Owning<Any> objectForCaseInsensitiveKey(const Any & key) const;
		const Owning<Any> objectForCaseInsensitiveKey(const Owning<Any> & key) const;
		
		const Array objectsForKeys(const Array & keys, Owning<Any> notFoundMarker = {}) const;
		const Array objectsForKeys(const Set & keys, Owning<Any> notFoundMarker = {}) const;
		
		const Array allKeys(CopyOption option = CopyNone) const;
		const Array allKeysForObject(const Any & obj, CopyOption option = CopyNone) const;
		const Array allKeysForObject(const Owning<Any> & obj, CopyOption option = CopyNone) const;
		
		const Array allValues(CopyOption option = CopyNone) const;
		
		const Array keysSortedByValueUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, CopyOption option = CopyNone) const;
		const Array keysSortedByValueAscending(CopyOption option = CopyNone) const;
		const Array keysSortedByValueDescending(CopyOption option = CopyNone) const;
		
		const Array keysSortedUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, CopyOption option = CopyNone) const;
		const Array keysSortedUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, CopyOption option, SortOptions options) const;
		
		const Array keysSortedAscending(CopyOption option = CopyNone) const;
		const Array keysSortedAscending(CopyOption option, SortOptions options) const;
		
		const Array keysSortedDescending(CopyOption option = CopyNone) const;
		const Array keysSortedDescending(CopyOption option, SortOptions options) const;
		
		const Array keysSortedUsingSelectorKey(const std::string & utf8_selkey, CopyOption option = CopyNone) const;
		const Array keysSortedUsingSelectorKey(const std::string & utf8_selkey, CopyOption option, bool descending) const;
		const Array keysSortedUsingSelectorKey(const std::string & utf8_selkey, CopyOption option, bool descending, SortOptions options) const;
		
		const Array keysSortedUsingDescriptor(const SortDescriptor & descriptor, CopyOption option = CopyNone) const;
		const Array keysSortedUsingDescriptor(const SortDescriptor & descriptor, CopyOption option, SortOptions options) const;
		
		const Array keysSortedUsingDescriptors(const Array & descriptors, CopyOption option = CopyNone) const;
		const Array keysSortedUsingDescriptors(const Array & descriptors, CopyOption option, SortOptions options) const;
		
		const Set keysOfEntriesPassingTest(const std::function<bool(const Owning<Any> & key, bool & stop)> & func, CopyOption option = CopyNone) const;
		
		bool writeToFile(const Path & path, bool atomically = true) const;
		bool writeToURL(const URL & url, bool atomically = true) const;
		
	public:
		const Owning<Any> operator [] (const std::string & utf8_key) const;
		const Owning<Any> operator [] (const Any & key) const;
		const Owning<Any> operator [] (const Owning<Any> & key) const;
	
	protected:
		typedef std::map< Owning<Any>, Owning<Any>, bool (*) (const Owning<Any> & a, const Owning<Any> & b)> impl_trait;
	
	public:
		typedef impl_trait::iterator iterator;
		typedef impl_trait::const_iterator const_iterator;
		
		typedef impl_trait::reverse_iterator reverse_iterator;
		typedef impl_trait::const_reverse_iterator const_reverse_iterator;
		
		typedef impl_trait::key_type key_type;
		typedef impl_trait::mapped_type mapped_type;
		
		typedef impl_trait::value_type value_type;
		typedef impl_trait::size_type size_type;
		typedef impl_trait::difference_type difference_type;
		
		typedef impl_trait::reference reference;
		typedef impl_trait::const_reference const_reference;
		typedef impl_trait::pointer pointer;
		typedef impl_trait::const_pointer const_pointer;
		
		typedef impl_trait::allocator_type allocator_type;
		
	public:
		iterator begin();
		iterator end();
		
		const_iterator begin() const;
		const_iterator end() const;
		
		const_iterator cbegin() const;
		const_iterator cend() const;
		
		reverse_iterator rbegin();
		reverse_iterator rend();
		
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;
		
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;
	
	protected:
		friend class MutableDictionary;
		friend class URL;
		
	protected:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_DICTIONARY_HPP */

/* EOF */