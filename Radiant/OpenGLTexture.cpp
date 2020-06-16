/*
	Filename:		OpenGLTexture.h
	Description:	OpenGL texture class realization
	Author:			Valentin Karyagin
*/

#include "OpenGLTexture.h"

#include "SDL.h"
#include <gl/GL.h>

#include "Commons.h"

namespace Radiant
{
	OpenGLTexture::OpenGLTexture()
		: Handle(0)
	{
		glGenTextures(1, &Handle);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &Handle);
	}

	int32_t OpenGLTexture::Create(SDL2Surface *FromSurface)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FromSurface->GetWidth(), FromSurface->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, FromSurface->GetData());
		return 0;
	}

	void OpenGLTexture::Destroy()
	{
		glDeleteTextures(1, &Handle);
		glGenTextures(1, &Handle);
	}
}
