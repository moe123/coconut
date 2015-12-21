//
// nucleus.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_NUCLEUS_HPP
#define COCONUT_RUNTIME_NUCLEUS_HPP

namespace coconut
{
	namespace runtime
	{
		COCONUT_PRIVATE class COCONUT_EXPORT nucleus 
		{
		COCONUT_RUNTIME_KDCL(coconut.runtime.nucleus, nucleus)
			
		private:
			nucleus();
		protected:
			nucleus(const nucleus & ref);
			nucleus & operator = (const nucleus & ref);
			
		protected:
			explicit nucleus(ClassKind root, ClassKind kind);
			virtual ~nucleus();
		
		protected:
		/*
		* Sending messages.
		*/
			static bool isSelectorKey(const std::string & utf8_in);
			static bool isAttributeKey(const std::string & utf8_attrkey);
			
		public:
			bool respondsToSelectorKey(const std::string & utf8_selkey) const;
			
			void performSelectorKeyAfterDelay(uint64_t microseconds, bool wait, const std::string & utf8_selkey, Owning<Any> arg = {}) const;
			void performSelectorKeyInBackground(const std::string & utf8_selkey, Owning<Any> arg = {}) const;
			Owning<Any> performSelectorKey(const std::string & utf8_selkey, Owning<Any> arg = {}) const;
			
		protected:
		/*
		* Instance identity settings.
		*/
			void pushKind(ClassKind kind);
			void setClassKind(ClassKind kind, bool ismutable);
			ClassKind classKind() const;
			ClassKind parentClassKind() const;
		
		protected:
		/*
		* Dynamic attributes.
		*/
			void conveyAttributesFrom(const Any & ref);
			void removeAllAttributes();
			
			bool setAttributeForKey(Owning<Any> ptr, const std::string & utf8_attrkey);
			bool removeAttributeForKey(const std::string & utf8_attrkey);
			bool hasAttributeForKey(const std::string & utf8_attrkey) const;
			Owning<Any> attributeForKey(const std::string & utf8_attrkey) const;
		
		public:
			void setTag(std::int64_t tag);
			std::int64_t tag() const;
			
		public:
			const std::string className() const;
			const std::string classTree() const;
		
		public:
			const Any * itself() const;
			virtual std::size_t hash() const;
			
		public:
		/*
		* Interface iConformance: Object inheritance and behavior. 
		*/
			template <typename T>
			bool conformsTo(void * no_param = nullptr) const
			{ COCONUT_UNUSED(no_param); T * ptr = dynamic_cast<T *>(this); return (ptr != nullptr); }
			
			bool isKindOf(ClassKind kind) const;
			bool isKindOf(const Any & ref, const Any & other_ref) const;
			bool isKindOf(Owning<Any> ptr, Owning<Any> other_ptr) const;
			bool isKindOf(const Any & ref) const;
			bool isKindOf(Owning<Any> ptr) const;
			
			bool isSubclassOf(ClassKind kind) const;
			bool isSubclassOf(const Any & ref, const Any & other_ref) const;
			bool isSubclassOf(Owning<Any> ptr, Owning<Any> other_ptr) const;
			bool isSubclassOf(const Any & ref) const;
			bool isSubclassOf(Owning<Any> ptr) const;
			
			bool isMemberOf(ClassKind kind) const;
			bool isMemberOf(const Any & ref, const Any & other_ref) const;
			bool isMemberOf(Owning<Any> ptr, Owning<Any> other_ptr) const;
			bool isMemberOf(const Any & ref) const;
			bool isMemberOf(Owning<Any> ptr) const;
			
			bool isAncestorOf(const Any & ref) const;
			bool isAncestorOf(Owning<Any> ptr) const;
			
			bool isParentOf(const Any & ref) const;
			bool isParentOf(Owning<Any> ptr) const;
			
		public:
		/*
		* Interface/Protocol iCopying: Copying object.
		*/
			virtual Owning<Any> copy() const;
			virtual Owning<Any> mutableCopy() const;
			Owning<Any> kindCopy() const;

		public:
		/*
		* Interface/Protocol iKeyValueCoding: A mechanism by which you can access the properties of an object indirectly by key.
		*/
			virtual Owning<Any> valueForKey(const std::string & utf8_key) const;
			virtual void setValueForKey(Owning<Any> ptr, const std::string & utf8_key);
			
			virtual Owning<Any> valueForKeyPath(const std::string & utf8_keypath) const;
			virtual void setValueForKeyPath(Owning<Any> ptr, const std::string & utf8_keypath);
			
			virtual Owning<Any> valueForSelectorKey(const std::string & utf8_selkey, Owning<Any> arg = {}) const;
			
			Owning<Any> valueForKey(const Any & key) const;
			Owning<Any> valueForKey(const Owning<Any> & key) const;
			
			void setValueForKey(Owning<Any> ptr, const Any & key);
			void setValueForKey(Owning<Any> ptr, const Owning<Any> & key);
			
			Owning<Any> valueForKeyPath(const Any & keypath) const;
			Owning<Any> valueForKeyPath(const Owning<Any> & keypath) const;
			
			void setValueForKeyPath(Owning<Any> ptr, const Any & keypath);
			void setValueForKeyPath(Owning<Any> ptr, const Owning<Any> & keypath);
			
			Owning<Any> valueForSelectorKey(const Any & selkey, Owning<Any> arg = {}) const;
			Owning<Any> valueForSelectorKey(const Owning<Any> & selkey, Owning<Any> arg = {}) const;
			
		private:
		/*
		* Interface/Protocol iComparison: Comparing objects.
		*/
			/* default placeholders for compare */
			template <typename T> int compareTo(T && a, T && b) const
			{
				if (sizeof(a) < sizeof(b)) {
					return cmp_ascending;
				} else if (sizeof(b) < sizeof(a)) {
					return cmp_descending;
				}
				return cmp_same;
			}

			template <typename T1, typename T2> int compareTo(T1 && a, T2 && b) const
			{
				if (sizeof(a) < sizeof(b)) {
					return cmp_ascending;
				} else if (sizeof(b) < sizeof(a)) {
					return cmp_descending;
				}
				return cmp_same;
			}
		
		public:
			bool isEqual(const Any & ref) const;
			bool isEqual(Owning<Any> ptr) const;
			
			virtual ComparisonResult compare(const Any & ref) const;
			ComparisonResult compare(Owning<Any> ptr) const;
			
			virtual bool doesContain(const Any & ref) const;
			bool doesContain(Owning<Any> ptr) const;
			
			bool doesNotContain(const Any & ref) const;
			bool doesNotContain(Owning<Any> ptr) const;
			
			bool isIdenticalTo(const Any & ref) const;
			bool isIdenticalTo(Owning<Any> ptr) const;
			
			bool isNotIdenticalTo(const Any & ref) const;
			bool isNotisIdenticalTo(Owning<Any> ptr) const;
			
			bool isEqualTo(const Any & ref) const;
			bool isEqualTo(Owning<Any> ptr) const;
			
			bool isNotEqualTo(const Any & ref) const;
			bool isNotEqualTo(Owning<Any> ptr) const;
			
			bool isLessThan(const Any & ref) const;
			bool isLessThan(Owning<Any> ptr) const;
			
			bool isLessThanOrEqualTo(const Any & ref) const;
			bool isLessThanOrEqualTo(Owning<Any> ptr) const;
			
			bool isGreaterThan(const Any & ref) const;
			bool isGreaterThan(Owning<Any> ptr) const;
			
			bool isGreaterThanOrEqualTo(const Any & ref) const;
			bool isGreaterThanOrEqualTo(Owning<Any> ptr) const;
			
			/*
			* operator identical by addresse calling @isIdenticalTo:, e.g left and right are truely the same.
			*/
			bool operator &= (const Any & ref) const;
			
			/*
			* operators identical and comparison by value calling @compare:.
			*/
			bool operator == (const Any & ref) const;
			bool operator != (const Any & ref) const;
			bool operator <  (const Any & ref) const;
			bool operator <= (const Any & ref) const;
			bool operator >  (const Any & ref) const;
			bool operator >= (const Any & ref) const;
		
		public:
		/*
		* Interface/Protocol iRepresentation: accessing string representations and numeric values.
		*/
			
			const std::string description() const;
			
			virtual std::string stringValue() const;
			virtual std::u16string string16Value() const;
			virtual std::u32string string32Value() const;
			
			virtual float floatValue() const;
			virtual double doubleValue() const;
			virtual long double longDoubleValue() const;
			
			virtual bool boolValue() const;
			virtual char charValue() const;
			
			virtual short shortValue() const;
			virtual int intValue() const;
			virtual long longValue() const;
			virtual long long longLongValue() const;
			
			virtual unsigned char unsignedCharValue() const;
			virtual unsigned short unsignedShortValue() const;
			virtual unsigned int unsignedIntValue() const;
			virtual unsigned long unsignedLongValue() const;
			virtual unsigned long long unsignedLongLongValue() const;
			
			virtual std::size_t size() const;
			
		public:
			friend inline std::ostream & operator << (std::ostream & os, const Any & ref)
			{ os << ref.stringValue(); return os; }
			
			friend inline std::ostream & operator << (std::ostream & os, const Owning<Any> ptr)
			{ if (ptr) { os << ptr->stringValue(); } return os; }
			
		private:
			uintptr_t sig() const;
			const std::string addr() const;
			bool mutability() const;
			
		private:
			std::unordered_map<std::string, Owning<Any>> m_attrs;
			std::vector<ClassKind> m_kinds;
			std::string m_addr;
			ClassKind m_kind;
			std::int64_t m_tag;
			bool m_ismutable;
			
		protected:
			typedef spinlock spin_type;
			spin_type & spin() { return m_spinlock; }
			spin_type m_spinlock;
		};
	}
}

#endif /* !COCONUT_RUNTIME_NUCLEUS_HPP */

/* EOF */