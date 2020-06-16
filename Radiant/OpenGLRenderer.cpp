/*
	Filename:		OpenGLRenderer.cpp
	Description:	OpenGL renderer class realization
	Author:			Valentin Karyagin
*/

#include "OpenGLRenderer.h"

// Third party
#include "glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

// Engine components
#include "Math.h"
#include "Application.h"
#include "Physics.h"
#include "VRSystem.h"

// Engine
#include "Engine.h"

namespace Radiant
{
	struct VREyeContext
	{
		GLuint DepthBuffer;
		GLuint RenderTexture;
		GLuint RenderFrameBuffer;
		GLuint ResolveTexture;
		GLuint ResolveFrameBuffer;
	};

	struct OpenGLVRContext
	{
		VREyeContext LeftEye, RightEye;
	};
}

namespace Radiant
{
	OpenGLRenderer::OpenGLRenderer()
		: VRContext(nullptr)
	{}

	OpenGLRenderer::~OpenGLRenderer() {}

	int32_t OpenGLRenderer::Init()
	{
		glewInit();

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		

		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);	

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glLineWidth(0.1f);

		return 0;
	}

	void OpenGLRenderer::Terminate()
	{
		
	}

	int32_t OpenGLRenderer::InitVRContext()
	{
		VRContext = new OpenGLVRContext{};
		return InitContext(EVRStereoType::EVRST_LeftEye) + InitContext(EVRStereoType::EVRST_RightEye);
	}

	void OpenGLRenderer::TerminateVRContext()
	{
		TerminateContext(EVRStereoType::EVRST_RightEye), TerminateContext(EVRStereoType::EVRST_LeftEye);
		delete VRContext;
	}

	int32_t OpenGLRenderer::InitContext(EVRStereoType Eye)
	{
		uint32_t Width, Height;
		GVRSystem->GetTargetSize(&Width, &Height);

		glGenFramebuffers(1, Eye == EVRStereoType::EVRST_LeftEye ? &VRContext->LeftEye.RenderFrameBuffer : &VRContext->RightEye.RenderFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.RenderFrameBuffer : VRContext->RightEye.RenderFrameBuffer);

		glGenRenderbuffers(1, Eye == EVRStereoType::EVRST_LeftEye ? &VRContext->LeftEye.DepthBuffer : &VRContext->RightEye.DepthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.DepthBuffer : VRContext->RightEye.DepthBuffer);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, Width, Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.DepthBuffer : VRContext->RightEye.DepthBuffer);

		glGenTextures(1, Eye == EVRStereoType::EVRST_LeftEye ? &VRContext->LeftEye.RenderTexture : &VRContext->RightEye.RenderTexture);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.RenderTexture : VRContext->RightEye.RenderTexture);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, Width, Height, true);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.RenderTexture : VRContext->RightEye.RenderTexture, 0);

		glGenFramebuffers(1, Eye == EVRStereoType::EVRST_LeftEye ? &VRContext->LeftEye.ResolveFrameBuffer : &VRContext->RightEye.ResolveFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.ResolveFrameBuffer : VRContext->RightEye.ResolveFrameBuffer);

		glGenTextures(1, Eye == EVRStereoType::EVRST_LeftEye ? &VRContext->LeftEye.ResolveTexture : &VRContext->RightEye.ResolveTexture);
		glBindTexture(GL_TEXTURE_2D, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.ResolveTexture : VRContext->RightEye.ResolveTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.ResolveTexture : VRContext->RightEye.ResolveTexture, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) return 1;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return 0;
	}

	void OpenGLRenderer::TerminateContext(EVRStereoType Eye)
	{
		// todo: delete handles that initialized in InitContext function
	}

	void OpenGLRenderer::Tick(float DeltaTime)
	{
		if (GEngine->IsDrawVR && GVRSystem->IsInited())
		{
			This::DrawVR(EVRStereoType::EVRST_LeftEye);
			This::DrawVR(EVRStereoType::EVRST_RightEye);
		}

		if (GEngine->IsDrawViewport)
		{
			This::DrawViewport();
		}
	}

	void OpenGLRenderer::SetViewport(int32_t X, int32_t Y, int32_t Width, int32_t Height)
	{
		glViewport(X, Y, Width, Height);
	}

	void OpenGLRenderer::DrawVR(EVRStereoType Eye) const
	{
		uint32_t Width, Height;
		GVRSystem->GetTargetSize(&Width, &Height);

		Matrix Projection, View, Model, MVP;		

		glBindFramebuffer(GL_FRAMEBUFFER, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.RenderFrameBuffer : VRContext->RightEye.RenderFrameBuffer);		

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glViewport(0, 0, Width, Height);

		Projection	= GVRSystem->GetStereoProjectionMatrix(Eye).GetTransposed();
		View		= GVRSystem->GetStereoViewMatrix(Eye).GetTransposed();
		Model		= GVRSystem->GetAbsoluteMatrix().GetTransposed();
		MVP			= (Projection * View * Model * GVRSystem->GetOffsetMatrix()).GetTransposed();

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)&MVP);

		glMatrixMode(GL_MODELVIEW);
		if (GEngine->IsDrawCollisions)		GPhysics->DrawCollisions();
		if (GEngine->IsDrawDebugMessages)	This::DrawDebugMessages();
		if (GEngine->IsDrawDrawInfo)		This::DrawDrawInfo();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.RenderFrameBuffer : VRContext->RightEye.RenderFrameBuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.ResolveFrameBuffer : VRContext->RightEye.ResolveFrameBuffer);

		glBlitFramebuffer(0, 0, Width, Height, 0, 0, Width, Height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		GVRSystem->Present(
			reinterpret_cast<void *>(static_cast<size_t>(Eye == EVRStereoType::EVRST_LeftEye ? VRContext->LeftEye.ResolveTexture : VRContext->RightEye.ResolveTexture)),
			Eye,
			EVRRenderTargetTextureType::EVRRTTT_OpenGL
		);

		glFlush();
		glFinish();
	}

	void OpenGLRenderer::DrawViewport() const
	{
		uint32_t Width, Height;
		GApplication->GetWindowSize(&Width, &Height);

		Matrix Projection, View, Model, MVP;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glViewport(0, 0, Width, Height);

		if (GEngine->IsDrawVR && GVRSystem->IsInited())
		{
			Projection	= GVRSystem->GetStereoProjectionMatrix(EVRStereoType::EVRST_LeftEye).GetTransposed();
			View		= GVRSystem->GetStereoViewMatrix(EVRStereoType::EVRST_LeftEye).GetTransposed();
			Model		= GVRSystem->GetAbsoluteMatrix().GetTransposed();
			MVP			= (Projection * View * Model * GVRSystem->GetOffsetMatrix()).GetTransposed();
		}
		else
		{
			Projection	= PerspectiveMatrix(Math::DegsToRads(GEngine->GetCurrentCameraFoV()), GEngine->GetViewportAspectRatio(), 0.001f, 1000.0f).GetTransposed();
			View		= LookAtMatrix(Vector3::Zero, Vector3::Forward).GetTransposed();
			Model		= Matrix::Identity.GetTransposed();
			MVP			= (Projection * View * Model).GetTransposed();
		}

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)&MVP);

		glMatrixMode(GL_MODELVIEW);
		if (GEngine->IsDrawCollisions)		GPhysics->DrawCollisions();
		if (GEngine->IsDrawDebugMessages)	This::DrawDebugMessages();
		if (GEngine->IsDrawDrawInfo)		This::DrawDrawInfo();

		glFlush();
		glFinish();
	}

	void OpenGLRenderer::DrawDebugMessages(const Matrix &Offset) const
	{
		uint32_t ViewportX, ViewportY;
		if (GEngine->IsDrawVR && GVRSystem->IsInited()) GVRSystem->GetTargetSize(&ViewportX, &ViewportY);
		else GEngine->GetViewportSize(&ViewportX, &ViewportY);

		Matrix Projection = OrthogonalMatrix(0.0f, static_cast<float>(ViewportX), static_cast<float>(ViewportY), 0.0f, 0.0f, 1.0f);
		Matrix MVP		  = Offset * Projection;

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)&MVP);

		glMatrixMode(GL_MODELVIEW);
		float CoordX, CoordY, CoordYOffsetStep = 10.0f;
		if (GEngine->IsDrawVR && GVRSystem->IsInited())
		{
			CoordX = 512.0f;
			CoordY = 640.0f;
		}
		else
		{
			CoordX = 10.0f;
			CoordY = 10.0f;
		}
		float CoordXOffset = CoordX, CoordYOffset = CoordY;

		glEnable(GL_TEXTURE_2D);

		for (auto &Item : GEngine->DebugMessages)
		{
			GLuint MessageTexture = 0;
			glGenTextures(1, &MessageTexture);
			glBindTexture(GL_TEXTURE_2D, MessageTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Item.MessageText.GetWidth(), Item.MessageText.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Item.MessageText.GetData());

			GLint W, H;
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &W);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &H);

			glBegin(GL_QUADS);
			glTexCoord2d(0, 0); glVertex2f(CoordXOffset,		CoordYOffset);
			glTexCoord2d(1, 0);	glVertex2f(CoordXOffset + W,	CoordYOffset);
			glTexCoord2d(1, 1);	glVertex2f(CoordXOffset + W,	CoordYOffset + H);
			glTexCoord2d(0, 1);	glVertex2f(CoordXOffset,		CoordYOffset + H);
			glEnd();

			glDeleteTextures(1, &MessageTexture);

			CoordYOffset = CoordYOffset + CoordYOffsetStep + H;
		}

		glDisable(GL_TEXTURE_2D);
	}

	void OpenGLRenderer::DrawDrawInfo(const Matrix &Offset) const
	{
		uint32_t ViewportX, ViewportY;
		if (GEngine->IsDrawVR && GVRSystem->IsInited()) GVRSystem->GetTargetSize(&ViewportX, &ViewportY);
		else GEngine->GetViewportSize(&ViewportX, &ViewportY);

		Matrix Projection	= OrthogonalMatrix(0.0f, static_cast<float>(ViewportX), static_cast<float>(ViewportY), 0.0f, 0.0f, 1.0f);
		Matrix MVP			= Offset * Projection;

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)&MVP);

		glMatrixMode(GL_MODELVIEW);

		float CoordX, CoordY;
		if (GEngine->IsDrawVR && GVRSystem->IsInited())
		{
			CoordX = 512.0f;
			CoordY = 640.0f;
		}
		else
		{
			CoordX = 10.0f;
			CoordY = 10.0f;
		}
		float CoordXOffset = CoordX, CoordYOffset = CoordY;

		const float DeltaTime	= GEngine->GetDeltaTime();
		const float FPS			= 1.0f / DeltaTime;
		tchar StringBuffer[32]{};
		tsprintf_s(StringBuffer, TXT("FT: %f FPS: %f"), DeltaTime, FPS);

		glEnable(GL_TEXTURE_2D);

		GLuint FPSTexture;
		glGenTextures(1, &FPSTexture);
		glBindTexture(GL_TEXTURE_2D, FPSTexture);

		Surface MessageText;
		MessageText.Create(&GEngine->DebugMessagesFont, StringBuffer, GEngine->DebugMessagesColor);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MessageText.GetWidth(), MessageText.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, MessageText.GetData());

		GLint W, H;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &W);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &H);

		CoordXOffset = ViewportX - CoordX - W;

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2f(CoordXOffset,		CoordYOffset);
		glTexCoord2d(1, 0);	glVertex2f(CoordXOffset + W,	CoordYOffset);
		glTexCoord2d(1, 1);	glVertex2f(CoordXOffset + W,	CoordYOffset + H);
		glTexCoord2d(0, 1);	glVertex2f(CoordXOffset,		CoordYOffset + H);
		glEnd();

		MessageText.Destroy();

		glDeleteTextures(1, &FPSTexture);

		glDisable(GL_TEXTURE_2D);
	}
}
