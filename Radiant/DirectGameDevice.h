/*
	Filename:		DirectGameDevie.h
	Description:	Game device class that implemented by DirectInput (part of DirectX) library
	Author:			Valentin Karyagin
*/

#pragma once

#include "DirectInputDevice.h"

namespace Radiant
{
	class RADIANT_API DirectGameDevice : public DirectInputDevice
	{
		DECLARE_CLASS(DirectGameDevice, DirectInputDevice)

	protected:
		void *DIJoyState;

	protected:
		int32_t		X, Y, Z;
		EInputState	ButtonsStates[128];

	public:
		DirectGameDevice(IDirectInputDevice8A *Device = nullptr);
		virtual ~DirectGameDevice();

	public:
		void Tick(float DeltaTime = 0.0f) override;
	};
}
