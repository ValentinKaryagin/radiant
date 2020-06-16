/*
	Filename:		BulletPhysicsCapsuleShape.h
	Description:	Sphere collision shape class that implemented by BulletPhysics library
	Author:			Valentin Karyagin
*/

#pragma once

#include "BulletPhysicsCollisionShape.h"

namespace Radiant
{
	class RADIANT_API BulletPhysicsCapsuleShape : public BulletPhysicsCollisionShape
	{
		DECLARE_CLASS(BulletPhysicsCapsuleShape, BulletPhysicsCollisionShape)

	public:
		BulletPhysicsCapsuleShape(float Radius = 1.0f, float Height = 2.0f);
		virtual ~BulletPhysicsCapsuleShape();
	};
}
