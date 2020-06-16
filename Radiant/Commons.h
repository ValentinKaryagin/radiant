#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS

#include "SDL2FontTTF.h"
#include "SDL2Surface.h"

namespace Radiant
{
	typedef SDL2FontTTF	FontTTF;
	typedef SDL2Surface	Surface;
}

#endif
