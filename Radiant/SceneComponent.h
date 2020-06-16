#pragma once

#include "ActorComponent.h"
#include "Transformation.h"

namespace Radiant
{
	class RADIANT_API SceneComponent : public ActorComponent
	{
		DECLARE_CLASS(SceneComponent, ActorComponent)

	protected:
		Transformation Transform;

	protected:
		SceneComponent					*Parent;
		std::vector<SceneComponent *>	Childrens;	

	public:
		SceneComponent();
		virtual ~SceneComponent();

	public:
		__forceinline void SetParent(SceneComponent *ParentComponent)
		{
			if (!ParentComponent || ParentComponent == this || ParentComponent == Parent) return;
			
			Parent = ParentComponent;
			Parent->Childrens.push_back(this);
		}

		__forceinline void UnsetParent()
		{
			if (!Parent) return;

			std::vector<SceneComponent *> *ParentChildrens = &Parent->Childrens;
			ParentChildrens->erase(std::remove(ParentChildrens->begin(), ParentChildrens->end(), Parent), ParentChildrens->end());

			Parent = nullptr;
		}

		__forceinline SceneComponent * GetParent() const
		{
			return Parent;
		}

		__forceinline bool HasParent() const
		{
			return Parent != nullptr;
		}

	public:
		__forceinline void SetChildren(SceneComponent *ComponentToChildren)
		{
			if (!ComponentToChildren || ComponentToChildren == this || ComponentToChildren->Parent == this) return;

			Childrens.push_back(ComponentToChildren);
			ComponentToChildren->Parent = this;
		}

		__forceinline void UnsetChildren(SceneComponent *ComponentToFree)
		{
			// todo
		}

	public:
		template<class T>
		__forceinline T * GetChildren() const
		{
			T *CastedComponent = nullptr;
			for (auto &Item : Childrens)
			{
				CastedComponent = dynamic_cast<T *>(Item);
				if (CastedComponent) return CastedComponent;
			}
			return nullptr;
		}

		__forceinline const std::vector<SceneComponent *> * GetChildrens() const
		{
			return &Childrens;
		}

		__forceinline std::vector<SceneComponent *> * GetChildrens()
		{
			return &Childrens;
		}	

		template<class T>
		__forceinline const std::vector<T *> GetChildrens() const
		{
			std::vector<T *> Result;
			T *CastedComponent = nullptr;
			for (auto &Item : Childrens)
			{
				CastedComponent = dynamic_cast<T *>(Item);
				if (CastedComponent) Result.push_back(CastedComponent);
			}
			return Result;
		}

		__forceinline bool HasChildrens() const
		{
			return !Childrens.empty();
		}
	};
}
