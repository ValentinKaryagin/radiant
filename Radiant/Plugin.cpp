/*
	Filename:		Plugin.cpp
	Description:	Base plugin class realization
	Author:			Valentin Karyagin
*/

#include "Plugin.h"

namespace Radiant
{
	Plugin::Plugin()
		: Super()
		, Name(TXT("Unnamed"))
		, Version(TXT("Unversioned"))
		, Author(TXT("Unauthored"))
		, Logic(nullptr)
	{
		
	}

	Plugin::~Plugin() {}

	void Plugin::OnInit(EngineLogic *OnInitLogic)
	{
		Logic = OnInitLogic;
	}

	void Plugin::OnTerminate()
	{

	}

	void Plugin::Tick(float DeltaTime)
	{

	}
}
