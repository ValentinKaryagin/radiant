/*
	Filename:		WindowsPlatform.h
	Description:	Windows platform includer
	Author:			Valentin Karyagin
*/

#pragma once

#include "WindowsAPI.h"
#include "WindowsMutex.h"
#include "WindowsFile.h"
#include "WindowsThread.h"

namespace Radiant
{
	typedef WindowsMutex	Mutex;
	typedef WindowsFile		File;
	typedef WindowsThread	Thread;
}
