//
// _inifini.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#ifndef COCONUT_RUNTIME_INIFINI_HPP
#define COCONUT_RUNTIME_INIFINI_HPP

#if defined(_MSC_VER)

	#define COCONUT_SECTION_INI_SYM(INI) \
		static void INI(void); \
		static int INI ## _section(void) { INI(); return 0; } \
		__pragma(section(".CRT$XCU", read)) \
		__declspec(allocate(".CRT$XCU")) static int (* _weak ## INI)(void) = INI ## _section; \
		static void INI(void)

	#define COCONUT_SECTION_FINI_SYM(FINI) \
		static void FINI(void); \
		static int FINI ## _section(void) { atexit(FINI); return 0; } \
		__pragma(section(".CRT$XCU", read)) \
		__declspec(allocate(".CRT$XCU")) static int (* _weak ## FINI)(void) = FINI ## _section; \
		static void FINI(void)

#elif defined(__GNUC__) || defined(__clang__)

	#define COCONUT_SECTION_INI_SYM(INI) \
		static void INI(void); \
		static int __attribute__((constructor)) INI ## _section (void); \
		static int INI ## _section(void) { INI(); return 0; } \
		static int __attribute__((used)) (* _weak ## INI)(void) = INI ## _section; \
		static void INI(void)

	#define COCONUT_SECTION_FINI_SYM(FINI) \
		static void FINI(void); \
		static int __attribute__((destructor)) FINI ## _section (void); \
		static int FINI ## _section(void) { FINI(); return 0; } \
		static int __attribute__((used)) (* _weak ## FINI)(void) = FINI ## _section; \
		static void FINI(void)

#elif defined(__SUNPRO_C)

	#define COCONUT_SECTION_INI_SYM(INI) \
		static void INI(void); \
		static INI ## _section (void); \
		static int INI ## _section(void) { INI(); return 0; } \
		static int (* _weak ## INI)(void) = INI ## _section; \
		init(INI ## _section); \
		static void INI(void)

	#define COCONUT_SECTION_FINI_SYM(FINI) \
		static void FINI(void); \
		static int FINI ## _section (void); \
		static int FINI ## _section(void) { FINI(); return 0; } \
		static int (* _weak ## FINI)(void) = FINI ## _section; \
		fini(FINI ## _section); \
		static void FINI(void)

#else

	#ifdef __cplusplus
		#define COCONUT_SECTION_INI_SYM(INI) \
			static void INI(void); \
			struct INI ## _section \
			{ \
				INI ## _section() { INI(); } \
				~INI ## _section() {} \
			}; \
			static INI ## _section INI ## _section; \
			static void INI(void)

		#define COCONUT_SECTION_FINI_SYM(FINI) \
			static void FINI(void); \
			struct FINI ## _section \
			{ \
				FINI ## _section() {} \
				~FINI ## _section() { FINI(); } \
			}; \
			static FINI ## _section FINI ## _section; \
			static void FINI(void)
	#else
		#define COCONUT_SECTION_INI_SYM(INI) \
			static void INI(void); \
			struct INI ## _section {}; \
			static INI ## _section INI ## _section; \
			static void INI(void)

		#define COCONUT_SECTION_FINI_SYM(FINI) \
			static void FINI(void); \
			struct FINI ## _section {}; \
			static FINI ## _section FINI ## _section; \
			static void FINI(void)	
	#endif

#endif

#define COCONUT_SECTION_INI \
	COCONUT_SECTION_INI_SYM(__coconut_crt_ini)

#define COCONUT_SECTION_FINI \
	COCONUT_SECTION_FINI_SYM(__coconut_crt_fini)

#endif /* !COCONUT_RUNTIME_INIFINI_HPP */

/* EOF */