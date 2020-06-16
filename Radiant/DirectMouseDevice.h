/*
	Filename:		DirectMouseDevie.h
	Description:	Mouse device class that implemented by DirectInput (part of DirectX) library
	Author:			Valentin Karyagin
*/

#pragma once

#include "DirectInputDevice.h"

namespace Radiant
{
	class RADIANT_API DirectMouseDevice : public DirectInputDevice
	{
		DECLARE_CLASS(DirectMouseDevice, DirectInputDevice)

	protected:
		void *DIMouseState;

	protected:
		int32_t		X, Y, Z;
		EInputState	ButtonsStates[8];

	public:
		DirectMouseDevice(IDirectInputDevice8A *Device = nullptr);
		virtual ~DirectMouseDevice();

	public:
		void Tick(float DeltaTime = 0.0f) override;
	};
}
