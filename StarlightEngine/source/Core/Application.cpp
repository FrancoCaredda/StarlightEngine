#include "Application.h"

#include "Core/Renderer/Renderer.h"

namespace Starlight
{
	Application Application::s_Instance;

	bool Application::Init() noexcept
	{
		s_Instance.m_Inited = glfwInit();

		return s_Instance.m_Inited;
	}

	void Application::SetCurrentContext(AWindow* context)
	{
		s_Instance.m_CurrentContext = context;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwMakeContextCurrent(s_Instance.m_CurrentContext->m_Context);
	}

	void Application::Start()
	{
		SL_STD_EXCEPTION(s_Instance.m_CurrentContext == nullptr, "No context is seted!");
		s_Instance.m_CurrentContext->Start();
	}

	void Application::Update()
	{
		SL_STD_EXCEPTION(s_Instance.m_CurrentContext == nullptr, "No context is seted!");

		GLFWwindow* context = s_Instance.m_CurrentContext->m_Context;

		float deltaTime = 0;
		float previousTime = 0;

		while (!glfwWindowShouldClose(context))
		{
			Renderer::Enable(DEPTH_TEST);
			Renderer::Enable(STENCIL_TEST);

			Renderer::Clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT | STENCIL_BUFFER_BIT);

			deltaTime = static_cast<float>(glfwGetTime()) - previousTime;
			previousTime += deltaTime;
	
			s_Instance.m_CurrentContext->Update(deltaTime);

			Renderer::DrawFrame();

			glfwSwapBuffers(context);
			glfwPollEvents();
		}
	}
	
	void Application::Shutdown() noexcept
	{
		if (s_Instance.m_Inited)
		{
			glfwTerminate();
		}
	}
}