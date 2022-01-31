#include "AWindow.h"

namespace Starlight
{
	AWindow::AWindow(const std::string& title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
		m_Context = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		SL_STD_EXCEPTION(!m_Context, "Context isn\'t created!");
	}
	
	void AWindow::SetTitle(const std::string& title) noexcept
	{
		m_Title = title;
		glfwSetWindowTitle(m_Context, m_Title.c_str());
	}
	
	void AWindow::SetWidth(int width) noexcept
	{
		m_Width = width;
		glfwSetWindowSize(m_Context, m_Width, m_Height);
	}

	void AWindow::SetHeight(int height) noexcept
	{
		m_Height = height;
		glfwSetWindowSize(m_Context, m_Width, m_Height);
	}
	
	AWindow::~AWindow()
	{
		glfwDestroyWindow(m_Context);
	}
}