/*
	Filename:		Plugin.cpp
	Description:	Plugin example realization
	Author:			Valentin Karyagin
*/

#include "Plugin.h"

Plugin::Plugin()
{
	Name	= TXT("Plugin");
	Version	= TXT("1.0");
	Author	= TXT("Valentin Karyagin");

#ifdef CHARSET_UNICODE
	tprintf(TXT("Plugin Loaded: %ws %ws %ws\n"), Name, Version, Author);
#else
	tprintf(TXT("Plugin Loaded: %s %s %s\n"), Name, Version, Author);
#endif
}

Plugin::~Plugin()
{
#ifdef CHARSET_UNICODE
	tprintf(TXT("Plugin Unloaded: %ws %ws %ws\n"), Name, Version, Author);
#else
	tprintf(TXT("Plugin Unloaded: %s %s %s\n"), Name, Version, Author);
#endif
}

DECLARE_PLUGIN_LOADER_REALISATION(Plugin)
