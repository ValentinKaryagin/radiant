/*
	Filename:		BulletPhysicsSphereShape.cpp
	Description:	BulletPhysics sphere collision shape class realization
	Author:			Valentin Karyagin
*/

#include "BulletPhysicsSphereShape.h"

#include "btBulletDynamicsCommon.h"

namespace Radiant
{
	BulletPhysicsSphereShape::BulletPhysicsSphereShape(float Radius)
		: Super(new btSphereShape(Radius))
	{}

	BulletPhysicsSphereShape::~BulletPhysicsSphereShape()
	{
		delete CollisionShape;
	}
}
