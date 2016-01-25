//
// uri.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_URI_HPP
#define COCONUT_RUNTIME_URI_HPP

namespace coconut
{
	namespace runtime
	{
		COCONUT_PRIVATE class COCONUT_EXPORT uri COCONUT_FINAL
		{
		COCONUT_RUNTIME_KDCL(coconut.runtime.uri, uri)
		
		public:
			uri();
			uri(const uri & url);
			uri(const uri & url, bool normalize);
			uri(const std::string & str_url, const uri & url, bool normalize);
			uri(const std::string & str_url, const std::string & str_base_url, bool normalize);
			uri(const std::string & str_url, bool is_filepath, bool normalize);
			uri(const std::string & scheme, const std::string & host, const std::string & path, bool normalize);
			uri(const std::string & str_url);
			virtual ~uri();
			
		public:
			static std::string escape(const std::string & in, bool space_as_plus = false);
			static std::string unescape(const std::string & in, bool plus_as_space = false);
			static bool is_scheme(const std::string & scheme);
			
		public:
			uri & operator = (const uri & url);
			int compare(const uri & other_url) const;
			
			std::string to_string() const;
			
			bool is_valid() const;
			bool is_file_url() const;
			
			const std::string specifier() const;
			
			const std::string scheme() const;
			const std::string user() const;
			const std::string password() const;
			const std::string host() const;
			std::size_t port() const;
			const std::string path() const;
			const std::string parameter() const;
			const std::string query() const;
			const std::string fragment() const;
			
			const std::map<std::string, std::string> parameters() const;
			const std::map<std::string, std::string> components() const;
		
		private:
			std::map<std::string, std::string> m_components;
			std::map<std::string, std::string> m_parameters;
			
			std::size_t m_port;
			bool m_isfile_url;
			bool m_isvalid_url;
		};
	}
}

#endif /* !COCONUT_RUNTIME_URI_HPP */

/* EOF */