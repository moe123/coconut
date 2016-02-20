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
#endif

namespace coconut
{
	namespace runtime
	{
		namespace builtins
		{
#if defined(__MICROSOFT__)
			namespace { std::mutex filesystem_mtx; }
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::int64_t filesystem_mtime(const std::wstring & filepath)
			{
				std::int64_t nanosecond = 0LL;
				if (filepath) {
					HANDLE file_h = CreateFileW(
						filepath.c_str(),
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
						x /=10;
						x -= 11644473600000000LL;
						x *= 1000LL;
						nanosecond = static_cast<std::int64_t>(x);
					}
				}
				return nanosecond;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::int64_t filesystem_atime(const std::wstring & filepath)
			{
				std::int64_t nanosecond = 0LL;
				if (filepath) {
					HANDLE file_h = CreateFileW(
						filepath.c_str(),
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
						x /=10;
						x -= 11644473600000000LL;
						x *= 1000LL;
						nanosecond = static_cast<std::int64_t>(x);
					}
				}
				return nanosecond;
			}

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool filesystem_isdir(const std::wstring & filepath)
			{
				if (filepath) {
					DWORD attrs = GetFileAttributesW(filepath.c_str());
					return (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY));
				}
				return false;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool filesystem_isfile(const std::wstring & filepath)
			{
				if (filepath) {
					DWORD attrs = GetFileAttributesW(filepath.c_str());
					return (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY));
				}
				return false;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool filesystem_exists(const WCHAR * filepath)
			{
				if (filepath) {
					DWORD attrs = GetFileAttributesW(filepath);
					return (attrs != INVALID_FILE_ATTRIBUTES);
				}
				return false;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool filesystem_resolve_v1(const std::wstring & filepath_in, std::wstring & filepath_out)
			{
				bool result = false;
				HANDLE file_h = CreateFileW(
					filepath_in.c_str(),
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
						filepath_out = std::move(wout);
						result = true;
					}
					CloseHandle(file_h);
				}
				return result;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::string filesystem_resolve_v0(const std::wstring & filepath_in, std::wstring & filepath_out)
			{
				std::unique_lock<std::mutex> auto_lock(filesystem_mtx);
				bool result = false;
				WCHAR buf[1024 + 1];
				DWORD len;
				if (0 != (len = GetFullPathNameW(filepath_in.c_str(), sizeof(buf), buf, NULL)) {
					if (len < sizeof(buf)) {
						std::wstring wout(buf, len);
						if (filesystem_exists(wout) {
							filepath_out = std::move(wout);
							result = true;
						}
					}
				}
				return result;
			}
#endif
		}
	}
}

/* EOF */