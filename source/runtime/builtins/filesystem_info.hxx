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
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::int64_t filesystem_mtime(const wchar_t * filepath)
			{
				std::int64_t nanosecond = 0LL;
				if (filepath) {
					HANDLE file_h = CreateFileW(
						filepath,
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
			std::int64_t filesystem_atime(const wchar_t * filepath)
			{
				std::int64_t nanosecond = 0LL;
				if (filepath) {
					HANDLE file_h = CreateFileW(
						filepath,
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
			bool filesystem_isdir(const wchar_t * filepath)
			{
				if (filepath) {
					DWORD attrs = GetFileAttributesW(filepath);
					return (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY));
				}
				return false;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool filesystem_isfile(const wchar_t * filepath)
			{
				if (filepath) {
					DWORD attrs = GetFileAttributesW(filepath);
					return (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY));
				}
				return false;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool filesystem_fileexists(const wchar_t * filepath)
			{
				return filesystem_isfile(filepath) || filesystem_isdir(filepath);
			}
#endif
		}
	}
}

/* EOF */