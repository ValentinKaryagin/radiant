#pragma once

#include "SceneComponent.h"

namespace Radiant
{
	constexpr const float FOV_DEFAULT = 60.0f;

	class RADIANT_API CameraComponent : public SceneComponent
	{
		DECLARE_CLASS(CameraComponent, SceneComponent)

	protected:
		float FoV;

	public:
		CameraComponent();
		virtual ~CameraComponent();

	public:
		__forceinline void SetFoV(float FoVToSet)
		{
			FoV = FoVToSet;
		}

		__forceinline float GetFoV() const
		{
			return FoV;
		}

		__forceinline void AddFoV(float FoVToAdd)
		{
			FoV += FoVToAdd;
		}

		__forceinline void ResetFoV()
		{
			FoV = FOV_DEFAULT;
		}
	};
}
