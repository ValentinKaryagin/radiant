#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS

#include "OpenGLRenderer.h"
#include "OpenGLTexture.h"

namespace Radiant
{
	typedef OpenGLRenderer	Renderer;
	typedef OpenGLTexture	Texture;
}

#endif

namespace Radiant
{
	extern RADIANT_API Renderer *GRenderer;
}
