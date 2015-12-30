//
// upath.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/proxy/upath.hpp>
#include <coconut/runtime/detail/proxy/ustring.hpp>

#include <coconut/runtime/detail/core/algorithm.hpp>
#include <coconut/runtime/detail/core/unicode.hpp>

#include <source/runtime/builtins/proxy_upath_absolute.hxx>

using namespace coconut::runtime;

upath::upath() :
	m_components()
{ /* NOP */ }

upath::upath(const upath & path) :
	m_components(path.m_components)
{ /* NOP */ }

upath::upath(const ustring & path, dirsep_option option) :
	upath(path.to_utf8(), encoding_utf8, option)
{ /* NOP */ }

upath::upath(const std::string & str_path, encoding_option encoding, dirsep_option option) :
	m_components()
{
	std::string path, sep;
	if (encoding != encoding_utf8) {
		ustring p(str_path, encoding);
		path = p.to_utf8();
	} else {
		path = str_path;
	}
	
	switch (option)
	{
		case dirsep_auto:
		{
			if (algorithm::starts_with<std::string>(path, "/")) {
				sep.assign("/");
			} else if (algorithm::starts_with<std::string>(path, "\\")) {
				sep.assign("\\");
			} else {
				size_t n_whack = std::count(path.begin(), path.end(), '/');
				size_t n_slack = std::count(path.begin(), path.end(), '\\');
				if (n_whack >= n_slack) {
					sep.assign("/");
				} else {
					sep.assign("\\");
				}
			}
		}
		break;
		case dirsep_slack:
			sep.assign("\\");
		break;
		default:
			sep.assign("/");
		break;
	}
	m_components = algorithm::split(path, sep);
	// sanitize
}

upath::upath(const std::u16string & str_path, encoding_option encoding, dirsep_option option) :
	m_components()
{
	std::string path, sep;
	ustring p(str_path, encoding);
	path = p.to_utf8();
	switch (option)
	{
		case dirsep_auto:
		{
			if (algorithm::starts_with<std::string>(path, "/")) {
				sep.assign("/");
			} else if (algorithm::starts_with<std::string>(path, "\\")) {
				sep.assign("\\");
			} else {
				size_t n_whack = std::count(path.begin(), path.end(), '/');
				size_t n_slack = std::count(path.begin(), path.end(), '\\');
				if (n_whack >= n_slack) {
					sep.assign("/");
				} else {
					sep.assign("\\");
				}
			}
		}
		break;
		case dirsep_slack:
			sep.assign("\\");
		break;
		default:
			sep.assign("/");
		break;
	}
	m_components = algorithm::split(path, sep);
	// sanitize
}

upath::~upath()
{ /* NOP */ }

upath & upath::operator = (const upath & path)
{
	if (this == &path) {
		return *this;
	}
	m_components = path.m_components;
	return *this;
}

int upath::compare(const upath & other_path) const
{
	return ustring::compare_utf8(
		to_utf8_string(),
		other_path.to_utf8_string(),
		search_insensitive|search_nowidth
	);
}

std::string upath::to_string() const
{
	return to_utf8_string();
}

const upath upath::absolute(dirsep_option option) const
{
	// be smarter about separator
	return upath(
		builtins::upath_absolute(to_utf8_string(option)),
		encoding_utf8,
		option
	);
}

const upath upath::basename() const
{
	return upath(
		m_components.back(), encoding_utf8, dirsep_whack
	);
}

const upath upath::dirname(dirsep_option option) const
{
	std::vector<std::string> components(m_components.begin(), m_components.end());
	if (components.size() > 1) {
		components.pop_back();
	}
	std::string sep;
	switch (option)
	{
		case dirsep_slack:
			sep.assign("\\");
		break;
		default:
			sep.assign("/");
		break;
	}
	return upath(
		algorithm::join<std::string>(m_components, sep), encoding_utf8, option
	);
}

const std::vector<std::string> upath::components() const
{
	return m_components;
}

const std::string upath::to_utf8_string(dirsep_option option) const
{
	std::string sep;
	switch (option)
	{
		case dirsep_slack:
			sep.assign("\\");
		break;
		default:
			sep.assign("/");
		break;
	}
	return sep + algorithm::join<std::string>(m_components, sep);
}

const std::u16string upath::to_utf16_string(dirsep_option option) const
{
	return unicode::utf8_to_utf16(to_utf8_string(option));
}

/* EOF */
