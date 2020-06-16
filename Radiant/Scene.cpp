/*
	Filename:		Scene.cpp
	Description:	Engine scene class realization
	Author:			Valentin Karyagin
*/

#include "Scene.h"

#include "CameraComponent.h"

namespace Radiant
{
	Scene::Scene()
		: CurrentCamera(nullptr)
	{}

	Scene::~Scene() {}

	int32_t Scene::Init()
	{
		if (!CurrentCamera)
		{
			CurrentCamera = CameraComponent::GetInstance();
			printf("Camera not defined but created automatically\n");
		}

		return 0;
	}

	void Scene::Terminate()
	{

	}
}
