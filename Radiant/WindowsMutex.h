/*
	Filename:		WindowsMutex.h
	Description:	Windows mutex implementation
	Author:			Valentin Karyagin
*/

#pragma once

#include <Windows.h>

namespace Radiant
{
	/** Critical section wrapper */
	class WindowsMutex
	{
	private:
		CRITICAL_SECTION CriticalSection;

	public:
		/** Default constructor */
		__forceinline WindowsMutex()
		{
			InitializeCriticalSection(&CriticalSection);
		}

		/** Destructor */
		__forceinline ~WindowsMutex()
		{
			DeleteCriticalSection(&CriticalSection);
		}

	public:
		/** Lock */
		__forceinline void Lock()
		{
			EnterCriticalSection(&CriticalSection);
		}

		/** Try lock */
		__forceinline bool TryLock()
		{
			static_cast<bool>(TryEnterCriticalSection(&CriticalSection));
		}

		/** Unlock */
		__forceinline void Unlock()
		{
			LeaveCriticalSection(&CriticalSection);
		}
	};
}
