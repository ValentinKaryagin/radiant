/*
	Filename:		EngineLogic.h
	Description:	Engine logic class
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

namespace Radiant
{
	class Scene;

	class RADIANT_API EngineLogic : public Object
	{
		DECLARE_CLASS(EngineLogic, Object)

	protected:
		Scene *CurrentScene;

	protected:
		EngineLogic();

	public:
		virtual ~EngineLogic();

	public:
		virtual int32_t Init();
		virtual void Terminate();

	public:
		__forceinline void SetCurrentScene(Scene *SceneToSet)
		{
			CurrentScene = SceneToSet;
		}

		__forceinline Scene * GetCurrentScene() const
		{
			return CurrentScene;
		}
	};
}
