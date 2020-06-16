/*
	Filename:		BulletPhysicsRigidBody.cpp
	Description:	BulletPhysics rigidbody class realization
	Author:			Valentin Karyagin
*/

#include "BulletPhysicsRigidBody.h"

#include "BulletPhysicsCollisionShape.h"

#include "btBulletDynamicsCommon.h"

namespace Radiant
{
	BulletPhysicsRigidBody::BulletPhysicsRigidBody()
		: MotionState(nullptr)
		, RigidBody(nullptr)
	{}

	BulletPhysicsRigidBody::BulletPhysicsRigidBody(BulletPhysicsCollisionShape *CollisionShape, float Mass)
		: MotionState(new btDefaultMotionState(btTransform(btQuaternion::getIdentity(), btVector3(10.0f, 0.0f, 0.0f))))
		, RigidBody(new btRigidBody(Mass, MotionState, CollisionShape->CollisionShape))
	{}

	BulletPhysicsRigidBody::~BulletPhysicsRigidBody()
	{
		if (RigidBody) delete RigidBody;
		if (MotionState) delete MotionState;
	}
}
