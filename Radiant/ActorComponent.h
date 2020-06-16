#pragma once

#include "Object.h"

namespace Radiant
{
	class RADIANT_API ActorComponent : public Object
	{
		DECLARE_CLASS(ActorComponent, Object)

	public:
		ActorComponent();
		virtual ~ActorComponent();
	};
}
