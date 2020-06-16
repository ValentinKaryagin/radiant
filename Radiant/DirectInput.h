/*
	Filename:		DirectInput.h
	Description:	Input class that implemented by DirectInput (part of DirectX) library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

struct IDirectInput8A;
struct DIDEVICEINSTANCEA;

namespace Radiant
{
	class DirectInputDevice;

	class RADIANT_API DirectInput
	{
		DECLARE_BASECLASS(DirectInput)

	protected:
		std::list<DirectInputDevice *> Devices;

	protected:
		IDirectInput8A* Driver;

	protected:
		DirectInput();

	public:
		virtual ~DirectInput();

	public:
		int32_t Init();
		void Terminate();

	public:
		void Tick(float DeltaTime = 0.0f);

	public:
		static BOOL EnumAndCreateDevices(const DIDEVICEINSTANCEA *Device, void *UserPtr);
	};
}
