/*
	Filename:		PlatformAbstractLayer.h
	Description:	Platform abstract layer
	Author:			Valentin Karyagin
*/

#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS

// Application
#include "GLFWApplication.h"

// Input
#include "DirectInput.h"
#include "DirectInputDevice.h"
#include "DirectMouseDevice.h"
#include "DirectKeyboardDevice.h"
#include "DirectGameDevice.h"

// Physics
#include "BulletPhysics.h"
#include "BulletPhysicsCollisionShape.h"
#include "BulletPhysicsSphereShape.h"
#include "BulletPhysicsCapsuleShape.h"
#include "BulletPhysicsRigidBody.h"

// Renderer
#include "OpenGLRenderer.h"
#include "OpenGLTexture.h"

// VR
#include "SteamVRSystem.h"

namespace Radiant
{
	// Application
	typedef GLFWApplication	Application;

	// Input
	typedef DirectInput					Input;
	typedef DirectInputDevice			InputDevice;
	typedef DirectMouseDevice			MouseDevice;
	typedef DirectKeyboardDevice		KeyboardDevice;
	typedef DirectGameDevice			GameDevice;

	// Physics
	typedef BulletPhysics				Physics;
	typedef BulletPhysicsCollisionShape	CollisionShape;
	typedef BulletPhysicsSphereShape	SphereShape;
	typedef BulletPhysicsCapsuleShape	CapsuleShape;
	typedef BulletPhysicsRigidBody		RigidBody;

	// Renderer
	typedef OpenGLRenderer				Renderer;
	typedef OpenGLTexture				Texture;

	// VR system
	typedef SteamVRSystem				VRSystem;
}

#endif

namespace Radiant
{
	extern RADIANT_API Application	*GApplication;
	extern RADIANT_API Input		*GInput;
	extern RADIANT_API Physics		*GPhysics;
	extern RADIANT_API Renderer		*GRenderer;
	extern RADIANT_API VRSystem		*GVRSystem;
}
