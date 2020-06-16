/*
	Filename:		PluginsManager.h
	Description:	Plugins manager class
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

namespace Radiant
{
	class Plugin;

	class RADIANT_API PluginsManager : public Object
	{
		DECLARE_CLASS(PluginsManager, Object)

	public:
		typedef Plugin * (* PluginGetInstanceFuncPtr)();

	public:
		struct PluginDescription
		{
			std::tstring				PluginName;
			HMODULE						DllHandle;
			PluginGetInstanceFuncPtr	PluginGetInstance;
		};

	private:
		std::vector<PluginDescription>	PluginDescriptions;
		std::vector<Plugin *>			Plugins;

	protected:
		PluginsManager();

	public:
		~PluginsManager();

	public:
		int32_t LoadPlugins();
		int32_t UnloadPlugins();
		int32_t ReloadPlugins();
	};
}
