/*
	Filename:		DebugMessage.cpp
	Description:	Debug message class realization
	Author:			Valentin Karyagin
*/

#include "DebugMessage.h"

#include "Engine.h"

namespace Radiant
{
	DebugMessage::DebugMessage()
		: LifeTime(0.0f)
	{}

	DebugMessage::~DebugMessage() {}

	int32_t DebugMessage::Create(const std::tstring &Message, const Color &MessageColor, float MessageLifeTime)
	{
		LifeTime = MessageLifeTime;
		return MessageText.Create(&GEngine->DebugMessagesFont, Message.c_str(), MessageColor);
	}

	void DebugMessage::Destroy()
	{
		MessageText.Destroy();
	}
}
