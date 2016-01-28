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
	COCONUT_PUBLIC class COCONUT_EXPORT Dictionary : public Object
	{
	COCONUT_KDCL(coconut.Dictionary, Object.Dictionary)
		
	public:
		Dictionary();
		Dictionary(const Dictionary & dict);
		Dictionary & operator = (const Dictionary & dict) = default;
		Dictionary(const Dictionary & dict, CopyOption option);
		
		Dictionary(Dictionary && dict);
		
		Dictionary(const std::initializer_list< std::pair< Owning<Any>, Owning<Any> > > & args);
		Dictionary(const std::initializer_list< std::pair<Any *, Any *> > & args);
		
		template <typename IterT>
		Dictionary(IterT && beg, IterT && end) :
			Dictionary(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone)
		{ /* NOP */ }
		
		template <typename IterT>
		Dictionary(IterT && beg, IterT && end, CopyOption option) :
			Object(DictionaryClass),
			m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
			{ return (a->compare(*b) == OrderedAscending); })
		{
			for (; beg != end; ++beg) {
				if ((*beg).first && (*beg).second) {
					if (option != CopyNone) {
						Owning<Any> kcpy = Object::copyObject((*beg).first, CopyImmutable);
						Owning<Any> vcpy = Object::copyObject((*beg).second, option);
						if (kcpy && vcpy) { m_impl.insert(std::make_pair(kcpy, vcpy)); }
					} else {
						m_impl.insert(std::make_pair((*beg).first, (*beg).second));
					}
				}
			}
		}
		
		template <typename IterKeyT, typename IterValT>
		Dictionary(IterKeyT && beg_key, IterKeyT && end_key, IterValT && beg_val, IterValT && end_val, CopyOption option = CopyNone) :
			Object(DictionaryClass),
			m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
			{ return (a->compare(*b) == OrderedAscending); })
		{
			using key_diff_t = typename IterKeyT::difference_type;
			using val_diff_t = typename IterValT::difference_type;
			
			key_diff_t dist_k = std::distance<IterKeyT>(beg_key, end_key);
			val_diff_t dist_v = std::distance<IterValT>(beg_val, end_val);
			
			typedef std::pair<
				typename std::decay<IterKeyT>::type,
				typename std::decay<IterValT>::type
			> pair_iterator;
			
			if (dist_k <= dist_v) {
				for (pair_iterator it(beg_key, beg_val); it.first != end_key; ++it.first, ++it.second) {
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
		
		COCONUT_KTOR Owning<Dictionary> with();
		COCONUT_KTOR Owning<Dictionary> with(const Dictionary & dict);
		COCONUT_KTOR Owning<Dictionary> with(const Dictionary & dict, CopyOption option);
		
		COCONUT_KTOR Owning<Dictionary> with(Dictionary && dict);
		
		COCONUT_KTOR Owning<Dictionary> with(const std::initializer_list< std::pair< Owning<Any>, Owning<Any> > > & args);
		COCONUT_KTOR Owning<Dictionary> with(const std::initializer_list< std::pair<Any *, Any *> > & args);
		
		template <typename IterT>
		COCONUT_KTOR Owning<Dictionary> with(IterT && beg, IterT && end)
		{ return ptr_create<Dictionary>(std::forward<IterT>(beg), std::forward<IterT>(end)); }
		
		template <typename IterT>
		COCONUT_KTOR Owning<Dictionary> with(IterT && beg, IterT && end, CopyOption option)
		{ return ptr_create<Dictionary>(std::forward<IterT>(beg), std::forward<IterT>(end), option); }
		
		template <typename IterKeyT, typename IterValT>
		COCONUT_KTOR Owning<Dictionary> with(IterKeyT && beg_key, IterKeyT && end_key, IterValT && beg_val, IterValT && end_val, CopyOption option = CopyNone)
		{ return ptr_create<Dictionary>(std::forward<IterKeyT>(beg_key), std::forward<IterKeyT>(end_key), std::forward<IterValT>(beg_val), std::forward<IterValT>(end_val), option); }
		
		COCONUT_KTOR Owning<Dictionary> with(const Path & path);
		COCONUT_KTOR Owning<Dictionary> with(const URL & url);
		
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
		typedef std::map<Owning<Any>, Owning<Any>, std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> > impl_type;
	
	public:
		typedef impl_type::iterator iterator;
		typedef impl_type::const_iterator const_iterator;
		
		typedef impl_type::reverse_iterator reverse_iterator;
		typedef impl_type::const_reverse_iterator const_reverse_iterator;
		
		typedef impl_type::value_type value_type;
		typedef impl_type::size_type size_type;
		typedef impl_type::difference_type difference_type;
	
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
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_DICTIONARY_HPP */

/* EOF */