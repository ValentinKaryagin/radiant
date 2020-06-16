/*
	Filename:		SDL2FontTTF.cpp
	Description:	SDl2 true type font realization
	Author:			Valentin Karyagin
*/

#include "SDL2FontTTF.h"

#include "Assert.h"

#include "SDL_ttf.h"

namespace Radiant
{
	SDL2FontTTF::SDL2FontTTF()
		: TTFFont(nullptr)
	{}

	SDL2FontTTF::~SDL2FontTTF() {}

	int32_t SDL2FontTTF::Create(const char *FontFile, size_t FontSize)
	{
		TTFFont = TTF_OpenFont(FontFile, static_cast<int>(FontSize));
		return TTFFont ? 0 : 1;
	}

	void SDL2FontTTF::Destroy()
	{
		TTF_CloseFont(TTFFont);
		TTFFont = nullptr;
	}
}
