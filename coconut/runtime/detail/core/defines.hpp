//
// defines.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <cfloat>
#include <cmath>
#include <ctgmath>
#include <cstdarg>
#include <cstddef>
#include <cinttypes>
#include <cstdint>
#include <cstdlib>
#include <climits>
#include <ctime>

#include <algorithm>
#include <array>
#include <atomic>
#include <codecvt>
#include <chrono>
#include <complex>
#include <fstream>
#include <functional>
#include <future>
#include <queue>
#include <iomanip>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#if __MACH__
	#include <mach/clock.h>
	#include <mach/mach.h>
	#include <mach/mach_error.h>
#endif

#if !defined(__CYGWIN__) && (defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64))
	#ifndef __MICROSOFT__
		#define __MICROSOFT__ 1
	#endif
	#ifndef _SCL_SECURE_NO_WARNINGS
		#define _SCL_SECURE_NO_WARNINGS 1
	#endif
	#ifndef _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS 1
	#endif

	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <rpcdce.h>
	#include <wincrypt.h>
	#include <windows.h>

	#ifndef _MSC_VER
		#include <sys/param.h>
	#endif

	#ifndef SIZE_MAX
		#if defined(WIN64) || defined(_WIN64)
			#define SIZE_MAX _UI64_MAX
		#else
			#define SIZE_MAX _UI32_MAX
		#endif
	#endif

#endif

#include <coconut/runtime/detail/core/_endian.hpp>
#include <coconut/runtime/detail/core/_intrinsic.hpp>
#include <coconut/runtime/detail/core/_inifini.hpp>

#ifndef COCONUT_RUNTIME_DEFINE_HPP
#define COCONUT_RUNTIME_DEFINE_HPP

	#ifndef COCONUT_API_VERSION
		#define COCONUT_API_VERSION 1_0_0
	#endif

	#define COCONUT_PPCAT_NX(A, B) A ## B
	#define COCONUT_PPCAT(A, B) COCONUT_PPCAT_NX(A, B)

	#define COCONUT_STRINGIZE_NX(A) #A
	#define COCONUT_STRINGIZE(A) COCONUT_STRINGIZE_NX(A)

	#ifndef coconut
		#if DEBUG || _DEBUG
			#define coconut \
				COCONUT_PPCAT(coconut_debug_, COCONUT_API_VERSION)
		#else
			#define coconut \
				COCONUT_PPCAT(coconut_, COCONUT_API_VERSION)
		#endif
	#endif

	#define COCONUT_UNUSED(S) (void)(S) /* unused */
	// #define COCONUT_UNUSED(S) do { (void)(S); } while (0) /* unused */

	#define COCONUT_PRIVATE
	#define COCONUT_PUBLIC
	#define COCONUT_PROTECTED
	#define COCONUT_ABSTRACT

	#define __COCONUT_BEGIN_DECLS extern "C" {
	#define __COCONUT_END_DECLS }

	#if !defined(COCONUT_ALIGNAS)
		#if defined(_MSC_VER)
			#define COCONUT_ALIGNAS(x) __declspec( align(x) )
		#elif ((defined(__GNUC__) || defined(__clang__) || defined(__llvm__)))
			#if defined(__clang__) || defined(__llvm__)
				#if __has_feature(cxx_alignas)
					#define COCONUT_ALIGNAS(x) alignas(x)
				#endif
			#endif
			#ifndef COCONUT_ALIGNAS
				#define COCONUT_ALIGNAS(x) __attribute__((aligned(x)))
			#endif
		#else
			#define COCONUT_ALIGNAS
		#endif
	#endif

	#if !defined(COCONUT_ALIGNOF)
		#if defined(_MSC_VER)
			#define COCONUT_ALIGNOF(t) __alignof(t)
		#elif ((defined(__GNUC__) || defined(__clang__) || defined(__llvm__)))
			#define COCONUT_ALIGNOF(t) __alignof__(t)
		#else
			#define COCONUT_ALIGNOF(t) sizeof(t)
		#endif
	#endif

	#if !defined(COCONUT_EXPORT)
		#if defined(_MSC_VER)
			#if defined(BUILD_DLL)
				#define COCONUT_EXPORT __declspec(dllexport)
			#else
				#define COCONUT_EXPORT __declspec(dllimport)
			#endif
		#elif ((defined(__GNUC__) || defined(__clang__) || defined(__llvm__)))
			#define COCONUT_EXPORT __attribute__ ((visibility("default")))
		#else
			#define COCONUT_EXPORT
		#endif
	#endif

	#if !defined(COCONUT_ALWAYS_INLINE)
		#if defined(_MSC_VER)
			#define COCONUT_ALWAYS_INLINE __forceinline
		#elif ((defined(__GNUC__) || defined(__clang__) || defined(__llvm__)))
			#define COCONUT_ALWAYS_INLINE __inline__ __attribute__((always_inline))
		#else
			#define COCONUT_ALWAYS_INLINE inline
		#endif
	#endif

	#if !defined(COCONUT_NEVER_INLINE)
		#if defined(_MSC_VER)
			#define COCONUT_NEVER_INLINE __declspec(noinline)
		#elif ((defined(__GNUC__) || defined(__clang__) || defined(__llvm__)))
			#define COCONUT_NEVER_INLINE __attribute__((noinline))
		#else
			#define COCONUT_NEVER_INLINE
		#endif
	#endif

	#define COCONUT_FINAL final
	#define COCONUT_OVERRIDE override
	#define COCONUT_FINAL_OVERRIDE COCONUT_OVERRIDE COCONUT_FINAL

	#define COCONUT_KTOR static
	#define COCONUT_KTOD static

	#define COCONUT_FORWARD_KDCL(KLASS) \
		class KLASS;

	#define COCONUT_RUNTIME_KDCL(NS_KLASS, TR_KLASS) \
		public: \
			virtual const std::string class_name() const { return (#NS_KLASS); } \
			virtual const std::string class_tree() const { return (#TR_KLASS); }

	#define COCONUT_KDCL(NS_KLASS, TR_KLASS) \
		public: \
			virtual const std::string class_name() const COCONUT_OVERRIDE { return (#NS_KLASS); } \
			virtual const std::string class_tree() const COCONUT_OVERRIDE { return (#TR_KLASS); }

	#define COCONUT_DESCRIPTION_FMT(KNAME, KTREE, SIZE, SIG, ADDR) \
		u8"{\"name\" : \"" + (KNAME) + "\", \"tree\" : \"" + (KTREE) + "\", \"size\" : " + (SIZE) + ", \"sig\" : " + (SIG) + ", \"addr\" : \"" + (ADDR) + "\"}"

	#define COCONUT_WEAK_ENUM_TYPED(NAME, TYPE) typedef TYPE NAME; enum
	#define COCONUT_WEAK_ENUM(NAME) COCONUT_WEAK_ENUM_TYPED(NAME, std::size_t)

	#define COCONUT_STRONG_ENUM_TYPED(NAME, TYPE) enum class NAME : TYPE
	#define COCONUT_STRONG_ENUM(NAME) COCONUT_STRONG_ENUM_TYPE(NAME, std::size_t)

	#define COCONUT_OPT COCONUT_WEAK_ENUM
	#define COCONUT_OPT_TYPED COCONUT_WEAK_ENUM_TYPED

#endif /* !COCONUT_RUNTIME_DEFINE_HPP */

/* EOF */