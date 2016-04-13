//
// hash.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/stream.hpp>

#ifndef COCONUT_RUNTIME_HASH_HPP
#define COCONUT_RUNTIME_HASH_HPP

namespace coconut
{
	namespace runtime
	{
		namespace hash
		{
			COCONUT_PRIVATE class COCONUT_VISIBLE sha_base
			{
			COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.hash.sha_base, hash.sha_base)
			
			protected:
				sha_base();
				sha_base(std::size_t blocksize, std::size_t digestsize);
				virtual ~sha_base();
			
			public:
				void add(const void * bytes, std::size_t length);
				const std::vector<char> hex(bool uppercase = false);
				const std::vector<std::uint8_t> raw();
				
			private:
				void process_buffer();
			
			public:
				virtual void reset() = 0;
				
			protected:
				virtual void process_block(const void * block) = 0;
				
			protected:
				std::size_t m_blocksize;
				std::size_t m_digestsize;
				std::uint64_t m_nbytes;
				std::size_t m_bufsize;
				std::uint8_t * m_buf;
				std::uint8_t * m_bufextra;
				std::uint32_t * m_hash;
			};
			
			COCONUT_PRIVATE class COCONUT_VISIBLE sha1 COCONUT_FINAL : public sha_base
			{
			COCONUT_CLASSDECLARE(coconut.runtime.hash.sha1, hash.sha_base.sha1)
				
			public:
				sha1();
				virtual ~sha1();
			
			public:
				virtual void reset()
				COCONUT_FINAL_OVERRIDE;
				
			protected:
				virtual void process_block(const void * block)
				COCONUT_FINAL_OVERRIDE;
			};
			
			COCONUT_PRIVATE class COCONUT_VISIBLE sha256 COCONUT_FINAL : public sha_base
			{
			COCONUT_CLASSDECLARE(coconut.runtime.hash.sha256, hash.sha_base.sha256)
			
			public:
				sha256();
				virtual ~sha256();
				
			public:
				virtual void reset()
				COCONUT_FINAL_OVERRIDE;
				
			protected:
				virtual void process_block(const void * block)
				COCONUT_FINAL_OVERRIDE;
			};
			
			COCONUT_VISIBLE
			const std::vector<char> sha1_hex(const void * bytes, std::size_t len);
			
			COCONUT_VISIBLE
			const std::vector<char> sha1_hex(stream::imstream & in_binary);
			
			COCONUT_VISIBLE
			const std::vector<char> sha1_hex(stream::ifstream & in_binary);
			
			COCONUT_VISIBLE
			const std::vector<std::uint8_t> sha1_raw(const void * bytes, std::size_t len);
			
			COCONUT_VISIBLE
			const std::vector<std::uint8_t> sha1_raw(stream::imstream & in_binary);
			
			COCONUT_VISIBLE
			const std::vector<std::uint8_t> sha1_raw(stream::ifstream & in_binary);
			
			COCONUT_VISIBLE
			const std::vector<char> sha256_hex(const void * bytes, std::size_t len);
			
			COCONUT_VISIBLE
			const std::vector<char> sha256_hex(stream::imstream & in_binary);
			
			COCONUT_VISIBLE
			const std::vector<char> sha256_hex(stream::ifstream & in_binary);
			
			COCONUT_VISIBLE
			const std::vector<std::uint8_t> sha256_raw(const void * bytes, std::size_t len);
			
			COCONUT_VISIBLE
			const std::vector<std::uint8_t> sha256_raw(stream::imstream & in_binary);
			
			COCONUT_VISIBLE
			const std::vector<std::uint8_t> sha256_raw(stream::ifstream & in_binary);
		}
	}
}

#endif /* !COCONUT_RUNTIME_HASH_HPP */
		
/* EOF */