/*
	Filename:		Assert.h
	Description:	Errors detection functional
	Author:			Valentin Karyagin
*/

#pragma once

#include "Platform.h"

#include <cstring>

__forceinline const tchar * CutFilename(const tchar *Filename)
{
#ifdef CHARSET_UNICODE
	size_t StrLength = wcslen(Filename);
#else
	size_t StrLength = strlen(Filename);
#endif
	for (; StrLength > 0; --StrLength)
	{
		if (Filename[StrLength] == TXT('\\')) break;
	}
	return Filename + StrLength + 1;
}
#ifdef CHARSET_UNICODE
// Some fucking macromagic
#define WIDE(macro) TXT(macro)
#define __WFILE__ WIDE(__FILE__)
#define ASSERT(Condition) if (!(Condition)) wprintf(TXT("ASSERT: %ws %ld\n"), CutFilename(__WFILE__), __LINE__)
#else
#define ASSERT(Condition) if (!(Condition)) printf(TXT("ASSERT: %s %ld\n"), CutFilename(__FILE__), __LINE__)
#endif
