/*
	Filename:		Platform.h
	Description:	Platform detector
	Author:			Valentin Karyagin
*/

#pragma once

#ifdef	_WIN64
#define	PLATFORM_WINDOWS
#ifdef	_WINDLL
#define	RADIANT_API __declspec(dllexport)
#else
#define	RADIANT_API __declspec(dllimport)
#endif
#endif

#ifdef	_DEBUG
#define	CONFIGURATION_DEBUG
#endif

#ifdef	_UNICODE
#define	CHARSET_UNICODE
typedef	wchar_t		tchar;
#define	TXT(str)	L ## str
#define	tfopen_s	_wfopen_s
#define tstring		wstring
#define to_tstring	to_wstring
#define tsprintf_s	swprintf_s
#define tifstream	wifstream
#define tprintf		wprintf
#else
typedef	char		tchar;
#define	TXT(str)	str
#define	fopen_s		fopen_s
#define tstring		string
#define to_tstring	to_string
#define tsprintf_s	sprintf_s
#define tifstream	ifstream
#define printf		wprintf
#endif

#ifdef	PLATFORM_WINDOWS
#include "WindowsPlatform.h"
#endif

#include "Std.h"
#include "Assert.h"
