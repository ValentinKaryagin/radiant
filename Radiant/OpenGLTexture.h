/*
	Filename:		OpenGLTexture.h
	Description:	Texture class that implemented by OpenGL library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

namespace Radiant
{
	class SDL2Surface;

	class RADIANT_API OpenGLTexture
	{
		DECLARE_BASECLASS(OpenGLTexture)

	private:
		unsigned int Handle;

	public:
		OpenGLTexture();
		virtual ~OpenGLTexture();

	public:
		__forceinline unsigned int GetOpenGLTexture() const
		{
			return Handle;
		}

	public:
		int32_t Create(SDL2Surface *FromSurface);
		void Destroy();
	};
}
