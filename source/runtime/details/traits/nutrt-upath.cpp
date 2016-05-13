//
// nutrt-upath.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-upath.hpp>
#include <coconut/runtime/details/traits/nutrt-ustring.hpp>

#include <coconut/runtime/details/nutrt-algorithm.hpp>
#include <coconut/runtime/details/nutrt-unicode.hpp>

using namespace coconut::runtime::traits;

#include <source/runtime/builtins/nutrt-unicode_wide.hxx>
#include <source/runtime/builtins/nutrt-filesystem_info.hxx>
#include <source/runtime/builtins/nutrt-upath_absolute.hxx>
#include <source/runtime/builtins/nutrt-upath_detection.hxx>

upath::upath()
: m_components()
{ /* NOP */ }

upath::upath(const upath & path)
: m_components(path.m_components)
{ /* NOP */ }

upath::upath(const ustring & path, dirsep_option option)
: upath(path.to_utf8(), encoding_utf8, option)
{ /* NOP */ }

upath::upath(const std::string & str_path, encoding_option encoding, dirsep_option option)
: m_components()
{
	std::string path;
	if (encoding != encoding_utf8) {
		ustring p(str_path, encoding);
		path = p.to_utf8();
	} else {
		path = str_path;
	}
	builtins::upath_parse(m_components, path, option);
	
	for (const auto & comp : m_components) {
		std::cerr << "+ " << comp << std::endl;
	}
}

upath::upath(const std::u16string & str_path, encoding_option encoding, dirsep_option option)
: upath(unicode::utf16_to_utf8(str_path), encoding_utf8, option)
{ /* NOP */ }

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
	// builtins::upath_absolute(to_utf8_string(option)),
	return upath(
		"",
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
{ return m_components; }

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
	return algorithm::join<std::string>(m_components, sep);
}

const std::u16string upath::to_utf16_string(dirsep_option option) const
{ return unicode::utf8_to_utf16(to_utf8_string(option)); }

/* EOF */
