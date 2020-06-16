/*
	Filename:		GLFWApplication.cpp
	Description:	GLFW application realization
	Author:			Valentin Karyagin
*/

#include "GLFWApplication.h"

// Third party
#define GLFW_EXPOSE_NATIVE_WIN32

#include "glfw3.h"
#include "glfw3native.h"

// Other engine components
#include "Renderer.h"

namespace Radiant
{
	class RADIANT_API GLFWInitializer
	{
		DECLARE_BASECLASS(GLFWInitializer)

	public:
		__forceinline static void OnError(int32_t Code, const char *Description)
		{
			printf("GLFW error %d: %s\n", Code, Description);
		}

	private:
		GLFWInitializer()
		{
			ASSERT(glfwInit() == GLFW_TRUE);
			glfwSetErrorCallback(GLFWInitializer::OnError);
		}

	public:
		virtual ~GLFWInitializer()
		{
			glfwTerminate();
		}
	};

	extern RADIANT_API GLFWInitializer *GGLFWInitializer = GLFWInitializer::GetInstance();
}

namespace Radiant
{
	GLFWApplication::GLFWApplication()
		: Window(nullptr)
		, Cursor(nullptr)
	{}

	GLFWApplication::~GLFWApplication() {}

	int32_t GLFWApplication::Init()
	{
		Window = glfwCreateWindow(1280, 720, "Radiant", nullptr, nullptr);
		ASSERT(Window);
		if (!Window) return 1;
		glfwMakeContextCurrent(Window);
		glfwSetFramebufferSizeCallback(Window, GLFWApplication::OnSetFrameBufferSize);

		Cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		ASSERT(Cursor);
		if (!Cursor) return 2;
		glfwSetCursor(Window, Cursor);

		return 0;
	}

	void GLFWApplication::Terminate()
	{
		glfwDestroyCursor(Cursor);
		Cursor = nullptr;

		glfwDestroyWindow(Window);
		Window = nullptr;
	}

	void GLFWApplication::Tick(float DeltaTime)
	{
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	void GLFWApplication::GetWindowSize(uint32_t *OutWidth, uint32_t *OutHeight) const
	{
		glfwGetWindowSize(Window, reinterpret_cast<int *>(OutWidth), reinterpret_cast<int *>(OutHeight));
	}

	float GLFWApplication::GetWindowAspectRatio() const
	{
		int32_t Width = 0, Height = 0;
		glfwGetWindowSize(Window, static_cast<int *>(&Width), static_cast<int *>(&Height));
		return static_cast<float>(Width) / static_cast<float>(Height);
	}

	void GLFWApplication::SetWindowSize(uint32_t Width, uint32_t Height) const
	{
		glfwSetWindowSize(Window, Width, Height);
	}

	HWND GLFWApplication::GetWin32Handler() const
	{
		return glfwGetWin32Window(Window);
	}

	void GLFWApplication::OnSetFrameBufferSize(GLFWwindow *Window, int32_t Width, int32_t Height)
	{
		GRenderer->SetViewport(0, 0, Width, Height);
	}
}
