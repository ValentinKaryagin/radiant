/*
	Filename:		DirectInput.cpp
	Description:	Input class that implemented by DirectInput (part of DirectX) library
	Author:			Valentin Karyagin
*/

#include "DirectInput.h"

// Third party
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

// This class components
#include "DirectInputDevice.h"
#include "DirectMouseDevice.h"
#include "DirectKeyboardDevice.h"
#include "DirectGameDevice.h"

// Other engine components
#include "Application.h"
#include "Input.h"

namespace Radiant
{
	DirectInput::DirectInput()
		: Driver(nullptr)
	{}

	DirectInput::~DirectInput() {}

	int32_t DirectInput::Init()
	{
		ASSERT(DirectInput8Create(GetModuleHandleA(0), DIRECTINPUT_VERSION, IID_IDirectInput8A, reinterpret_cast<void **>(&Driver), nullptr) == DI_OK);

		if (FAILED(Driver->EnumDevices(DI8DEVCLASS_POINTER, &DirectInput::EnumAndCreateDevices, Driver, DIEDFL_ATTACHEDONLY)))
		{
			printf("Failed to enumerate Mouse devices\n");
		}

		if (FAILED(Driver->EnumDevices(DI8DEVCLASS_KEYBOARD, &DirectInput::EnumAndCreateDevices, Driver, DIEDFL_ATTACHEDONLY)))
		{
			printf("Failed to enumerate Keyboard devices\n");
		}

		if (FAILED(Driver->EnumDevices(DI8DEVCLASS_GAMECTRL, &DirectInput::EnumAndCreateDevices, Driver, DIEDFL_ATTACHEDONLY)))
		{
			printf("Failed to enumerate Game devices\n");
		}

		return 0;
	}

	void DirectInput::Terminate()
	{
		for (auto &Item : Devices)
		{
			delete Item;
		}

		Devices.clear();

		Driver->Release();
		Driver = nullptr;		
	}

	void DirectInput::Tick(float DeltaTime)
	{
		for (auto &Item : Devices)
		{
			Item->Tick(DeltaTime);
		}
	}

