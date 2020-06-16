/*
	Filename:		DirectInputDevie.cpp
	Description:	Direct input base input device class realization
	Author:			Valentin Karyagin
*/

#include "DirectInputDevice.h"

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

namespace Radiant
{
	DirectInputDevice::DirectInputDevice(IDirectInputDevice8A *Device)
		: Device(Device)
	{}

	DirectInputDevice::~DirectInputDevice()
	{
		if (Device) Device->Release();
	}

	void DirectInputDevice::Tick(float DeltaTime)
	{
		
	}
}
