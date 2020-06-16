/*
	Filename:		BulletPhysicsCapsuleShape.cpp
	Description:	BulletPhysics sphere collision shape class realization
	Author:			Valentin Karyagin
*/

#include "BulletPhysicsCapsuleShape.h"

#include "btBulletDynamicsCommon.h"

namespace Radiant
{
	BulletPhysicsCapsuleShape::BulletPhysicsCapsuleShape(float Radius, float Height)
		: Super(new btCapsuleShapeZ(Radius, Height))
	{}

	BulletPhysicsCapsuleShape::~BulletPhysicsCapsuleShape()
	{
		delete CollisionShape;
	}
}
