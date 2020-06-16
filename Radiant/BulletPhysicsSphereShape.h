/*
	Filename:		BulletPhysicsSphereShape.h
	Description:	Sphere collision shape class that implemented by BulletPhysics library
	Author:			Valentin Karyagin
*/

#pragma once

#include "BulletPhysicsCollisionShape.h"

namespace Radiant
{
	class RADIANT_API BulletPhysicsSphereShape : public BulletPhysicsCollisionShape
	{
		DECLARE_CLASS(BulletPhysicsSphereShape, BulletPhysicsCollisionShape)

	public:
		BulletPhysicsSphereShape(float Radius = 1.0f);
		virtual ~BulletPhysicsSphereShape();
	};
}
