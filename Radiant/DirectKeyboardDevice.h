/*
	Filename:		DirectKeyboardDevie.h
	Description:	Keyboard device class that implemented by DirectInput (part of DirectX) library
	Author:			Valentin Karyagin
*/

#pragma once

#include "DirectInputDevice.h"

namespace Radiant
{
	struct DirectKeys
	{
		static RADIANT_API const Key Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M;
	};	
}

namespace Radiant
{
	class RADIANT_API DirectKeyboardDevice : public DirectInputDevice
	{
		DECLARE_CLASS(DirectKeyboardDevice, DirectInputDevice)

	protected:
		byte DIKeysStates[256];

	protected:
		EInputState KeysStates[256];

	public:
		DirectKeyboardDevice(IDirectInputDevice8A *Device = nullptr);
		virtual ~DirectKeyboardDevice();

	public:
		void Tick(float DeltaTime = 0.0f) override;
		//bool IsInputEvent(const uint32_t Key, EInputEvent Event);
		//bool IsInputEvent();
	};
}
