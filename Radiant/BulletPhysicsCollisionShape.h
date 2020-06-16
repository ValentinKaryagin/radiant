/*
	Filename:		BulletPhysicsCollisionShape.h
	Description:	Base collision shape class that implemented by BulletPhysics library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

class btCollisionShape;

namespace Radiant
{
	class RADIANT_API BulletPhysicsCollisionShape
	{
		DECLARE_BASECLASS(BulletPhysicsCollisionShape)

	public:
		friend class BulletPhysicsRigidBody;

	protected:
		btCollisionShape *CollisionShape;

	public:
		BulletPhysicsCollisionShape(btCollisionShape *CollisionShape = nullptr);
		virtual ~BulletPhysicsCollisionShape();

	public:
		void SetCollisionShape(btCollisionShape *NewCollisionShape);
		btCollisionShape * GetCollisionShape() const;
	};
}
