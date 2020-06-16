/*
	Filename:		Game.h
	Description:	Simple game logic
	Author:			Valentin Karyagin
*/

#pragma once

#include "..\Radiant\Radiant.h"

#ifdef _WINDLL
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif

class GAME_API Game : public Radiant::EngineLogic
{
	DECLARE_CLASS(Game, EngineLogic)

public:
	Game();
	~Game();
};
