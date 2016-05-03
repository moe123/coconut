//
// nutrt-uri.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-uri.hpp>
#include <coconut/runtime/details/nutrt-algorithm.hpp>

using namespace coconut::runtime::traits;

#include <source/runtime/builtins/nutrt-uri_escaping.hxx>
#include <source/runtime/builtins/nutrt-uri_joining.hxx>
#include <source/runtime/builtins/nutrt-uri_parsing.hxx>

uri::uri()
: m_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, m_parameters()
, m_port(0)
, m_isfile_url(false)
, m_isvalid_url(false)
{ /* NOP */ }

uri::uri(const uri & url)
: m_components(url.m_components)
, m_parameters(url.m_parameters)
, m_port(url.m_port)
, m_isfile_url(url.m_isfile_url)
, m_isvalid_url(url.m_isvalid_url)
{ /* NOP */ }

uri::uri(const uri & url, bool normalize)
: m_components(url.m_components)
, m_parameters(url.m_parameters)
, m_port(url.m_port)
, m_isfile_url(url.m_isfile_url)
, m_isvalid_url(url.m_isvalid_url)
{
	if (normalize) {
		m_components.clear();
		m_components =
		{
			{ "string", "" },
			{ "specifier", "" },
			{ "scheme", "" },
			{ "user", "" },
			{ "password", "" },
			{ "host", "" },
			{ "port", "" },
			{ "path", "" },
			{ "parameter", "" },
			{ "query", "" },
			{ "fragment", "" }
		};
		m_parameters.clear();
		m_port = 0;
		m_isvalid_url = parseit(
			url.to_string()
			, m_components
			, m_parameters
			, m_isfile_url
			, m_port
			, normalize
		);
		if (m_isvalid_url && m_components.at("port").size()) {
			m_port = algorithm::to_numeric<std::size_t>(m_components.at("port"));
		}
	}
}

uri::uri(const std::string & str_url, const uri & url, bool normalize)
: m_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, m_parameters()
, m_port(0)
, m_isfile_url(false)
, m_isvalid_url(false)
{
	std::string str_abs_url;
	if (joinit(str_url, url.to_string(), str_abs_url, normalize)) {
		m_isvalid_url = parseit(
			str_abs_url
			, m_components
			, m_parameters
			, m_isfile_url
			, m_port
			, normalize
		);
		if (m_isvalid_url && m_components.at("port").size()) {
			m_port = algorithm::to_numeric<std::size_t>(m_components.at("port"));
		}
	}
}

uri::uri(const std::string & str_url, const std::string & str_base_url, bool normalize)
: m_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, m_parameters()
, m_port(0)
, m_isfile_url(false)
, m_isvalid_url(false)
{
	std::string str_abs_url;
	if (joinit(str_url, str_base_url, str_abs_url, normalize)) {
		m_isvalid_url = parseit(
			str_abs_url
			, m_components
			, m_parameters
			, m_isfile_url
			, m_port
			, normalize
		);
		if (m_isvalid_url && m_components.at("port").size()) {
			m_port = algorithm::to_numeric<std::size_t>(m_components.at("port"));
		}
	}
}

uri::uri(const std::string & str_url, bool is_filepath, bool normalize)
: m_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, m_parameters()
, m_port(0)
, m_isfile_url(false)
, m_isvalid_url(false)
{
	if (is_filepath) {
		std::string abs_uri;
		if (builtins::uri_filetouri(str_url, abs_uri)) {
			m_isfile_url = true;
			m_isvalid_url = parseit(
				abs_uri
				, m_components
				, m_parameters
				, m_isfile_url
				, m_port
				, normalize
			);
		}
	} else {
		m_isvalid_url = parseit(
			str_url
			, m_components
			, m_parameters
			, m_isfile_url
			, m_port
			, normalize
		);
	}
	if (m_isvalid_url && m_components.at("port").size()) {
		m_port = algorithm::to_numeric<std::size_t>(m_components.at("port"));
	}
}

uri::uri(const std::string & scheme, const std::string & host, const std::string & path, bool normalize)
: m_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, m_parameters()
, m_port(0)
, m_isfile_url(false)
, m_isvalid_url(false)
{
	std::string in = scheme;
	in += "://";
	in += host;
	in += path;
	m_isvalid_url = parseit(
		in
		, m_components
		, m_parameters
		, m_isfile_url
		, m_port
		, normalize
	);
	if (m_isvalid_url && m_components.at("port").size()) {
		m_port = algorithm::to_numeric<std::size_t>(m_components.at("port"));
	}
}

uri::uri(const std::string & str_url)
: uri(str_url, !builtins::uri_have_scheme(str_url), true)
{ /* NOP */ }

uri::~uri()
{ /* NOP */ }

#pragma mark -

std::string uri::escape(const std::string & in, bool space_as_plus)
{ return builtins::uri_escape(in, space_as_plus); }

std::string uri::unescape(const std::string & in, bool plus_as_space)
{ return builtins::uri_escape(in, plus_as_space); }

bool uri::is_scheme(const std::string & scheme)
{ return builtins::uri_valid_scheme(scheme); }

#pragma mark -

bool uri::parseit(
	const std::string & str_url,
	std::map<std::string, std::string> & components,
	std::map<std::string, std::string> & parameters,
	bool & is_file,
	std::uint16_t & port,
	bool normalize
) {
	return builtins::uri_parse(
		str_url
		, components
		, parameters
		, is_file
		, port
		, normalize
	);
}

bool uri::joinit(
	const std::string & str_relative_url,
	const std::string & str_base_url,
	std::string & str_url,
	bool normalize
) {
	return builtins::uri_join(
		str_relative_url
		, str_base_url
		, str_url
		, normalize
	);
}

#pragma mark -

uri & uri::operator = (const uri & url)
{
	if (this == &url) {
		return *this;
	}
	
	m_components = url.m_components;
	m_parameters = url.m_parameters;
	m_port = url.m_port;
	m_isfile_url = url.m_isfile_url;
	m_isvalid_url = url.m_isvalid_url;
	
	return *this;
}

int uri::compare(const uri & other_url) const
{ return algorithm::icmp(to_string(), other_url.to_string()); }

#pragma mark -

std::string uri::to_string() const
{
	std::string abs;
	abs += m_components.at("scheme");
	abs += ":";
	abs += m_components.at("specifier");
	return abs;
}

#pragma mark -

bool uri::is_valid() const
{ return m_isvalid_url; }

bool uri::is_file_url() const
{ return m_isfile_url; }

#pragma mark -

const std::string & uri::specifier() const
{ return m_components.at("specifier"); }

#pragma mark -

const std::string & uri::scheme() const
{ return m_components.at("scheme"); }

const std::string & uri::user() const
{ return m_components.at("user"); }

const std::string & uri::password() const
{ return m_components.at("password"); }

const std::string & uri::host() const
{ return m_components.at("host"); }

std::uint16_t uri::port() const
{ return m_port; }

const std::string & uri::path() const
{ return m_components.at("path"); }

const std::string & uri::parameter() const
{ return m_components.at("parameter"); }

const std::string & uri::query() const
{ return m_components.at("query"); }

const std::string & uri::fragment() const
{ return m_components.at("fragment"); }

#pragma mark -

const std::map<std::string, std::string> & uri::components() const
{ return m_components; }

const std::map<std::string, std::string> & uri::parameters() const
{ return m_parameters; }

/* EOF */