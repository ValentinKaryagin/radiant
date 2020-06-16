#pragma once

#include "SceneComponent.h"

namespace Radiant
{
	class AudioComponent : public SceneComponent
	{
		DECLARE_CLASS(AudioComponent, SceneComponent)

	public:
		AudioComponent();
		virtual ~AudioComponent();
	};
}
