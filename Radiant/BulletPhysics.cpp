/*
	Filename:		BulletPhysics.cpp
	Description:	BulletPhysics class realization
	Author:			Valentin Karyagin
*/

#include "BulletPhysics.h"

#include "glfw3.h"
#include "btBulletDynamicsCommon.h"

#include "BulletPhysicsRigidBody.h"

namespace Radiant
{
	class BulletPhysicsDrawer : public btIDebugDraw
	{
	private:
		int32_t DrawMode;

	private:
		__forceinline BulletPhysicsDrawer()
			: DrawMode(DBG_DrawWireframe)
		{}

	public:
		__forceinline ~BulletPhysicsDrawer() {}

	public:
		__forceinline void drawLine(const btVector3 &From, const btVector3 &To, const btVector3 &Color) override
		{
			glBegin(GL_LINES);
			glColor3f(Color.getX(), Color.getY(), Color.getZ());
			glVertex3f(From.getX(), From.getY(), From.getZ());
			glVertex3f(To.getX(), To.getY(), To.getZ());
			glEnd();
		}

		__forceinline void drawLine(const btVector3 &From, const btVector3 &To, const btVector3 &FromColor, const btVector3 &ToColor) override
		{
			glBegin(GL_LINES);
			glColor3f(FromColor.getX(), FromColor.getY(), FromColor.getZ());
			glVertex3f(From.getX(), From.getY(), From.getZ());
			glColor3f(ToColor.getX(), ToColor.getY(), ToColor.getZ());
			glVertex3f(To.getX(), To.getY(), To.getZ());
			glEnd();
		}

		__forceinline void drawContactPoint(const btVector3 &PointOnB, const btVector3 &NormalOnB, btScalar Distance, int32_t LifeTime, const btVector3 &Color) override
		{
			
		}

		__forceinline void reportErrorWarning(const char *WarningString) override
		{
			printf("%s\n", WarningString);
		}

		__forceinline void draw3dText(const btVector3 &Location, const char *TextString) override
		{
			
		}

		__forceinline void setDebugMode(int32_t DebugMode) override
		{
			DrawMode = DebugMode;
		}

		__forceinline int32_t getDebugMode() const override
		{
			return DrawMode;
		}

	public:
		__forceinline static BulletPhysicsDrawer * GetInstance()
		{
			static BulletPhysicsDrawer BulletPhysicsDrawerInstance;
			return &BulletPhysicsDrawerInstance;
		}
	};
}

namespace Radiant
{
	BulletPhysics::BulletPhysics()
		: Broadphase(new btDbvtBroadphase())
		, Configuration(new btDefaultCollisionConfiguration())
		, Dispatcher(new btCollisionDispatcher(Configuration))
		, Solver(new btSequentialImpulseConstraintSolver())
		, DynamicsWorld(new btDiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, Configuration))
	{}

	BulletPhysics::~BulletPhysics()
	{
		delete DynamicsWorld;
		delete Solver;
		delete Dispatcher;
		delete Configuration;
		delete Broadphase;
	}

	int32_t BulletPhysics::Init()
	{
		DynamicsWorld->setGravity(btVector3(0.0f, 0.0f, 0.0f));
		DynamicsWorld->setDebugDrawer(BulletPhysicsDrawer::GetInstance());

		return 0;
	}

	void BulletPhysics::Terminate()
	{
		DynamicsWorld->setDebugDrawer(nullptr);
	}

	void BulletPhysics::Tick(float DeltaTime)
	{
		DynamicsWorld->stepSimulation(DeltaTime);
	}

	void BulletPhysics::AddRigidBody(BulletPhysicsRigidBody *RigidBodyToAdd)
	{
		DynamicsWorld->addRigidBody(RigidBodyToAdd->RigidBody);
	}

	void BulletPhysics::RemoveRigidBody(BulletPhysicsRigidBody *RigidBodyToRemove)
	{
		DynamicsWorld->removeRigidBody(RigidBodyToRemove->RigidBody);
	}

	void BulletPhysics::DrawCollisions()
	{
		DynamicsWorld->debugDrawWorld();
	}
}
