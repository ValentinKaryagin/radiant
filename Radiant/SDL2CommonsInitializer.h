/*
	Filename:		SDL2CommonsInitializer.h
	Description:	SDL2 library initializer
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

namespace Radiant
{
	class RADIANT_API SDL2CommonsInitializer
	{
		DECLARE_BASECLASS(SDL2CommonsInitializer)

	protected:
		SDL2CommonsInitializer();

	public:
		virtual ~SDL2CommonsInitializer();
	};
}
