#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS

#include "SteamVRSystem.h"

namespace Radiant
{
	typedef SteamVRSystem	VRSystem;
}

#endif

namespace Radiant
{
	extern RADIANT_API VRSystem *GVRSystem;
}
