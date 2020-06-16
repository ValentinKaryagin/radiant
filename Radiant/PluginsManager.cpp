/*
	Filename:		PluginsManager.cpp
	Description:	Plugins manager class realization
	Author:			Valentin Karyagin
*/

#include "PluginsManager.h"

#include "Plugin.h"

#include "Engine.h"

#define PLUGINS_LIST_FILENAME TEXT("plugins.list")

namespace Radiant
{
	PluginsManager::PluginsManager()
		: Super()
	{}

	PluginsManager::~PluginsManager() {}

	int32_t PluginsManager::LoadPlugins()
	{
		std::tifstream PluginsList(PLUGINS_LIST_FILENAME);
		std::tstring PluginName;
		while (std::getline(PluginsList, PluginName))
		{
			PluginDescription PluginDesc = { PluginName, WindowsAPI::LoadDll((PluginName + TXT(".dll")).c_str()), nullptr };
			if (!PluginDesc.DllHandle) return 1;
			else
			{
				PluginDesc.PluginGetInstance = reinterpret_cast<PluginGetInstanceFuncPtr>(WindowsAPI::GetProcAddrFromDll(PluginDesc.DllHandle, (PluginName + TXT("Load")).c_str()));

				if (!PluginDesc.PluginGetInstance) return 2;
				else
				{
					Plugin *PluginInstance = PluginDesc.PluginGetInstance();
					if (!PluginInstance) return 3;
					else
					{
						PluginDescriptions.push_back(PluginDesc);
						Plugins.push_back(PluginInstance);

						PluginInstance->OnInit(GEngine->GetLogic());
					}
				}
			}
		}

		return 0;
	}

	int32_t PluginsManager::UnloadPlugins()
	{
		for (auto &Item : Plugins)
		{
			Item->OnTerminate();
		}

		Plugins.clear();

		for (auto &Item : PluginDescriptions)
		{
			Item.PluginGetInstance = nullptr;
			if (!WindowsAPI::FreeDll(Item.DllHandle)) return 1;
		}

		PluginDescriptions.clear();

		return 0;
	}

	int32_t PluginsManager::ReloadPlugins()
	{
		int32_t ErrorLevel = UnloadPlugins();
		if (ErrorLevel) return 1;

		ErrorLevel = LoadPlugins();
		if (ErrorLevel) return 2;

		return 0;
	}
}
