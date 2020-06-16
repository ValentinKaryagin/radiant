/*
	Filename:		BulletPhysicsCollisionShape.cpp
	Description:	BulletPhysics base collision shape class realization
	Author:			Valentin Karyagin
*/

#include "BulletPhysicsCollisionShape.h"

#include "btBulletDynamicsCommon.h"

namespace Radiant
{
	BulletPhysicsCollisionShape::BulletPhysicsCollisionShape(btCollisionShape *CollisionShape)
		: CollisionShape(CollisionShape)
	{
		btVector3 Inertia(0.0f, 0.0f, 0.0f);
		CollisionShape->calculateLocalInertia(0.0f, Inertia);
	}

	BulletPhysicsCollisionShape::~BulletPhysicsCollisionShape() {}

	void BulletPhysicsCollisionShape::SetCollisionShape(btCollisionShape *NewCollisionShape)
	{
		CollisionShape = NewCollisionShape;
	}

	btCollisionShape * BulletPhysicsCollisionShape::GetCollisionShape() const
	{
		return CollisionShape;
	}
}
