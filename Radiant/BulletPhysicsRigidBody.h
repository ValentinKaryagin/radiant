/*
	Filename:		BulletPhysicsRigidBody.h
	Description:	Rigidbody class that implemented by BulletPhysics library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

struct btDefaultMotionState;
class btRigidBody;

namespace Radiant
{
	class BulletPhysicsCollisionShape;

	class RADIANT_API BulletPhysicsRigidBody
	{
		DECLARE_BASECLASS(BulletPhysicsRigidBody)

	public:
		friend class BulletPhysics;

	protected:		
		btDefaultMotionState	*MotionState;
		btRigidBody				*RigidBody;

	public:
		BulletPhysicsRigidBody();
		BulletPhysicsRigidBody(BulletPhysicsCollisionShape *CollisionShape, float Mass = 0.0f);
		virtual ~BulletPhysicsRigidBody();
	};
}
