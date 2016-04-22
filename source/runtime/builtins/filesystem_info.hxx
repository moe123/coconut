//
// filesystem_info.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#if defined(__MICROSOFT__)
	#undef UNICODE
	#undef _UNICODE

	#define UNICODE 1
	#define _UNICODE 1

	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <rpcdce.h>
	#include <wincrypt.h>
	#include <windows.h>
#else
	#include <sys/types.h>
	#include <sys/stat.h>
#endif

namespace coconut {
	namespace runtime {
		namespace builtins {

#if defined(__MICROSOFT__)

namespace { std::mutex fs_mtx; }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::wstring fs_lname_prefix(const std::wstring & utf16_fullpath)
{
	// \\\\?\\

	return L"";
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::wstring fs_lname_strip(const std::wstring & utf16_fullpath)
{ return L""; }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t fs_btime(const std::wstring & utf16_fullpath)
{
	std::int64_t nanosecond = 0LL;
	if (utf16_fullpath.size()) {
		HANDLE file_h = CreateFileW(
			utf16_fullpath.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		
		if (file_h != INVALID_HANDLE_VALUE) {
			FILETIME ft;
			GetFileTime(file_h, &ft, NULL, NULL);
			CloseHandle(file_h);
			
			long long x;
			x = static_cast<long long>(ft.dwHighDateTime);
			x <<= 32;
			x |= static_cast<long long>(ft.dwLowDateTime);
			x /= 10;
			x -= 11644473600000000LL;
			x *= 1000LL;
			nanosecond = static_cast<std::int64_t>(x);
		}
	}
	return nanosecond;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t fs_mtime(const std::wstring & utf16_fullpath)
{
	std::int64_t nanosecond = 0LL;
	if (utf16_fullpath.size()) {
		HANDLE file_h = CreateFileW(
			utf16_fullpath.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		
		if (file_h != INVALID_HANDLE_VALUE) {
			FILETIME ft;
			GetFileTime(file_h, NULL, NULL, &ft);
			CloseHandle(file_h);
			
			long long x;
			x = static_cast<long long>(ft.dwHighDateTime);
			x <<= 32;
			x |= static_cast<long long>(ft.dwLowDateTime);
			x /= 10;
			x -= 11644473600000000LL;
			x *= 1000LL;
			nanosecond = static_cast<std::int64_t>(x);
		}
	}
	return nanosecond;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t fs_atime(const std::wstring & utf16_fullpath)
{
	std::int64_t nanosecond = 0LL;
	if (utf16_fullpath.size()) {
		HANDLE file_h = CreateFileW(
			utf16_fullpath.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		
		if (file_h != INVALID_HANDLE_VALUE) {
			FILETIME ft;
			GetFileTime(file_h, NULL, &ft, NULL);
			CloseHandle(file_h);
			
			long long x;
			x = static_cast<long long>(ft.dwHighDateTime);
			x <<= 32;
			x |= static_cast<long long>(ft.dwLowDateTime);
			x /= 10;
			x -= 11644473600000000LL;
			x *= 1000LL;
			nanosecond = static_cast<std::int64_t>(x);
		}
	}
	return nanosecond;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool fs_isdir(const std::wstring & utf16_fullpath)
{
	if (utf16_fullpath.size()) {
		DWORD attrs = GetFileAttributesW(utf16_fullpath.c_str());
		return (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY) && !(attrs & FILE_ATTRIBUTE_REPARSE_POINT));
	}
	return false;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool fs_islink(const std::wstring & utf16_fullpath)
{
	if (utf16_fullpath.size()) {
		DWORD attrs = GetFileAttributesW(utf16_fullpath.c_str());
		return (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_REPARSE_POINT));
	}
	return false;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool fs_isfile(const std::wstring & utf16_fullpath)
{
	if (utf16_fullpath.size()) {
		DWORD attrs = GetFileAttributesW(utf16_fullpath.c_str());
		return (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY) && !(attrs & FILE_ATTRIBUTE_REPARSE_POINT));
	}
	return false;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool fs_exists(const std::wstring & utf16_fullpath)
{
	if (utf16_fullpath.size()) {
		DWORD attrs = GetFileAttributesW(utf16_fullpath.c_str());
		return (attrs != INVALID_FILE_ATTRIBUTES);
	}
	return false;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool fs_resolve_v1(const std::wstring & utf16_path_in, std::wstring & utf16_fullpath_out)
{
	bool result = false;
	
	// TODO HANDLING LONG NAME MARKER
	if (utf16_fullpath.size()) {
		HANDLE file_h;
		
		if (!fs_isdir(utf16_path_in)) {
			file_h = CreateFileW(
				utf16_path_in.c_str(),
				GENERIC_READ,
				FILE_SHARE_READ|FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);
			
			if (file_h != INVALID_HANDLE_VALUE) {
				WCHAR buf[1024 + 1];
				DWORD len;
				if (0 != (len = GetFinalPathNameByHandleW(file_h, buf, sizeof(buf), FILE_NAME_NORMALIZED))) {
					std::wstring wout(buf, len);
					utf16_fullpath_out = std::move(wout);
					result = true;
				}
				CloseHandle(file_h);
			}
		}
		if (!result) {
			file_h = CreateFileW(
				utf16_path_in.c_str(),
				GENERIC_READ,
				FILE_SHARE_READ|FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_FLAG_BACKUP_SEMANTICS,
				NULL
			);
			
			if (file_h != INVALID_HANDLE_VALUE) {
				WCHAR buf[1024 + 1];
				DWORD len;
				if (0 != (len = GetFinalPathNameByHandleW(file_h, buf, sizeof(buf), FILE_NAME_NORMALIZED))) {
					std::wstring wout(buf, len);
					utf16_fullpath_out = std::move(wout);
					result = true;
				}
				CloseHandle(file_h);
			}
			
		}
	}
	return result;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool fs_resolve_v0(const std::wstring & utf16_path_in, std::wstring & utf16_fullpath_out)
{
	std::unique_lock<std::mutex> auto_lock(fs_mtx);
	bool result = false;
	WCHAR buf[1024 + 1];
	DWORD len;
	if (0 != (len = GetFullPathNameW(utf16_path_in.c_str(), sizeof(buf), buf, NULL)) {
		if (len < sizeof(buf)) {
			std::wstring wout(buf, len);
			if (fs_exists(wout) {
				utf16_fullpath_out = std::move(wout);
				result = true;
			}
		}
	}
	return result;
}

#else

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t fs_btime(const std::string & utf8_path)
{
	std::int64_t nanosecond = 0LL;
	if (utf8_path.size()) {
		struct stat attr;
		stat(utf8_path.c_str(), &attr);
#if defined(__APPLE__)
	#ifndef st_birthtime
		nanosecond = static_cast<std::int64_t>(attr.st_birthtime * 1000000000LL);
	#else
		nanosecond = static_cast<std::int64_t>((attr.st_birthtimespec.tv_sec * 1000000000LL) + attr.st_birthtimespec.tv_nsec);
	#endif
#else
	#if defined(__linux__) || defined(__gnu_linux__)
		nanosecond = static_cast<std::int64_t>((attr.st_ctim.tv_sec * 1000000000LL) + attr.st_ctim.tv_nsec);
	#else
		// __FreeBSD__ 10 yes, __DragonFly__ , __OpenBSD__, __NetBSD__ ?
		nanosecond = static_cast<std::int64_t>((attr.st_birthtim.tv_sec * 1000000000LL) + attr.st_birthtim.tv_nsec);
	#endif
#endif
	}
	return nanosecond;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t fs_mtime(const std::string & utf8_path)
{
	std::int64_t nanosecond = 0LL;
	if (utf8_path.size()) {
		struct stat attr;
		stat(utf8_path.c_str(), &attr);
#if defined(__APPLE__)
	#ifndef st_mtime
		nanosecond = static_cast<std::int64_t>(attr.st_mtime * 1000000000LL);
	#else
		nanosecond = static_cast<std::int64_t>((attr.st_mtimespec.tv_sec * 1000000000LL) + attr.st_mtimespec.tv_nsec);
	#endif
#else
		// __FreeBSD__ 10 yes, __linux__  yes, __DragonFly__ , __OpenBSD__, __NetBSD__ ?
		nanosecond = static_cast<std::int64_t>((attr.st_mtim.tv_sec * 1000000000LL) + attr.st_mtim.tv_nsec);
#endif
	}
	return nanosecond;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t fs_atime(const std::string & utf8_path)
{
	std::int64_t nanosecond = 0LL;
	if (utf8_path.size()) {
		struct stat attr;
		stat(utf8_path.c_str(), &attr);
#if defined(__APPLE__)
	#ifndef st_atime
		nanosecond = static_cast<std::int64_t>(attr.st_atime * 1000000000LL);
	#else
		nanosecond = static_cast<std::int64_t>((attr.st_atimespec.tv_sec * 1000000000LL) + attr.st_atimespec.tv_nsec);
	#endif
#else
		// __FreeBSD__  10 yes, __linux__  yes, __DragonFly__, __OpenBSD__, __NetBSD__ ?
		nanosecond = static_cast<std::int64_t>((attr.st_atim.tv_sec * 1000000000LL) + attr.st_atim.tv_nsec);
#endif
	}
	return nanosecond;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool fs_exists(const std::string & utf8_path)
{
	if (utf8_path.size()) {
		return access(utf8_path.c_str(), F_OK) == 0;
	}
	return false;
}

bool fs_resolve(const std::string & utf8_path_in, std::string & utf8_path_out)
{
	bool result = false;
	char buffer[PATH_MAX + 1];
	std::memset(buffer, 0, PATH_MAX + 1);
	char * pathname;
	if (NULL != (pathname = realpath(utf8_path_in.c_str(), buffer))) {
		utf8_path_out.assign(pathname);
		result = true;
	}
	return result;
}

#endif

}}} /* EONS */

/* EOF */