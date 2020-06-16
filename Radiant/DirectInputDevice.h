/*
	Filename:		DirectInputDevie.h
	Description:	Base input device class that implemented by DirectInput (part of DirectX) library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"
#include "Key.h"

struct IDirectInputDevice8A;

namespace Radiant
{
	class RADIANT_API DirectInputDevice
	{
		DECLARE_BASECLASS(DirectInputDevice)

	protected:
		IDirectInputDevice8A *Device;

	public:
		DirectInputDevice(IDirectInputDevice8A *Device = nullptr);
		virtual ~DirectInputDevice();

	public:
		virtual void Tick(float DeltaTime = 0.0f);
	};
}
