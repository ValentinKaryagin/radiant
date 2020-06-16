/*
	Filename:		Launcher.cpp
	Description:	Engine launcher
	Author:			Valentin Karyagin
*/

#include "..\Radiant\Radiant.h"
#include "..\Game\Game.h"

#include <tchar.h>

using namespace Radiant;

int _tmain(int ArgsCount, tchar **Args)
{
	setlocale(LC_ALL, "Russian");
	
	GEngine = GameEngine::GetInstance();

	GEngine->SetLogic(Game::GetInstance());

	int32_t ErrorLevel = GEngine->Init(ArgsCount, Args);
	if (ErrorLevel) return ErrorLevel;

	ErrorLevel = GEngine->Loop();
	if (ErrorLevel) return ErrorLevel;

	GEngine->Terminate();

	return 0;
}
