/*
	Filename:		BulletPhysics.h
	Description:	Physics class that implemented by BulletPhysics library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

namespace Radiant
{
	class BulletPhysicsRigidBody;

	class RADIANT_API BulletPhysics
	{
		DECLARE_BASECLASS(BulletPhysics)

	protected:
		btBroadphaseInterface				*Broadphase;
		btDefaultCollisionConfiguration		*Configuration;
		btCollisionDispatcher				*Dispatcher;
		btSequentialImpulseConstraintSolver	*Solver;
		btDiscreteDynamicsWorld				*DynamicsWorld;

	protected:
		BulletPhysics();

	public:
		virtual ~BulletPhysics();

	public:
		int32_t Init();

	public:
		void Terminate();

	public:
		void Tick(float DeltaTime = 0.0f);

	public:
		void AddRigidBody(BulletPhysicsRigidBody *RigidBodyToAdd);
		void RemoveRigidBody(BulletPhysicsRigidBody *RigidBodyToRemove);

	public:
		void DrawCollisions();
	};
}
