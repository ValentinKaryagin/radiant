/*
	Filename:		SDL2CommonsInitializer.h
	Description:	SDL2 library initializer realization
	Author:			Valentin Karyagin
*/

#include "SDL2CommonsInitializer.h"

#include "Assert.h"

#include "SDL_image.h"
#include "SDL_ttf.h"

namespace Radiant
{
	extern SDL2CommonsInitializer *GCommons = SDL2CommonsInitializer::GetInstance();
}

namespace Radiant
{
	SDL2CommonsInitializer::SDL2CommonsInitializer()
	{
		ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0);
		ASSERT(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) & (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP));
		ASSERT(TTF_Init() == 0);
	}

	SDL2CommonsInitializer::~SDL2CommonsInitializer()
	{
		TTF_Quit();
		IMG_Quit();		
		SDL_Quit();
	}
}
