/*
	Filename:		SDL2FontTTF.h
	Description:	True type font class that implemented by SDL2 library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

struct _TTF_Font;

namespace Radiant
{
	class RADIANT_API SDL2FontTTF
	{
		DECLARE_BASECLASS(SDL2FontTTF)

	protected:
		_TTF_Font *TTFFont;

	public:
		SDL2FontTTF();
		virtual ~SDL2FontTTF();

	public:
		int32_t Create(const char *FontFile, size_t FontSize);
		void Destroy();

	public:
		__forceinline _TTF_Font * GetSDLFont() const
		{
			return TTFFont;
		}
	};
}
