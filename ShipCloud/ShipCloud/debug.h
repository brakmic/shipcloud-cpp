#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <windows.h>
#include <tchar.h>
//a simple Tracer
#ifdef ENABLE_TRACE
bool _trace(TCHAR *format, ...)
{
	TCHAR buffer[2048];

	va_list argptr;
	va_start(argptr, format);
	wvsprintf(buffer, format, argptr);
	va_end(argptr);

	OutputDebugString(buffer);

	return true;
}
#else 
bool _trace(TCHAR *format, ...)
{
	// do nothing
	return true;
}
#endif

#endif // __DEBUG_H__