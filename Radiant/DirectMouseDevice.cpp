/*
	Filename:		DirectMouseDevie.cpp
	Description:	Direct input mouse device class realization
	Author:			Valentin Karyagin
*/

#include "DirectMouseDevice.h"

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

namespace Radiant
{
	DirectMouseDevice::DirectMouseDevice(IDirectInputDevice8A *Device)
		: Super(Device)
		, DIMouseState(new DIMOUSESTATE2())
		, X(0)
		, Y(0)
		, Z(0)
		, ButtonsStates{}		
	{}

	DirectMouseDevice::~DirectMouseDevice()
	{
		delete DIMouseState;
	}

	void DirectMouseDevice::Tick(float DeltaTime)
	{
		if (!Device) return;

		DIMOUSESTATE2 *CastedMouseState = reinterpret_cast<DIMOUSESTATE2 *>(DIMouseState);

		HRESULT StateResult = Device->GetDeviceState(sizeof(DIMOUSESTATE2), DIMouseState);
		if (FAILED(StateResult))
		{
			if (StateResult == DIERR_INPUTLOST || StateResult == DIERR_NOTACQUIRED)
			{
				//printf("Mouse DIERR_INPUTLOST || DIERR_NOTACQUIRED\n");
				if (FAILED(Device->Acquire()))
				{
					//printf("Failed to acquire Mouse\n");
					return;
				}
			}
		}

		X = CastedMouseState->lX;
		Y = CastedMouseState->lX;
		Z = CastedMouseState->lX;

		for (size_t i = 0; i < 8; ++i)
		{
			if (CastedMouseState->rgbButtons[i] & 0x80)
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
