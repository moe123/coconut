//
// Data.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_DATA_HPP
#define COCONUT_FOUNDATION_DATA_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT Data : public Object
	{
	COCONUT_KDCL(coconut.Data, Object.Data)
	
	public:
		Data();
		Data(const Data & dat);
		Data & operator = (const Data & dat) = default;
		
		Data(Data && dat);
		
		Data(const Data & dat, bool b64_decode);
		Data(const Data && dat, bool b64_decode);
		Data(Data && dat, bool b64_decode);
		
		Data(const std::uint8_t * in, std::size_t length, bool b64_decode = false);
		Data(const char * in, std::size_t length, bool b64_decode = false);
		
		template <typename IterT>
		Data(IterT && beg, IterT && end, bool b64_decode) :
			Object(DataClass),
			m_impl(std::forward<IterT>(beg), std::forward<IterT>(end), b64_decode)
		{ /* NOP */ }
		
		Data(const std::uint16_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		Data(const std::uint32_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		Data(const std::uint64_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		
		Data(const std::int16_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		Data(const std::int32_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		Data(const std::int64_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		
		template <typename IterT>
		Data(IterT && beg, IterT && end, DataPackingOption option) :
			Object(DataClass),
			m_impl(std::forward<IterT>(beg), std::forward<IterT>(end), option)
		{ /* NOP */ }
		
		Data(const Path & path, bool b64_decode = false);
		Data(const URL & url, bool b64_decode = false);
		
		virtual ~Data();
		
		COCONUT_KTOR Owning<Data> with();
		COCONUT_KTOR Owning<Data> with(const Data & dat);
		COCONUT_KTOR Owning<Data> with(Data && dat);
		
		COCONUT_KTOR Owning<Data> with(const Data & dat, bool b64_decode);
		COCONUT_KTOR Owning<Data> with(Data && dat, bool b64_decode);
		
		COCONUT_KTOR Owning<Data> with(const std::uint8_t * in, std::size_t length, bool b64_decode = false);
		COCONUT_KTOR Owning<Data> with(const char * in, std::size_t length, bool b64_decode = false);
		
		template <typename IterT>
		COCONUT_KTOR Owning<Data> with(IterT && beg, IterT && end, bool b64_decode)
		{ return ptr_create<Data>(std::forward<IterT>(beg), std::forward<IterT>(end), b64_decode); }
		
		COCONUT_KTOR Owning<Data> with(const std::uint16_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		COCONUT_KTOR Owning<Data> with(const std::uint32_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		COCONUT_KTOR Owning<Data> with(const std::uint64_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		
		COCONUT_KTOR Owning<Data> with(const std::int16_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		COCONUT_KTOR Owning<Data> with(const std::int32_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);
		COCONUT_KTOR Owning<Data> with(const std::int64_t * in, std::size_t length, DataPackingOption option = DataPackingBigEndian);

		template <typename IterT>
		COCONUT_KTOR Owning<Data> with(IterT && beg, IterT && end, DataPackingOption option)
		{ return ptr_create<Data>(std::forward<IterT>(beg), std::forward<IterT>(end), option); }
		
		COCONUT_KTOR Owning<Data> with(const Path & path, bool b64_decode = false);
		COCONUT_KTOR Owning<Data> with(const URL & url, bool b64_decode = false);
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		// virtual Owning<Any> mutableCopy() const
		// COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
		
		const std::uint8_t * bytes() const;
		
		bool getBytes(std::uint8_t * buf, std::size_t length) const;
		bool getBytes(std::uint8_t * buf, const Range & rg) const;
		bool getBytes(std::uint8_t * buf, std::size_t location, std::size_t length) const;
		
		bool getBytes(char * buf, std::size_t length) const;
		bool getBytes(char * buf, const Range & rg) const;
		bool getBytes(char * buf, std::size_t location, std::size_t length) const;
		
		bool getBytes(std::vector<std::uint8_t> & bv) const;
		bool getBytes(std::vector<std::uint8_t> & bv, std::size_t length) const;
		bool getBytes(std::vector<std::uint8_t> & bv, const Range & rg) const;
		bool getBytes(std::vector<std::uint8_t> & bv, std::size_t location, std::size_t length) const;
		
		const Data base64EncodedData(ChunkSplitOption option = ChunkSplitNone) const;
		const Data subdataWithRange(const Range & rg) const;
		const Data subdataWithRange(std::size_t location, std::size_t length) const;
		
		bool getBase64EncodedValue(std::vector<char> & out, ChunkSplitOption option = ChunkSplitNone) const;
		
		const std::string sha1Value() const;
		const std::string sha256Value() const;
		
		bool writeToFile(const Path & path, bool atomically = true) const;
		bool writeToURL(const URL & url, bool atomically = true) const;
	
	public:
		const std::uint8_t operator [] (std::size_t index) const;

	public:
		friend inline std::ostream & operator << (std::ostream & os, const Owning<Data> ptr)
		{ if (ptr) { os << ptr->stringValue(); } return os; }
		
	protected:
		typedef runtime::bytebuf impl_type;
		
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
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_DATA_HPP */

/* EOF */