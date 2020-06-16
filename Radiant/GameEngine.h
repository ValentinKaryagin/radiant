/*
	Filename:		GameEngine.h
	Description:	Game Engine class
	Author:			Valentin Karyagin
*/

#include "Engine.h"

namespace Radiant
{
	class RADIANT_API GameEngine : public Engine
	{
		DECLARE_CLASS(GameEngine, Engine)

	protected:
		GameEngine();

	public:
		virtual ~GameEngine();
	};
}
