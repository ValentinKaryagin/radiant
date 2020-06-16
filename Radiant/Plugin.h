/*
	Filename:		Plugin.h
	Description:	Base plugin class that can be externally attached to engine
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

#define DECLARE_PLUGIN_LOADER_INTERFACE(API, PluginClass) extern "C" API Radiant::Plugin * PluginClass ## Load();
#define DECLARE_PLUGIN_LOADER_REALISATION(PluginClass) Radiant::Plugin * PluginClass ## Load() { static PluginClass PluginClass ## Instance; return &PluginClass ## Instance; }

namespace Radiant
{
	class EngineLogic;

	class RADIANT_API Plugin : public Object
	{
		DECLARE_CLASS(Plugin, Object)

	protected:
		const tchar *Name;
		const tchar *Version;
		const tchar *Author;

	protected:
		EngineLogic *Logic;

	protected:
		Plugin();

	public:
		virtual ~Plugin();

	public:
		virtual void OnInit(EngineLogic *OnInitLogic);
		virtual void OnTerminate();
		virtual void Tick(float DeltaTime = 0.0f);

	public:
		__forceinline const tchar * GetName() const
		{
			return Name;
		}

		__forceinline const tchar * GetVersion() const
		{
			return Version;
		}

		__forceinline const tchar * GetAuthor() const
		{
			return Author;
		}
	};
}
