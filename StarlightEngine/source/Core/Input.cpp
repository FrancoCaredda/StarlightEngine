#include "Input.h"


namespace Starlight
{
	Input::Input(AWindow* context)
	{
		m_Context = context->m_Context;
	}
	
	bool Input::GetKeyPressed(int key) noexcept
	{
		int state = glfwGetKey(m_Context, key);

		if (state == GLFW_PRESS)
			return true;

		return false;
	}
	
	bool Input::GetKeyUp(int key) noexcept
	{
		int state = glfwGetKey(m_Context, key);

		if (state == GLFW_RELEASE)
			return true;

		return false;
	}
	
	bool Input::GetMouseButtonDown(int key) noexcept
	{
		int state = glfwGetMouseButton(m_Context, key);

		if (state == GLFW_PRESS)
			return true;

		return false;
	}
	
	bool Input::GetMouseButtonUp(int key) noexcept
	{
		int state = glfwGetMouseButton(m_Context, key);

		if (state == GLFW_RELEASE)
			return true;

		return false;
	}

	void Input::DisableCursor() noexcept
	{
		glfwSetInputMode(m_Context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Input::EnableCursor() noexcept
	{
		glfwSetInputMode(m_Context, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	
	glm::vec2 Input::GetMousePosition() noexcept
	{
		double x, y;
		glfwGetCursorPos(m_Context, &x, &y);
	
		return { (float)x, (float)y };
	}
}
