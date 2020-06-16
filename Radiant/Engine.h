/*
	Filename:		Engine.h
	Description:	Base Engine class
	Author:			Valentin Karyagin
*/

#pragma once

#include "Timer.h"
#include "DebugMessage.h"

namespace Radiant
{
	class EngineLogic;
	class PluginsManager;

	class RADIANT_API Engine : public Object
	{
		DECLARE_CLASS(Engine, Object)

	private:
		HMODULE HotReloadDllHandle;
		typedef EngineLogic * (* EngineLogicGetInstanceFuncPtr)();
		EngineLogicGetInstanceFuncPtr LogicGetInstance;

	public:
		bool IsExitRequested;

	public:
		bool IsDrawVR;
		bool IsDrawViewport;
		bool IsDrawCollisions;
		bool IsDrawDebugMessages;
		bool IsDrawDrawInfo;

	protected:
		float DeltaTime;

	public:
		FontTTF DebugMessagesFont;
		Color	DebugMessagesColor;

	public:
		std::list<DebugMessage> DebugMessages;

	protected:
		Timer TimeManager;

	protected:
		EngineLogic		*Logic;
		PluginsManager	*PluginsManager;

	protected:
		Engine();

	public:
		virtual ~Engine();

	public:
		__forceinline void SetLogic(EngineLogic *LogicToSet)
		{
			Logic = LogicToSet;
		};

		__forceinline EngineLogic * GetLogic() const
		{
			return Logic;
		};

	public:
		int32_t HotLoad(const tchar *DllName);
		int32_t HotFree();
		int32_t HotReload(const tchar *DllName);

	public:
		int32_t Init(size_t ArgsCount, tchar **Args);
		void Terminate();

	public:
		int32_t Loop();

	public:
		void GetViewportSize(uint32_t *OutWidth, uint32_t *OutHeight) const;
		float GetViewportAspectRatio() const;
		float GetCurrentCameraFoV() const;

	public:
		void ShowDebugMessage(const std::tstring &Message, const Color &MessageColor = Color::White, float LifeTime = 1.0f);

	public:
		__forceinline float GetDeltaTime() const
		{
			return DeltaTime;
		}

	private:
		void UpdateDebugMessages();
	};
}

namespace Radiant
{
	extern RADIANT_API Engine *GEngine;

}
