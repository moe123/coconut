//
// MutableDictionary.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Dictionary.hpp>

#ifndef COCONUT_FOUNDATION_MUTABLEDICTIONARY_HPP
#define COCONUT_FOUNDATION_MUTABLEDICTIONARY_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT MutableDictionary : public Dictionary
	{
	COCONUT_KDCL(coconut.MutableDictionary, Object.Dictionary.MutableDictionary)
		
	public:
		MutableDictionary();
		MutableDictionary(const MutableDictionary & dict);
		MutableDictionary & operator = (const MutableDictionary & dict) = default;
		MutableDictionary(const MutableDictionary & dict, CopyOption option);
		
		MutableDictionary(MutableDictionary && dict);
		
		MutableDictionary(const Dictionary & dict, CopyOption option);
		MutableDictionary(Dictionary && dict);
		
		MutableDictionary(const std::initializer_list< std::pair<Owning<Any>, Owning<Any>> > & args);
		MutableDictionary(const std::initializer_list< std::pair<Any *, Any *> > & args);
		
		template <typename IterT>
		MutableDictionary(IterT && beg, IterT && end) :
			Dictionary(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone)
		{ setClassKind(MutableDictionaryClass, true); }
		
		template <typename IterT>
		MutableDictionary(IterT && beg, IterT && end, CopyOption option) :
			Dictionary(beg, end, option)
		{ setClassKind(MutableDictionaryClass, true); }
		
		template <typename IterKeyT, typename IterValT>
		MutableDictionary(IterKeyT && beg_key, IterKeyT && end_key, IterValT && beg_val, IterValT && end_val, CopyOption option = CopyNone) :
			Dictionary(beg_key, end_key, beg_val, end_val, option)
		{ setClassKind(MutableDictionaryClass, true); }
		
		MutableDictionary(const Path & path);
		MutableDictionary(const URL & url);
		virtual ~MutableDictionary();

		virtual void setValueForKey(Owning<Any> ptr, const std::string & utf8_key)
		COCONUT_FINAL_OVERRIDE;
		
		COCONUT_KTOR MutableDictionaryPtr with();
		COCONUT_KTOR MutableDictionaryPtr with(const MutableDictionary & dict);
		COCONUT_KTOR MutableDictionaryPtr with(const MutableDictionary & dict, CopyOption option);
		COCONUT_KTOR MutableDictionaryPtr with(MutableDictionary && dict);
		
		COCONUT_KTOR MutableDictionaryPtr with(const Dictionary & dict, CopyOption option);
		COCONUT_KTOR MutableDictionaryPtr with(Dictionary && dict);
		
		COCONUT_KTOR MutableDictionaryPtr with(const std::initializer_list< std::pair<Owning<Any>, Owning<Any>> > & args);
		COCONUT_KTOR MutableDictionaryPtr with(const std::initializer_list< std::pair<Any *, Any *> > & args);
		
		template <typename IterT>
		COCONUT_KTOR MutableDictionaryPtr with(IterT && beg, IterT && end)
		{ return ptr_create<MutableDictionary>(std::forward<IterT>(beg), std::forward<IterT>(end)); }
		
		template <typename IterT>
		COCONUT_KTOR MutableDictionaryPtr with(IterT && beg, IterT && end, CopyOption option)
		{ return ptr_create<MutableDictionary>(std::forward<IterT>(beg), std::forward<IterT>(end), option); }
		
		template <typename IterKeyT, typename IterValT>
		COCONUT_KTOR MutableDictionaryPtr with(IterKeyT && beg_key, IterKeyT && end_key, IterValT && beg_val, IterValT && end_val, CopyOption option = CopyNone)
		{ return ptr_create<MutableDictionary>(std::forward<IterKeyT>(beg_key), std::forward<IterKeyT>(end_key), std::forward<IterValT>(beg_val), std::forward<IterValT>(end_val), option); }
		
		COCONUT_KTOR MutableDictionaryPtr with(const Path & path);
		COCONUT_KTOR MutableDictionaryPtr with(const URL & url);
		
		void setDictionary(MutableDictionary && dict);
		void setDictionary(Dictionary && dict);
		
		void setObjectsFromDictionary(const Dictionary & dict);
		void setObjectsFromDictionary(const Dictionary & dict, CopyOption option);
		
		template <typename IterT>
		void setObjects(IterT && beg, IterT && end)
		{ setObjects(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone); }
		
		template <typename IterT>
		void setObjects(IterT && beg, IterT && end, CopyOption option)
		{ setObjectsFromDictionary(Dictionary(std::forward<IterT>(beg), std::forward<IterT>(end)), option); }
		
		void setObject(Owning<Any> ptr, const std::string & utf8_key);
		void setObject(Owning<Any> ptr, const Any & key);
		void setObject(Owning<Any> ptr, const Owning<Any> & key);
		
		void setObject(Owning<Any> ptr, const std::string & utf8_key, CopyOption option);
		void setObject(Owning<Any> ptr, const Any & key, CopyOption option);
		void setObject(Owning<Any> ptr, const Owning<Any> & key, CopyOption option);
		
		void addEntriesFromDictionary(const Dictionary & dict);
		void addEntriesFromDictionary(const Dictionary & dict, CopyOption option);
		
		template <typename IterT>
		void addEntries(IterT && beg, IterT && end) const
		{ addEntries(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone); }
		
		template <typename IterT>
		void addEntries(IterT && beg, IterT && end, CopyOption option)
		{ addEntriesFromDictionary(Dictionary(std::forward<IterT>(beg), std::forward<IterT>(end)), option); }
		
		void removeObjectForKey(const std::string & utf8_key);
		void removeObjectForKey(const Any & key);
		void removeObjectForKey(const Owning<Any> & key);
		
		void removeAllObjects();
		void removeObjectsForKeys(const Array & keys);
		
	public:
		Owning<Any> & operator [] (const std::string & utf8_key);
		Owning<Any> & operator [] (const Any & key);
		Owning<Any> & operator [] (const Owning<Any> & key);
	};
}

#endif /* !COCONUT_FOUNDATION_MUTABLEDICTIONARY_HPP */

/* EOF */