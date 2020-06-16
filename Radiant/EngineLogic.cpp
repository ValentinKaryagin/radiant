/*
	Filename:		EngineLogic.cpp
	Description:	Engine logic class realization
	Author:			Valentin Karyagin
*/

#include "EngineLogic.h"

#include "Scene.h"

namespace Radiant
{
	EngineLogic::EngineLogic()
		: Super()
		, CurrentScene(nullptr)
	{}

	EngineLogic::~EngineLogic() {}

	int32_t EngineLogic::Init()
	{
		if (!CurrentScene)
		{
			CurrentScene = Scene::GetInstance();
			printf("Scene not defined but created automatically\n");
		}

		int32_t ErrorLevel = CurrentScene->Init();
		if (ErrorLevel) return 1;

		return 0;
	}

	void EngineLogic::Terminate()
	{
		CurrentScene->Terminate();
	}
}