	BOOL DirectInput::EnumAndCreateDevices(const DIDEVICEINSTANCEA *Device, void *UserPtr)
	{
		IDirectInput8A		*Driver			= reinterpret_cast<IDirectInput8A *>(UserPtr);
		BYTE				DeviceType		= GET_DIDEVICE_TYPE(Device->dwDevType);
		BYTE				DeviceSubType	= GET_DIDEVICE_SUBTYPE(Device->dwDevType);

		DirectInputDevice	*NewDevice		= nullptr;

		if (DeviceType == DI8DEVTYPE_MOUSE)
		{
			if (DeviceSubType == DI8DEVTYPEMOUSE_UNKNOWN)
			{
				printf("Mouse device: %s %s\n", Device->tszInstanceName, "UNKNOWN");
			}
			else if (DeviceSubType == DI8DEVTYPEMOUSE_TRADITIONAL)
			{
				printf("Mouse device: %s %s\n", Device->tszInstanceName, "ABSOLUTE");
			}
			else if (DeviceSubType == DI8DEVTYPEMOUSE_FINGERSTICK)
			{
				printf("Mouse device: %s %s\n", Device->tszInstanceName, "FINGERSTICK");
			}
			else if (DeviceSubType == DI8DEVTYPEMOUSE_TOUCHPAD)
			{
				printf("Mouse device: %s %s\n", Device->tszInstanceName, "TOUCHPAD");
			}
			else if (DeviceSubType == DI8DEVTYPEMOUSE_TRACKBALL)
			{
				printf("Mouse device: %s %s\n", Device->tszInstanceName, "TRACKBALL");
			}
			else if (DeviceSubType == DI8DEVTYPEMOUSE_ABSOLUTE)
			{
				printf("Mouse device: %s %s\n", Device->tszInstanceName, "TRADITIONAL");
			}			
			else
			{
				printf("Mouse device: %s %s\n", Device->tszInstanceName, "ERROR");
			}

			IDirectInputDevice8A *InputDevice = nullptr;
			if (FAILED(Driver->CreateDevice(Device->guidInstance, &InputDevice, nullptr)))
			{
				printf("Failed to create Mouse device\n");
				return DIENUM_CONTINUE;
			}

			if (FAILED(InputDevice->SetDataFormat(&c_dfDIMouse2)))
			{
				printf("Failed to set Mouse device format data\n");
				InputDevice->Release();
				return DIENUM_CONTINUE;
			}
			
			if (FAILED(InputDevice->SetCooperativeLevel(GApplication->GetWin32Handler(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
			{
				printf("Failed to set Mouse device cooperative level\n");
				InputDevice->Release();
				return DIENUM_CONTINUE;
			}			

			if (FAILED(InputDevice->Acquire()))
			{
				//printf("Failed to acquire Mouse device\n");
				return DIENUM_CONTINUE;
			}

			NewDevice = new DirectMouseDevice(InputDevice);
		}
		else if (DeviceType == DI8DEVTYPE_KEYBOARD)
		{
			if (DeviceSubType == DI8DEVTYPEKEYBOARD_UNKNOWN)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "UNKNOWN");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_PCXT)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "PCXT");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_OLIVETTI)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "OLIVETTI");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_PCAT)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "PCAT");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_PCENH)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "PCENH");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_NOKIA1050)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "NOKIA1050");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_NOKIA9140)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "NOKIA9140");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_NEC98)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "NEC98");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_NEC98LAPTOP)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "NEC98LAPTOP");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_NEC98106)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "NEC98106");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_JAPAN106)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "JAPAN106");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_JAPANAX)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "JAPANAX");
			}
			else if (DeviceSubType == DI8DEVTYPEKEYBOARD_J3100)
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "J3100");
			}
			else
			{
				printf("Keyboard device: %s %s\n", Device->tszInstanceName, "ERROR");
			}

			IDirectInputDevice8A *InputDevice = nullptr;
			if (FAILED(Driver->CreateDevice(Device->guidInstance, &InputDevice, nullptr)))
			{
				printf("Failed to create Keyboard device\n");
				return DIENUM_CONTINUE;
			}

			if (FAILED(InputDevice->SetDataFormat(&c_dfDIKeyboard)))
			{
				printf("Failed to set Keyboard device format data\n");
				InputDevice->Release();
				return DIENUM_CONTINUE;
			}

			GLFWApplication *PlatformApplication = dynamic_cast<GLFWApplication *>(GApplication);
			if (PlatformApplication)
			{
				if (FAILED(InputDevice->SetCooperativeLevel(PlatformApplication->GetWin32Handler(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
				{
					printf("Failed to set Keyboard device cooperative level\n");
					InputDevice->Release();
					return DIENUM_CONTINUE;
				}
			}			

			if (FAILED(InputDevice->Acquire()))
			{
				//printf("Failed to acquire Keyboard device\n");
				return DIENUM_CONTINUE;
			}

			NewDevice = new DirectKeyboardDevice(InputDevice);
		}
		else if (DeviceType == DI8DEVTYPE_JOYSTICK)
		{		
			if (DeviceSubType == DI8DEVTYPEJOYSTICK_LIMITED)
			{
				printf("Joystick device: %s %s\n", Device->tszInstanceName, "LIMITED");
			}
			else if (DeviceSubType == DI8DEVTYPEJOYSTICK_STANDARD)
			{
				printf("Joystick device: %s %s\n", Device->tszInstanceName, "STANDARD");
			}
			else
			{
				printf("Joystick device: %s %s\n", Device->tszInstanceName, "ERROR");
			}

			IDirectInputDevice8A *InputDevice = nullptr;
			if (FAILED(Driver->CreateDevice(Device->guidInstance, &InputDevice, nullptr)))
			{
				printf("Failed to create Joystick device\n");
				return DIENUM_CONTINUE;
			}

			if (FAILED(InputDevice->SetDataFormat(&c_dfDIJoystick2)))
			{
				printf("Failed to set Joystick device format data\n");
				InputDevice->Release();
				return DIENUM_CONTINUE;
			}

			GLFWApplication *PlatformApplication = dynamic_cast<GLFWApplication *>(GApplication);
			if (PlatformApplication)
			{
				if (FAILED(InputDevice->SetCooperativeLevel(PlatformApplication->GetWin32Handler(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
				{
					printf("Failed to set Joystick device cooperative level\n");
					InputDevice->Release();
					return DIENUM_CONTINUE;
				}
			}

			if (FAILED(InputDevice->Acquire()))
			{
				printf("Failed to acquire Joystick device\n");
				return DIENUM_CONTINUE;
			}

			NewDevice = new DirectGameDevice(InputDevice);
		}
		else if (DeviceType == DI8DEVTYPE_GAMEPAD)
		{
			if (DeviceSubType == DI8DEVTYPEGAMEPAD_LIMITED)
			{
				printf("Gamepad device: %s %s\n", Device->tszInstanceName, "LIMITED");
			}
			else if (DeviceSubType == DI8DEVTYPEGAMEPAD_STANDARD)
			{
				printf("Gamepad device: %s %s\n", Device->tszInstanceName, "STANDARD");
			}
			else if (DeviceSubType == DI8DEVTYPEGAMEPAD_TILT)
			{
				printf("Gamepad device: %s %s\n", Device->tszInstanceName, "TILT");
			}
			else
			{
				printf("Gamepad device: %s %s\n", Device->tszInstanceName, "ERROR");
			}

			IDirectInputDevice8A *InputDevice = nullptr;
			if (FAILED(Driver->CreateDevice(Device->guidInstance, &InputDevice, nullptr)))
			{
				printf("Failed to create Gamepad device\n");
				return DIENUM_CONTINUE;
			}

			if (FAILED(InputDevice->SetDataFormat(&c_dfDIJoystick2)))
			{
				printf("Failed to set Gamepad device format data\n");
				InputDevice->Release();
				return DIENUM_CONTINUE;
			}

			GLFWApplication *PlatformApplication = dynamic_cast<GLFWApplication *>(GApplication);
			if (PlatformApplication)
			{
				if (FAILED(InputDevice->SetCooperativeLevel(PlatformApplication->GetWin32Handler(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
				{
					printf("Failed to set Gamepad device cooperative level\n");
					InputDevice->Release();
					return DIENUM_CONTINUE;
				}
			}

			if (FAILED(InputDevice->Acquire()))
			{
				//printf("Failed to acquire Gamepad device\n");
				return DIENUM_CONTINUE;
			}

			NewDevice = new DirectGameDevice(InputDevice);
		}
		else if (DeviceType == DI8DEVTYPE_DRIVING)
		{
			if (DeviceSubType == DI8DEVTYPEDRIVING_LIMITED)
			{
				printf("Driving device: %s %s\n", Device->tszInstanceName, "LIMITED");
			}
			else if (DeviceSubType == DI8DEVTYPEDRIVING_COMBINEDPEDALS)
			{
				printf("Driving device: %s %s\n", Device->tszInstanceName, "COMBINEDPEDALS");
			}
			else if (DeviceSubType == DI8DEVTYPEDRIVING_DUALPEDALS)
			{
				printf("Driving device: %s %s\n", Device->tszInstanceName, "DUALPEDALS");
			}
			else if (DeviceSubType == DI8DEVTYPEDRIVING_THREEPEDALS)
			{
				printf("Driving device: %s %s\n", Device->tszInstanceName, "THREEPEDALS");
			}
			else if (DeviceSubType == DI8DEVTYPEDRIVING_HANDHELD)
			{
				printf("Driving device: %s %s\n", Device->tszInstanceName, "HANDHELD");
			}
			else
			{
				printf("Driving device: %s %s\n", Device->tszInstanceName, "ERROR");
			}

			IDirectInputDevice8A *InputDevice = nullptr;
			if (FAILED(Driver->CreateDevice(Device->guidInstance, &InputDevice, nullptr)))
			{
				printf("Failed to create Driving device\n");
				return DIENUM_CONTINUE;
			}

			if (FAILED(InputDevice->SetDataFormat(&c_dfDIJoystick2)))
			{
				printf("Failed to set Driving device format data\n");
				InputDevice->Release();
				return DIENUM_CONTINUE;
			}

			GLFWApplication *PlatformApplication = dynamic_cast<GLFWApplication *>(GApplication);
			if (PlatformApplication)
			{
				if (FAILED(InputDevice->SetCooperativeLevel(PlatformApplication->GetWin32Handler(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
				{
					printf("Failed to set Driving device cooperative level\n");
					InputDevice->Release();
					return DIENUM_CONTINUE;
				}
			}

			if (FAILED(InputDevice->Acquire()))
			{
				//printf("Failed to acquire Driving device\n");
				return DIENUM_CONTINUE;
			}

			NewDevice = new DirectGameDevice(InputDevice);
		}
		else if (DeviceType == DI8DEVTYPE_FLIGHT)
		{
			if (DeviceSubType == DI8DEVTYPEFLIGHT_LIMITED)
			{
				printf("Flight device: %s %s\n", Device->tszInstanceName, "LIMITED");
			}
			else if (DeviceSubType == DI8DEVTYPEFLIGHT_STICK)
			{
				printf("Flight device: %s %s\n", Device->tszInstanceName, "STICK");
			}
			else if (DeviceSubType == DI8DEVTYPEFLIGHT_YOKE)
			{
				printf("Flight device: %s %s\n", Device->tszInstanceName, "YOKE");
			}
			else if (DeviceSubType == DI8DEVTYPEFLIGHT_RC)
			{
				printf("Flight device: %s %s\n", Device->tszInstanceName, "RC");
			}
			else
			{
				printf("Flight device: %s %s\n", Device->tszInstanceName, "ERROR");
			}

			IDirectInputDevice8A *InputDevice = nullptr;
			if (FAILED(Driver->CreateDevice(Device->guidInstance, &InputDevice, nullptr)))
			{
				printf("Failed to create Flight device\n");
				return DIENUM_CONTINUE;
			}

			if (FAILED(InputDevice->SetDataFormat(&c_dfDIJoystick2)))
			{
				printf("Failed to set Flight device format data\n");
				InputDevice->Release();
				return DIENUM_CONTINUE;
			}

			GLFWApplication *PlatformApplication = dynamic_cast<GLFWApplication *>(GApplication);
			if (PlatformApplication)
			{
				if (FAILED(InputDevice->SetCooperativeLevel(PlatformApplication->GetWin32Handler(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
				{
					printf("Failed to set Flight device cooperative level\n");
					InputDevice->Release();
					return DIENUM_CONTINUE;
				}
			}

			if (FAILED(InputDevice->Acquire()))
			{
				//printf("Failed to acquire Flight device\n");
				return DIENUM_CONTINUE;
			}

			NewDevice = new DirectGameDevice(InputDevice);
		}
		else
		{
			printf("Other device: %s\n", Device->tszInstanceName);
		}

		if (NewDevice) GInput->Devices.push_back(NewDevice);

		return DIENUM_CONTINUE;
	}
}
