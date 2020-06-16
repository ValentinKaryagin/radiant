/*
	Filename:		WindowsAPI.h
	Description:	WinAPI includer
	Author:			Valentin Karyagin
*/

#pragma once

#include <Windows.h>

class WindowsAPI
{
public:
	__forceinline static HMODULE LoadDll(const tchar *DllName)
	{
		return LoadLibrary(DllName);
	}

	__forceinline static FARPROC GetProcAddrFromDll(HMODULE Handle, const tchar *ProcName)
	{
#ifdef CHARSET_UNICODE
		char ProcNameAnsi[MAX_PATH]{};
		size_t Converted = 0;
		wcstombs_s(&Converted, ProcNameAnsi, ProcName, MAX_PATH);
		return GetProcAddress(Handle, ProcNameAnsi);
#else
		return GetProcAddress(Handle, ProcName);
#endif		
	}

	__forceinline static bool FreeDll(HMODULE Handle)
	{
		return static_cast<bool>(FreeLibrary(Handle));
	}
};
