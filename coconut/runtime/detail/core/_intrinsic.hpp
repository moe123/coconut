//
// _intrinsic.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#ifndef COCONUT_RUNTIME_INTRINSIC_HPP
#define COCONUT_RUNTIME_INTRINSIC_HPP

	#if defined(_MSC_VER)
		#include <intrin.h>
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

#endif /* !COCONUT_RUNTIME_INTRINSIC_HPP */

/* EOF */

/* EOF */