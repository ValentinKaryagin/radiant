/*
	Filename:		DirectKeyboardDevie.cpp
	Description:	Direct input keyboard device class realization
	Author:			Valentin Karyagin
*/

#include "DirectKeyboardDevice.h"

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

namespace Radiant
{
	const Key DirectKeys::Q = Key(DIK_Q, TXT("Q"));
	const Key DirectKeys::W = Key(DIK_W, TXT("W"));
	const Key DirectKeys::E = Key(DIK_E, TXT("E"));
	const Key DirectKeys::R = Key(DIK_R, TXT("R"));
	const Key DirectKeys::T = Key(DIK_T, TXT("T"));
	const Key DirectKeys::Y = Key(DIK_Y, TXT("Y"));
	const Key DirectKeys::U = Key(DIK_U, TXT("U"));
	const Key DirectKeys::I = Key(DIK_I, TXT("I"));
	const Key DirectKeys::O = Key(DIK_O, TXT("O"));
	const Key DirectKeys::P = Key(DIK_P, TXT("P"));
	const Key DirectKeys::A = Key(DIK_A, TXT("A"));
	const Key DirectKeys::S = Key(DIK_S, TXT("S"));
	const Key DirectKeys::D = Key(DIK_D, TXT("D"));
	const Key DirectKeys::F = Key(DIK_F, TXT("F"));
	const Key DirectKeys::G = Key(DIK_G, TXT("G"));
	const Key DirectKeys::H = Key(DIK_H, TXT("H"));
	const Key DirectKeys::J = Key(DIK_J, TXT("J"));
	const Key DirectKeys::K = Key(DIK_K, TXT("K"));
	const Key DirectKeys::L = Key(DIK_L, TXT("L"));
	const Key DirectKeys::Z = Key(DIK_Z, TXT("Z"));
	const Key DirectKeys::X = Key(DIK_X, TXT("X"));
	const Key DirectKeys::C = Key(DIK_C, TXT("C"));
	const Key DirectKeys::V = Key(DIK_V, TXT("V"));
	const Key DirectKeys::B = Key(DIK_B, TXT("B"));
	const Key DirectKeys::N = Key(DIK_N, TXT("N"));
	const Key DirectKeys::M = Key(DIK_M, TXT("M"));
}

namespace Radiant
{
	DirectKeyboardDevice::DirectKeyboardDevice(IDirectInputDevice8A *Device)
		: Super(Device)
		, DIKeysStates{}
		, KeysStates{}
	{}

	DirectKeyboardDevice::~DirectKeyboardDevice() {}

	void DirectKeyboardDevice::Tick(float DeltaTime)
	{
		if (!Device) return;

		HRESULT StateResult = Device->GetDeviceState(sizeof(DIKeysStates), &DIKeysStates);
		if (FAILED(StateResult))
		{
			if (StateResult == DIERR_INPUTLOST || StateResult == DIERR_NOTACQUIRED)
			{
				//printf("Keyboard DIERR_INPUTLOST || DIERR_NOTACQUIRED\n");
				if (FAILED(Device->Acquire()))
				{
					//printf("Failed to acquire Keyboard\n");
					return;
				}
			}
		}

		for (size_t i = 0; i < 256; ++i)
		{
			if (DIKeysStates[i] & 0x80)
			{
				if (KeysStates[i] == IS_None)
				{
					KeysStates[i] = IS_Pressed;
					//printf("IS_Pressed\n");
				}
				else if (KeysStates[i] == IS_Pressed)
				{
					KeysStates[i] = IS_Repeated;
					//printf("IS_Repeated\n");
				}
				else if (KeysStates[i] == IS_Repeated)
				{
					KeysStates[i] = IS_Repeated;
					//printf("IS_Repeated\n");
				}
			}
			else
			{
				if (KeysStates[i] == IS_Pressed || KeysStates[i] == IS_Repeated)
				{
					KeysStates[i] = IS_Released;
					//printf("IS_Released\n");
				}
				else if (KeysStates[i] == IS_Released)
				{
					KeysStates[i] = IS_None;
				}
			}
		}
	}
}
