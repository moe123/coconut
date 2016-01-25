//
// Path.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Path.hpp>
#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/String.hpp>

using namespace coconut;

Path::Path() :
	Object(PathClass),
	m_impl()
{ /* NOP */ }

Path::Path(const Path & path) :
	Object(PathClass),
	m_impl(path.m_impl)
{ /* NOP */ }

Path::Path(const String & path) :
	Object(PathClass),
	m_impl(path.m_impl, DirectorySeparatorAuto)
{ /* NOP */ }

Path::Path(const char * utf8_path) :
	Object(PathClass),
	m_impl(utf8_path, StringEncodingUTF8, DirectorySeparatorAuto)
{ /* NOP */ }

Path::Path(const char16_t * utf16_path) :
	Object(PathClass),
	m_impl(utf16_path, StringEncodingUTF16, DirectorySeparatorAuto)
{ /* NOP */ }

Path::~Path()
{ /* NOP */ }

#pragma mark -

Owning<Path> Path::with(const Path & path)
{ return ptr_create<Path>(path); }

Owning<Path> Path::with(const String & path)
{ return ptr_create<Path>(path); }

Owning<Path> Path::with(const char * utf8_path)
{ return ptr_create<Path>(utf8_path); }

Owning<Path> Path::with(const char16_t * utf16_path)
{ return ptr_create<Path>(utf16_path); }

#pragma mark -

Owning<Any> Path::copy() const
{ return ptr_create<Path>(*this); }

#pragma mark -

ComparisonResult Path::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	return OrderedDescending;
}

#pragma mark -

std::string Path::stringValue() const
{ return UTF8String(); }

std::u16string Path::string16Value() const
{ return UTF16String(); }

#pragma mark -

const Array Path::components() const
{
	Array comps;
	return comps;
}

const Path Path::absolute(DirectorySeparatorOption option)
{
	Path path;
	path.m_impl = m_impl.absolute(option);
	return path;
}

const Path Path::basename() const
{
	Path path;
	path.m_impl = m_impl.basename();
	return path;
}

const Path Path::dirname(DirectorySeparatorOption option) const
{
	Path path;
	path.m_impl = m_impl.dirname(option);
	return path;
}

const std::string Path::UTF8String(DirectorySeparatorOption option) const
{ return m_impl.to_utf8_string(option); }

const std::u16string Path::UTF16String(DirectorySeparatorOption option) const
{ return m_impl.to_utf16_string(option); }

/* EOF */