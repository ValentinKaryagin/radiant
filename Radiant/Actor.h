#pragma once

#include "Object.h"

namespace Radiant
{
	class Scene;
	class SceneComponent;

	class RADIANT_API Actor : public Object
	{
		DECLARE_CLASS(Actor, Object)

	public:
		friend Scene;

	public:
		Actor					*Parent;
		std::vector<Actor *>	Childrens;

	protected:
		SceneComponent *RootComponent;

	public:
		Actor();
		virtual ~Actor();

	public:
		__forceinline void SetParent(Actor *ParentActor)
		{
			if (!ParentActor || ParentActor == this || ParentActor == Parent) return;

			Parent = ParentActor;
			Parent->Childrens.push_back(this);
		}

		__forceinline void UnsetParent()
		{
			if (!Parent) return;

			std::vector<Actor *> *ParentChildrens = &Parent->Childrens;
			ParentChildrens->erase(std::remove(ParentChildrens->begin(), ParentChildrens->end(), Parent), ParentChildrens->end());

			Parent = nullptr;
		}

		__forceinline Actor * GetParent() const
		{
			return Parent;
		}

		__forceinline bool HasParent() const
		{
			return Parent != nullptr;
		}

	public:
		__forceinline void SetChildren(Actor *ActorToChildren)
		{
			if (!ActorToChildren || ActorToChildren == this || ActorToChildren->Parent == this) return;
			
			Childrens.push_back(ActorToChildren);
			ActorToChildren->Parent = this;
		}

		__forceinline void UnsetChildren(Actor *ActorToFree)
		{
			// todo
		}

	public:

		template<class T>
		__forceinline T * GetChildren() const
		{
			T *CastedActor = nullptr;
			for (auto &Item : Childrens)
			{
				CastedActor = dynamic_cast<T *>(Item);
				if (CastedActor) return CastedActor;
			}
			return nullptr;
		}

		__forceinline const std::vector<Actor *> * GetChildrens() const
		{
			return &Childrens;
		}

		__forceinline std::vector<Actor *> * GetChildrens()
		{
			return &Childrens;
		}

		template<class T>
		__forceinline const std::vector<T *> GetChildrens() const
		{
			std::vector<T *> Result;
			T *CastedActor = nullptr;
			for (auto &Item : Childrens)
			{
				CastedActor = dynamic_cast<T *>(Item);
				if (CastedActor) Result.push_back(CastedActor);
			}
		}

		__forceinline bool HasChildrens() const
		{
			return !Childrens.empty();
		}

	public:
		__forceinline void SetRootComponent(SceneComponent *ComponentToSet)
		{
			RootComponent = ComponentToSet;
		};

		__forceinline SceneComponent * GetRootComponent() const
		{
			return RootComponent;
		};
		
	public:
		virtual void OnCreate(Scene *SpawnInScene);
		virtual void OnDestroy(Scene *DestroyInScene);
	};
}
