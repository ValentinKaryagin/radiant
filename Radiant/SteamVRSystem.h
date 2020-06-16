#pragma once

#include "Object.h"

#include "VRStereo.h"
#include "Math.h"

namespace vr
{
	class IVRSystem;
	class IVRCompositor;
}

namespace Radiant
{
	class RADIANT_API SteamVRSystem
	{
		DECLARE_BASECLASS(SteamVRSystem)

	protected:
		vr::IVRSystem		*VRSystem;
		vr::IVRCompositor	*VRCompositor;
		Matrix				AbsoluteMatrix;
		Matrix				OffsetMatrix;

	protected:
		SteamVRSystem();

	public:
		virtual ~SteamVRSystem();

	public:
		int32_t Init();
		void Terminate();

	public:
		bool IsInited() const;

	public:
		void TickInput(float DeltaTime = 0.0f);
		void Present(void *Texture, EVRStereoType StereoType, EVRRenderTargetTextureType TextureType);

	public:
		void GetTargetSize(uint32_t *Width, uint32_t *Height) const;

	public:
		Matrix GetAbsoluteMatrix() const;
		Matrix GetStereoViewMatrix(EVRStereoType Eye) const;
		Matrix GetStereoProjectionMatrix(EVRStereoType Eye) const;
		Matrix GetOffsetMatrix() const;
	};
}
