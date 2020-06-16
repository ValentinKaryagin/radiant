/*
	Filename:		SDL2Surface.h
	Description:	Surface class that implemented by SDL2 library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

#include "Misc.h"

struct SDL_Surface;

namespace Radiant
{
	class SDL2FontTTF;

	class RADIANT_API SDL2Surface
	{
		DECLARE_BASECLASS(SDL2Surface)

	protected:
		SDL_Surface *Surface;

	public:
		SDL2Surface();
		virtual ~SDL2Surface();

	public:
		int32_t Create(const char *ImageFile);
		int32_t Create(SDL2FontTTF *Font, const tchar *Text, const Color &TextColor = Color::White);
		void Destroy();
		int32_t GetWidth() const;
		int32_t GetHeight() const;
		void * GetData() const;
	};
}
