#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS

#include "GLFWApplication.h"

namespace Radiant
{
	typedef GLFWApplication	Application;
}

#endif

namespace Radiant
{
	extern RADIANT_API Application *GApplication;
}
