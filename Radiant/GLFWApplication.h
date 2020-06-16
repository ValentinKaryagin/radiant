/*
	Filename:		GLFWApplication.h
	Description:	Application class that implemented by GLFW library
	Author:			Valentin Karyagin
*/

#pragma once

#include "Object.h"

struct GLFWwindow;
struct GLFWcursor;

namespace Radiant
{
	class RADIANT_API GLFWApplication
	{
		DECLARE_BASECLASS(GLFWApplication)

	protected:
		GLFWwindow	*Window;
		GLFWcursor	*Cursor;

	protected:
		GLFWApplication();

	public:
		virtual ~GLFWApplication();

	public:
		int32_t Init();
		void Terminate();

	public:
		void Tick(float DeltaTime = 0.0f);

	public:
		void GetWindowSize(uint32_t *OutWidth, uint32_t *OutHeight) const;
		float GetWindowAspectRatio() const;

	public:
		void SetWindowSize(uint32_t Width, uint32_t Height) const;

	public:
		HWND GetWin32Handler() const;

	public:		
		static void OnSetFrameBufferSize(GLFWwindow *Window, int32_t Width, int32_t Height);		
	};
}
