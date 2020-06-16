/*
	Filename:		DirectGameDevie.cpp
	Description:	Direct input game device class realization
	Author:			Valentin Karyagin
*/

#include "DirectGameDevice.h"

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

namespace Radiant
{
	DirectGameDevice::DirectGameDevice(IDirectInputDevice8A *Device)
		: Super(Device)
		, DIJoyState(new DIJOYSTATE2())
		, X(0)
		, Y(0)
		, Z(0)
	{}

	DirectGameDevice::~DirectGameDevice()
	{
		delete DIJoyState;
	}

	void DirectGameDevice::Tick(float DeltaTime)
	{
		if (!Device) return;

		if (!Device) return;

		DIJOYSTATE2 *CastedJoyState = reinterpret_cast<DIJOYSTATE2 *>(DIJoyState);

		HRESULT StateResult = Device->GetDeviceState(sizeof(DIJOYSTATE2), DIJoyState);
		if (FAILED(StateResult))
		{
			if (StateResult == DIERR_INPUTLOST || StateResult == DIERR_NOTACQUIRED)
			{
				//printf("Game device DIERR_INPUTLOST || DIERR_NOTACQUIRED\n");
				if (FAILED(Device->Acquire()))
				{
					//printf("Failed to acquire Game device\n");
					return;
				}
			}
		}

		X = CastedJoyState->lX;
		Y = CastedJoyState->lX;
		Z = CastedJoyState->lX;

		for (size_t i = 0; i < 128; ++i)
		{
			if (CastedJoyState->rgbButtons[i] & 0x80)
			{
				if (ButtonsStates[i] == IS_None)
				{
					ButtonsStates[i] = IS_Pressed;
					//printf("IS_Pressed\n");
				}
				else if (ButtonsStates[i] == IS_Pressed)
				{
					ButtonsStates[i] = IS_Repeated;
					//printf("IS_Repeated\n");
				}
				else if (ButtonsStates[i] == IS_Repeated)
				{
					ButtonsStates[i] = IS_Repeated;
					//printf("IS_Repeated\n");
				}
			}
			else
			{
				if (ButtonsStates[i] == IS_Pressed || ButtonsStates[i] == IS_Repeated)
				{
					ButtonsStates[i] = IS_Released;
					//printf("IS_Released\n");
				}
				else if (ButtonsStates[i] == IS_Released)
				{
					ButtonsStates[i] = IS_None;
				}
			}
		}
	}
}
