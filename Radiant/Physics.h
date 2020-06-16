#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS

#include "BulletPhysics.h"
#include "BulletPhysicsCollisionShape.h"
#include "BulletPhysicsSphereShape.h"
#include "BulletPhysicsCapsuleShape.h"
#include "BulletPhysicsRigidBody.h"

namespace Radiant
{
	typedef BulletPhysics				Physics;
	typedef BulletPhysicsCollisionShape	CollisionShape;
	typedef BulletPhysicsSphereShape	SphereShape;
	typedef BulletPhysicsCapsuleShape	CapsuleShape;
	typedef BulletPhysicsRigidBody		RigidBody;
}

#endif

namespace Radiant
{
	extern RADIANT_API Physics *GPhysics;
}
