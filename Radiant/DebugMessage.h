/*
	Filename:		DebugMessage.h
	Description:	Debug message class
	Author:			Valentin Karyagin
*/

#pragma once

#include "Commons.h"
#include "Misc.h"

namespace Radiant
{
	struct RADIANT_API DebugMessage
	{
		Surface	MessageText;
		float	LifeTime;

		DebugMessage();
		virtual ~DebugMessage();

		int32_t Create(const std::tstring &Message, const Color &MessageColor = Color::White, float MessageLifeTime = 1.0f);
		void Destroy();
	};
}
