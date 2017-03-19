#pragma once

#if _MSC_VER
#pragma warning(disable: 4005)
#endif

// Compiler and Architecture
#define ETL_LLVM 0
#define ETL_MSVC 0
#define ETL_GCC 0

#define ETL_32BIT 0
#define ETL_64BIT 0
#define ETL_X86 0
#define ETL_X64 0

#if defined(__llvm__)

#define ETL_LLVM 1
#if defined(__i386__)
#define ETL_32BIT 1
#define ETL_X86 1
#elif defined(__x86_64__)
#define ETL_64BIT 1
#define ETL_X64 1
#endif

#elif defined(_MSC_VER)

#define ETL_MSVC 1
#if defined(_M_IX86)
#define ETL_32BIT 1
#define ETL_X86 1
#elif defined(_M_X64)
#define ETL_64BIT 1
#define ETL_X64 1
#endif

#elif defined(__GNUC__)

#define ETL_GCC 1
#if defined(__i386__)
#define ETL_32BIT 1
#define ETL_X86 1
#elif defined(__x86_64__)
#define ETL_64BIT 1
#define ETL_X64 1
#endif

#endif

// Operating System and Debug
#define ETL_WIN 0
#define ETL_LINUX 0
#define ETL_MAC 0

#define ETL_DEBUG 0

#if defined(_WIN32) || defined(WIN32)

#define ETL_WIN 1
#if ETL_MSVC
#define _CRT_SECURE_NO_WARNINGS
#endif
#if defined(_DEBUG) || (DEBUG)
#define ETL_DEBUG 1
#endif

#elif defined(__linux)

#define ETL_LINUX 1
#ifdef DEBUG
#define ETL_DEBUG 1
#endif

#elif defined(__APPLE__)

#define ETL_MAC 1
#if DEBUG
#define ETL_DEBUG 1
#endif

#endif

// Compatibility
#define ETL_NOEXCEPT noexcept

#if ETL_MSVC && _MSC_VER < 1910
#define ETL_NOEXCEPT throw()
#endif

// Unicode
#define ETL_UNICODE 0

#if defined(_UNICODE) || defined(UNICODE)
#define ETL_UNICODE 1
#endif

#if _MSC_VER
#pragma warning(default: 4005)
#endif