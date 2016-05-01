//
// nutrt-uri.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_URI_HPP
#define COCONUT_RUNTIME_URI_HPP

namespace coconut {
	namespace runtime {
		namespace traits {
	
COCONUT_PRIVATE class COCONUT_VISIBLE uri COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.uri, uri)

public:
	uri();
	uri(const uri & url);
	uri(const uri & url, bool normalize);
	uri(const std::string & str_url, const uri & url, bool normalize);
	uri(const std::string & str_url, const std::string & str_base_url, bool normalize);
	uri(const std::string & str_url, bool is_filepath, bool normalize);
	uri(const std::string & scheme, const std::string & host, const std::string & path, bool normalize);
	uri(const std::string & str_url);
	~uri();
	
public:
	COCONUT_CLASSMETHOD std::string escape(const std::string & in, bool space_as_plus = false);
	COCONUT_CLASSMETHOD std::string unescape(const std::string & in, bool plus_as_space = false);
	COCONUT_CLASSMETHOD bool is_scheme(const std::string & scheme);
	
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
	std::uint16_t port() const;
	const std::string path() const;
	const std::string parameter() const;
	const std::string query() const;
	const std::string fragment() const;
	
	const std::map<std::string, std::string> components() const;
	const std::map<std::string, std::string> parameters() const;

private:
	std::map<std::string, std::string> m_components;
	std::map<std::string, std::string> m_parameters;
	
	std::uint16_t m_port;
	bool m_isfile_url;
	bool m_isvalid_url;
};
	
}}} /* EONS */

#endif /* !COCONUT_RUNTIME_URI_HPP */

/* EOF */