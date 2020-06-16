/*
	Filename:		SDL2Surface.cpp
	Description:	SDL2 surface realization
	Author:			Valentin Karyagin
*/

#include "SDL2Surface.h"

#include "SDL2FontTTF.h"

#include "SDL_image.h"
#include "SDL_ttf.h"

namespace Radiant
{
	SDL2Surface::SDL2Surface()
		: Surface(nullptr)
	{}

	SDL2Surface::~SDL2Surface() {}

	int32_t SDL2Surface::Create(const char *ImageFile)
	{
		Surface = IMG_Load(ImageFile);
		return Surface ? 0 : 1;
	}

	int32_t SDL2Surface::Create(SDL2FontTTF *Font, const tchar *Text, const Color &TextColor)
	{	
		TTF_Font *SDL2TTFFont = Font->GetSDLFont();

		SDL_Color SDLColor = { TextColor.R, TextColor.G, TextColor.B, TextColor.A };

#ifdef CHARSET_UNICODE
		Surface = TTF_RenderUNICODE_Blended(Font->GetSDLFont(), reinterpret_cast<const Uint16 *>(Text), SDLColor);
#else
		Surface = TTF_RenderText_Blended(Font->GetSDLFont(), Text, SDLColor);
#endif
		return Surface ? 0 : 2;
	}

	void SDL2Surface::Destroy()
	{
		SDL_FreeSurface(Surface);
		Surface = nullptr;
	}

	int32_t SDL2Surface::GetWidth() const
	{
		return Surface->w;
	}

	int32_t SDL2Surface::GetHeight() const
	{
		return Surface->h;
	}

	void * SDL2Surface::GetData() const
	{
		return Surface->pixels;
	}
}
