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
			
			void performSelectorKeyAfterDelay(uint64_t microseconds, bool wait, const std::string & utf8_selkey, kind_ptr arg = {}) const;
			void performSelectorKeyInBackground(const std::string & utf8_selkey, kind_ptr arg = {}) const;
			kind_ptr performSelectorKey(const std::string & utf8_selkey, kind_ptr arg = {}) const;
			
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
			void conveyAttributesFrom(const_kind_ref ref);
			void removeAllAttributes();
			
			bool setAttributeForKey(kind_ptr ptr, const std::string & utf8_attrkey);
			bool removeAttributeForKey(const std::string & utf8_attrkey);
			bool hasAttributeForKey(const std::string & utf8_attrkey) const;
			kind_ptr attributeForKey(const std::string & utf8_attrkey) const;
		
		public:
			void setTag(std::int64_t tag);
			std::int64_t tag() const;
			
		public:
			const std::string className() const;
			const std::string classTree() const;
		
		public:
			const_kind_raw_ptr itself() const;
			virtual std::size_t hash() const;
			
		public:
		/*
		* Interface iConformance: Object inheritance and behavior. 
		*/
			template <typename T>
			bool conformsTo(void * no_param = nullptr) const
			{ COCONUT_UNUSED(no_param); T * ptr = dynamic_cast<T *>(this); return (ptr != nullptr); }
			
			bool isKindOf(ClassKind kind) const;
			bool isKindOf(const_kind_ref ref, const_kind_ref other_ref) const;
			bool isKindOf(kind_ptr ptr, kind_ptr other_ptr) const;
			bool isKindOf(const_kind_ref ref) const;
			bool isKindOf(kind_ptr ptr) const;
			
			bool isSubclassOf(ClassKind kind) const;
			bool isSubclassOf(const_kind_ref ref, const_kind_ref other_ref) const;
			bool isSubclassOf(kind_ptr ptr, kind_ptr other_ptr) const;
			bool isSubclassOf(const_kind_ref ref) const;
			bool isSubclassOf(kind_ptr ptr) const;
			
			bool isMemberOf(ClassKind kind) const;
			bool isMemberOf(const_kind_ref ref, const_kind_ref other_ref) const;
			bool isMemberOf(kind_ptr ptr, kind_ptr other_ptr) const;
			bool isMemberOf(const_kind_ref ref) const;
			bool isMemberOf(kind_ptr ptr) const;
			
			bool isAncestorOf(const_kind_ref ref) const;
			bool isAncestorOf(kind_ptr ptr) const;
			
			bool isParentOf(const_kind_ref ref) const;
			bool isParentOf(kind_ptr ptr) const;
			
		public:
		/*
		* Interface/Protocol iCopying: Copying object.
		*/
			virtual kind_ptr copy() const;
			virtual kind_ptr mutableCopy() const;
			kind_ptr kindCopy() const;

		public:
		/*
		* Interface/Protocol iKeyValueCoding: A mechanism by which you can access the properties of an object indirectly by key.
		*/
			virtual kind_ptr valueForKey(const std::string & utf8_key) const;
			virtual void setValueForKey(kind_ptr ptr, const std::string & utf8_key);
			
			virtual kind_ptr valueForKeyPath(const std::string & utf8_keypath) const;
			virtual void setValueForKeyPath(kind_ptr ptr, const std::string & utf8_keypath);
			
			virtual kind_ptr valueForSelectorKey(const std::string & utf8_selkey, kind_ptr arg = {}) const;
			
			kind_ptr valueForKey(const_kind_ref key) const;
			kind_ptr valueForKey(const_kind_ptr & key) const;
			
			void setValueForKey(kind_ptr ptr, const_kind_ref key);
			void setValueForKey(kind_ptr ptr, const_kind_ptr & key);
			
			kind_ptr valueForKeyPath(const_kind_ref keypath) const;
			kind_ptr valueForKeyPath(const_kind_ptr & keypath) const;
			
			void setValueForKeyPath(kind_ptr ptr, const_kind_ref keypath);
			void setValueForKeyPath(kind_ptr ptr, const_kind_ptr & keypath);
			
			kind_ptr valueForSelectorKey(const_kind_ref selkey, kind_ptr arg = {}) const;
			kind_ptr valueForSelectorKey(const_kind_ptr & selkey, kind_ptr arg = {}) const;
			
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
			bool isEqual(const_kind_ref ref) const;
			bool isEqual(kind_ptr ptr) const;
			
			virtual ComparisonResult compare(const_kind_ref ref) const;
			ComparisonResult compare(kind_ptr ptr) const;
			
			virtual bool doesContain(const_kind_ref ref) const;
			bool doesContain(kind_ptr ptr) const;
			
			bool doesNotContain(const_kind_ref ref) const;
			bool doesNotContain(kind_ptr ptr) const;
			
			bool isIdenticalTo(const_kind_ref ref) const;
			bool isIdenticalTo(kind_ptr ptr) const;
			
			bool isNotIdenticalTo(const_kind_ref ref) const;
			bool isNotisIdenticalTo(kind_ptr ptr) const;
			
			bool isEqualTo(const_kind_ref ref) const;
			bool isEqualTo(kind_ptr ptr) const;
			
			bool isNotEqualTo(const_kind_ref ref) const;
			bool isNotEqualTo(kind_ptr ptr) const;
			
			bool isLessThan(const_kind_ref ref) const;
			bool isLessThan(kind_ptr ptr) const;
			
			bool isLessThanOrEqualTo(const_kind_ref ref) const;
			bool isLessThanOrEqualTo(kind_ptr ptr) const;
			
			bool isGreaterThan(const_kind_ref ref) const;
			bool isGreaterThan(kind_ptr ptr) const;
			
			bool isGreaterThanOrEqualTo(const_kind_ref ref) const;
			bool isGreaterThanOrEqualTo(kind_ptr ptr) const;
			
			/*
			* operator identical by addresse calling @isIdenticalTo:, e.g left and right are truely the same.
			*/
			bool operator &= (const_kind_ref ref) const;
			
			/*
			* operators identical and comparison by value calling @compare:.
			*/
			bool operator == (const_kind_ref ref) const;
			bool operator != (const_kind_ref ref) const;
			bool operator <  (const_kind_ref ref) const;
			bool operator <= (const_kind_ref ref) const;
			bool operator >  (const_kind_ref ref) const;
			bool operator >= (const_kind_ref ref) const;
		
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
			friend inline std::ostream & operator << (std::ostream & os, const_kind_ref ref)
			{ os << ref.stringValue(); return os; }
			
			friend inline std::ostream & operator << (std::ostream & os, const_kind_ptr ptr)
			{ if (ptr) { os << ptr->stringValue(); } return os; }
			
		private:
			uintptr_t sig() const;
			const std::string addr() const;
			bool mutability() const;
			
		private:
			std::unordered_map<std::string, kind_ptr> m_attrs;
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