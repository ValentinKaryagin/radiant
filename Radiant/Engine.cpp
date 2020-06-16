/*
	Filename:		Engine.h
	Description:	Base Engine class realization
	Author:			Valentin Karyagin
*/

#include "Engine.h"

#include "Application.h"
#include "Input.h"
#include "Physics.h"
#include "Renderer.h"
#include "VRSystem.h"

#include "PluginsManager.h"
#include "EngineLogic.h"
#include "Scene.h"
#include "CameraComponent.h"

namespace Radiant
{
	Engine::Engine()
		: IsExitRequested(false)
		, IsDrawVR(false)
		, IsDrawViewport(true)
#ifdef CONFIGURATION_DEBUG
		, IsDrawCollisions(true)
		, IsDrawDebugMessages(true)
		, IsDrawDrawInfo(true)
#else
		, IsDrawCollisions(true)
		, IsDrawDebugMessages(true)
		, IsDrawDrawInfo(true)
		
#endif		
		, DeltaTime(0.0f)
		, DebugMessagesColor(Color::White)
		, LogicGetInstance(nullptr)
		, Logic(nullptr)
		, PluginsManager(PluginsManager::GetInstance())
		
	{}

	Engine::~Engine() {}

	int32_t Engine::HotLoad(const tchar *DllName)
	{
		HotReloadDllHandle = WindowsAPI::LoadDll(DllName);
		if (!HotReloadDllHandle) return 1;

		LogicGetInstance = reinterpret_cast<EngineLogicGetInstanceFuncPtr>(WindowsAPI::GetProcAddrFromDll(HotReloadDllHandle, TXT("LogicGetInstance")));
		if (!LogicGetInstance) return 2;

		Logic = LogicGetInstance();
		if (!Logic) return 3;

		return 0;
	}

	int32_t Engine::HotFree()
	{
		if (!WindowsAPI::FreeDll(HotReloadDllHandle)) return 1;
		return 0;
	}

	int32_t Engine::HotReload(const tchar *DllName)
	{
		int32_t ErrorLevel = HotFree();
		if (ErrorLevel) return 1;

		ErrorLevel = HotLoad(DllName);
		if (ErrorLevel) return 2;

		return 0;
	}

	int32_t Engine::Init(size_t ArgsCount, tchar **Args)
	{
		bool IsVRMode = false;

		for (size_t ArgIndex = 0; ArgIndex < ArgsCount; ++ArgIndex)
		{
			std::tstring Argument = Args[ArgIndex];
			std::transform(Argument.begin(), Argument.end(), Argument.begin(), tolower);

			if (Argument == TXT("-vr")) IsVRMode = true;
		}

		GApplication = Application::GetInstance();
		int32_t ErrorLevel = GApplication->Init();
		if (ErrorLevel) return 1;

		GInput = Input::GetInstance();
		ErrorLevel = GInput->Init();
		if (ErrorLevel) return 2;

		ErrorLevel = DebugMessagesFont.Create("consolas.ttf", 14);
		if (ErrorLevel) return 3;

		GPhysics = Physics::GetInstance();
		ErrorLevel = GPhysics->Init();
		if (ErrorLevel) return 4;				

		GRenderer = Renderer::GetInstance();
		ErrorLevel = GRenderer->Init();
		if (ErrorLevel) return 5;

		if (IsVRMode)
		{
			GVRSystem = VRSystem::GetInstance();
			ErrorLevel = GVRSystem->Init();

			uint32_t Width, Height;

			GVRSystem->GetTargetSize(&Width, &Height);

			GApplication->SetWindowSize(Width, Height);

			GApplication->GetWindowSize(&Width, &Height);

			if (Width != Height) GApplication->SetWindowSize(Height, Height);

			ErrorLevel = GRenderer->InitVRContext();

			IsDrawVR = true;
		}

		if (!Logic) return 7;
		ErrorLevel = Logic->Init();
		if (ErrorLevel) return 8;

		ErrorLevel = PluginsManager->LoadPlugins();
		if (ErrorLevel) return 9;

		// TODELETE: Begin
		for (size_t i = 0; i < 64; ++i)
		{
			ShowDebugMessage(TXT("Message ") + std::to_tstring(i), Color::White, static_cast<float>(i * 3));
			GPhysics->AddRigidBody(new RigidBody(new SphereShape(), 1.0f));
		}
		// TODELETE: End

		return 0;
	}

	void Engine::Terminate()
	{
		PluginsManager->UnloadPlugins();
		Logic->Terminate();
		if (GVRSystem && GVRSystem->IsInited())
		{
			GVRSystem->Terminate();
			GRenderer->TerminateVRContext();
		}
		GRenderer->Terminate();
		GPhysics->Terminate();
		DebugMessagesFont.Destroy();
		GInput->Terminate();
		GApplication->Terminate();
	}

	int32_t Engine::Loop()
	{
		while (!IsExitRequested)
		{
			DeltaTime = TimeManager.CalcDeltaTime();
#ifdef MULTITHREADED
			// TODO: Multithreading
#else
			UpdateDebugMessages();

			GApplication->Tick();
			GInput->Tick();
			if (GVRSystem && GVRSystem->IsInited()) GVRSystem->TickInput();
			GPhysics->Tick(DeltaTime);
			GRenderer->Tick();

			TimeManager.Update();
#endif		
		}

		return 0;
	}

	void Engine::GetViewportSize(uint32_t *OutWidth, uint32_t *OutHeight) const
	{
		GApplication->GetWindowSize(OutWidth, OutHeight);
	}

	float Engine::GetViewportAspectRatio() const
	{
		return GApplication->GetWindowAspectRatio();
	}

	float Engine::GetCurrentCameraFoV() const
	{
		return Logic->GetCurrentScene()->GetCurrentCamera()->GetFoV();
	}

	void Engine::ShowDebugMessage(const std::tstring &Message, const Color &MessageColor, float LifeTime)
	{
		DebugMessage MessageToPush;
		MessageToPush.Create(Message, MessageColor, LifeTime);
		DebugMessages.push_back(MessageToPush);
	}

	void Engine::UpdateDebugMessages()
	{
		for (auto &Item : DebugMessages) Item.LifeTime -= DeltaTime;
		DebugMessages.remove_if(
			[](DebugMessage &Message)
		{
			bool Result = Message.LifeTime < 0.0f;
			if (Result) Message.Destroy();
			return Result;
		});
	}
}

namespace Radiant
{
	extern Engine *GEngine = nullptr;
}
