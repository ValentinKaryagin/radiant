#pragma once

#include "Actor.h"

namespace Radiant
{
	class RADIANT_API StaticMeshActor :	public Actor
	{
		DECLARE_CLASS(StaticMeshActor, Actor)

	public:
		StaticMeshActor();
		virtual ~StaticMeshActor();
	};
}
