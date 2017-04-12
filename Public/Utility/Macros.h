#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC
#define ETL_ALIGN(x) __declspec(align(x))
#elif ETL_STD // ETL_MSVC
#define ETL_ALIGN(x) __attribute__((aligned(x)))
#if ETL_MAC
#ifdef __OJBC__
#define ETL_OBJC_CLASS(name) @class name
#else // __OBJC__
#define ETL_OBJC_CLASS(name) typedef struct objc_object name
#endif // __OBJC__
#endif // ETL_MAC
#endif // ETL_MSVC

#if ETL_WIN
#define ETL_SYSTEM_PAUSE system("Pause")
#elif ETL_POSIX // ETL_WIN
#define ETL_SYSTEM_PAUSE system("read -n 1 -s -p \"Press any key to continue...\"; echo")
#endif // ETL_WIN

#define ETL_DISABLECOPYING(x) x(const x&) = delete;\
x& operator =(const x&) = delete;

#define ETL_DISABLECOPYING_AND_MOVE(x) x(const x&) = delete;\
x(const x&&) = delete;\
x& operator =(const x&) = delete;\
x& operator =(const x&&) = delete

#define ETL_ITERATOR_FOR_LOOP(iter, container) for(auto iter = container.begin(); iter != container.end(); ++iter)
#define ETL_ITERATOR_WHILE_LOOP(iter, container) for(auto iter = container.begin(); iter != container.end();)

#define ETL_DECLARE_SINGLETON(className) public:\
inline static className& Instance()\
{\
	return sm_Instance;\
}\
inline static className* InstancePtr()\
{\
	return &sm_Instance;\
}\
private:\
static className sm_Instance;\
className();\
virtual ~className();\
className(const className&) = delete;\
className(className&&) = delete;\
className& operator=(const className&) = delete;\
className& operator=(className&&) = delete

#define ETL_IMPLEMENT_SINGLETON(className) className className::sm_Instance