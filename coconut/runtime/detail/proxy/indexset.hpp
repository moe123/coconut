//
// indexset.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_INDEXSET_HPP
#define COCONUT_RUNTIME_INDEXSET_HPP

namespace coconut
{
	namespace runtime
	{
		class irange;
		
		COCONUT_PRIVATE class COCONUT_EXPORT indexset COCONUT_FINAL
		{
		COCONUT_RUNTIME_KDCL(coconut.runtime.indexset, indexset)
			
		public:
			indexset();
			indexset(const indexset & idxset);
			indexset(const irange & rg);
			indexset(std::size_t loc, std::size_t len);
			indexset(std::size_t idx);
			virtual ~indexset();
		
		private:
			static std::size_t pos_greater_eq_loc(const std::vector<irange> & rgs, std::size_t location);
			static std::size_t pos_greater_less_loc(const std::vector<irange> & rgs, std::size_t location);
			static void remove_range_at_pos(std::vector<irange> & rgs, std::size_t position);
			static void insert_range_at_pos(std::vector<irange> & rgs, const irange & rg, std::size_t position);
			static std::size_t find_pos_for_index(const std::vector<irange> & rgs, std::size_t index);
			
		public:
			indexset & operator = (const indexset & idxset);
			int compare(const indexset & other_idxset) const;
			
			std::string to_string() const;
			
			std::size_t count() const;
			std::size_t count_in(const irange & rg) const;
			std::size_t count_in(std::size_t loc, std::size_t len) const;
			
			bool contains(const indexset & idxset) const;
			bool contains(const irange & rg) const;
			bool contains(std::size_t loc, std::size_t len) const;
			bool contains(std::size_t idx = 0) const;
			
			std::size_t first_index() const;
			std::size_t last_index() const;
			
			std::size_t greater(std::size_t idx = 0) const;
			std::size_t greater_equal(std::size_t idx = 0) const;
			std::size_t less(std::size_t idx = 0) const;
			std::size_t less_equal(std::size_t idx = 0) const;
			
			bool intersects(const irange & rg) const;
			bool intersects(std::size_t loc, std::size_t len) const;
			
			void add(const indexset & idxset);
			void add(const irange & rg);
			void add(std::size_t loc, std::size_t len);
			void add(std::size_t idx = 0);
			
			void remove();
			void remove(const indexset & idxset);
			void remove(const irange & rg);
			void remove(std::size_t loc, std::size_t len);
			void remove(std::size_t idx = 0);
		
		public:
			typedef std::vector<irange>::iterator iterator;
			typedef std::vector<irange>::const_iterator const_iterator;
			
			typedef std::vector<irange>::reverse_iterator reverse_iterator;
			typedef std::vector<irange>::const_reverse_iterator const_reverse_iterator;
			
			typedef std::vector<irange>::value_type value_type;
			typedef std::vector<irange>::difference_type difference_type;
			
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
			
		private:
			std::size_t m_len;
			std::vector<irange> m_ranges;
		};
	}
}

#endif /* !COCONUT_RUNTIME_INDEXSET_HPP */

/* EOF */