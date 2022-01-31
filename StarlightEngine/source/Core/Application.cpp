#include "Application.h"

namespace Starlight
{
	Application Application::s_Instance;

	bool Application::Init() noexcept
	{
		return s_Instance.m_Inited = glfwInit();
	}

	void Application::SetCurrentContext(AWindow* context)
	{
		s_Instance.m_CurrentContext = context;
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
			glClear(GL_COLOR_BUFFER_BIT);

			deltaTime = static_cast<float>(glfwGetTime()) - previousTime;
			previousTime += deltaTime;
	
			s_Instance.m_CurrentContext->Update(deltaTime);

			glfwSwapBuffers(context);
			glfwPollEvents();
		}
	}
	
	void Application::Shutdown() noexcept
	{
		if (s_Instance.m_Inited)
			glfwTerminate();
	}
}