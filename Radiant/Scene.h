/*
	Filename:		Scene.h
	Description:	Engine scene class
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

#include "Actor.h"

namespace Radiant
{
	class CameraComponent;

	class RADIANT_API Scene : public Object
	{
		DECLARE_CLASS(Scene, Object)

	protected:
		CameraComponent *CurrentCamera;

	protected:
		std::vector<Actor *> Actors;

	public:
		Scene();
		virtual ~Scene();

	public:
		int32_t Init();
		void Terminate();

	public:
		 template<class T>
		 __forceinline T * CreateActor()
		{
			T *NewActor = new T(std::nothrow);
			if (!NewActor) return nullptr;
			
			Actors.push_back(NewActor);
			NewActor->OnCreate(this);
			
			return NewActor;
		}

		__forceinline void DestroyActor(Actor *ActorToDestroy)
		{
			if (!ActorToDestroy) return;

			Actors.erase(std::remove(Actors.begin(), Actors.end(), ActorToDestroy), Actors.end());
			ActorToDestroy->OnDestroy(this);
			delete ActorToDestroy;
			ActorToDestroy = nullptr;
		}

	public:
		__forceinline std::vector<Actor *> * GetActors() { return &Actors; }

	public:
		CameraComponent * GetCurrentCamera() const
		{
			return CurrentCamera;
		}
	};
}
