#pragma once

#include "ActorComponent.h"

namespace Radiant
{
	class InputComponent : public ActorComponent
	{
		DECLARE_CLASS(InputComponent, ActorComponent)

	public:
		InputComponent();
		virtual ~InputComponent();
	};
}
