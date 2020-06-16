/*
	Filename:		OpenGLRenderer.h
	Description:	Renderer class that implemented by OpenGL library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"
#include "VRStereo.h"
#include "Math.h"

namespace Radiant
{
	struct OpenGLVRContext;
}

namespace Radiant
{
	class RADIANT_API OpenGLRenderer
	{
		DECLARE_BASECLASS(OpenGLRenderer)

	protected:
		OpenGLVRContext	*VRContext;

	protected:
		OpenGLRenderer();

	public:
		virtual ~OpenGLRenderer();

	public:
		int32_t Init();
		void Terminate();

	public:
		int32_t InitVRContext();
		void TerminateVRContext();

	private:
		int32_t InitContext(EVRStereoType Eye);
		void TerminateContext(EVRStereoType Eye);

	public:
		void Tick(float DeltaTime = 0.0f);

	public:
		void SetViewport(int32_t X, int32_t Y, int32_t Width, int32_t Height);

	private:
		void DrawVR(EVRStereoType Eye) const;
		void DrawViewport() const;
		void DrawDebugMessages(const Matrix &Offset = Matrix::Identity) const;
		void DrawDrawInfo(const Matrix &Offset = Matrix::Identity) const;
	};
}
