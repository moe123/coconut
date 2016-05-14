//
// nutrt-_intrinsic.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#ifndef COCONUT_RUNTIME_INTRINSIC_HPP
#define COCONUT_RUNTIME_INTRINSIC_HPP

	#if defined(_MSC_VER)
		#include <intrin.h>
	#elif defined(__ICL)
		#include <immintrin.h>
	#elif (defined(__GNUC__) || defined(__clang__)) && (defined(__x86_64__) || defined(__i386__))
		#include <x86intrin.h>
	#elif (defined(__GNUC__) || defined(__clang__)) && defined(__ARM_NEON__)
		#include <arm_neon.h>
	#elif (defined(__GNUC__) || defined(__clang__)) && defined(__IWMMXT__)
		#include <mmintrin.h>
	#elif ((defined(__GNUC__) || defined(__clang__)) || defined(__xlC__)) && (defined(__VEC__) || defined(__ALTIVEC__))
		#include <altivec.h>
	#elif (defined(__GNUC__) || defined(__clang__)) && defined(__SPE__)
		#include <spe.h>
	#endif

	#if defined(__clang__)
		#ifdef __MMX__
			#include <mmintrin.h>
		#endif

		#ifdef __SSE__
			#include <xmmintrin.h>
		#endif

		#ifdef __SSE2__
			#include <emmintrin.h>
		#endif

		#ifdef __SSE3__
			#include <pmmintrin.h>
		#endif

		#ifdef __SSSE3__
			#include <tmmintrin.h>
		#endif

		#if defined (__SSE4_2__) || defined (__SSE4_1__)
			#include <smmintrin.h>
		#endif

		#if defined (__AES__) || defined (__PCLMUL__)
			#include <wmmintrin.h>
		#endif

		#ifdef __AVX__
			#include <avxintrin.h>
		#endif
	#endif

#endif /* !COCONUT_RUNTIME_INTRINSIC_HPP */

/* EOF */

/* EOF */