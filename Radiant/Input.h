#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS

#include "DirectInput.h"
#include "DirectInputDevice.h"
#include "DirectMouseDevice.h"
#include "DirectKeyboardDevice.h"
#include "DirectGameDevice.h"

namespace Radiant
{
	typedef DirectInput					Input;
	typedef DirectInputDevice			InputDevice;
	typedef DirectMouseDevice			MouseDevice;
	typedef DirectKeyboardDevice		KeyboardDevice;
	typedef DirectGameDevice			GameDevice;
}

#endif

namespace Radiant
{
	extern RADIANT_API Input *GInput;
}
