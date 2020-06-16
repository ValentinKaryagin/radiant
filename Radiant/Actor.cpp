#include "Actor.h"

namespace Radiant
{
	Actor::Actor()
		: Super()
		, Parent(nullptr)
		, RootComponent(nullptr)
	{}

	Actor::~Actor() {}

	void Actor::OnCreate(Scene *SpawnInScene)
	{

	}

	void Actor::OnDestroy(Scene *DestroyInScene)
	{

	}
}
