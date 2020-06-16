/*
	Filename:		Plugin.h
	Description:	Plugin example
	Author:			Valentin Karyagin
*/

#pragma once

#include "..\Radiant\Plugin.h"

#ifdef _WIN64
#define PLATFORM_WINDOWS
#ifdef _WINDLL
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API __declspec(dllimport)
#endif
#endif

class PLUGIN_API Plugin : public Radiant::Plugin
{
	DECLARE_CLASS(Plugin, Radiant::Plugin)

public:
	Plugin();
	virtual ~Plugin();
};

DECLARE_PLUGIN_LOADER_INTERFACE(PLUGIN_API, Plugin)
