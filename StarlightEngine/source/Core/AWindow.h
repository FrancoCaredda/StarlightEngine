#ifndef AWINDOW_H
#define AWINDOW_H

#include "defines.h"

#include <string>

namespace Starlight
{
	class STARLIGHT_API AWindow
	{
	public:
		AWindow(const std::string& title, int width, int height);

		virtual void Start() = 0;
		virtual void Update(float deltaTime) = 0;

		void SetTitle(const std::string& title) noexcept;
		inline std::string GetTitle() const noexcept { return m_Title; }
	
		void SetWidth(int width) noexcept;
		inline int GetWidth() const noexcept { return m_Width; }

		void SetHeight(int height) noexcept;
		inline int GetHeight() const noexcept { return m_Height; }

		friend class Application;
		friend class Input;

		virtual ~AWindow();
	protected:
		std::string m_Title;
		int m_Width;
		int m_Height;
	private:
		GLFWwindow* m_Context;
	};
}


#endif // !AWINDOW_H

