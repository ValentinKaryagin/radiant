/*
	Filename:		EditorEngine.h
	Description:	Editor Engine class realization
	Author:			Valentin Karyagin
*/

#pragma once

#include "Engine.h"

namespace Radiant
{
	class RADIANT_API EditorEngine : public Engine
	{
		DECLARE_CLASS(EditorEngine, Engine)

	protected:
		EditorEngine();

	public:
		virtual ~EditorEngine();
	};
}
