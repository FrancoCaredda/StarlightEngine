#ifndef INPUT_H
#define INPUT_H

#include "defines.h"
#include "AWindow.h"

#include "glm/glm.hpp"

namespace Starlight
{
	class STARLIGHT_API Input
	{
	public:
		Input(AWindow* context);

		bool GetKeyPressed(int key) noexcept;
		bool GetKeyUp(int key) noexcept;

		bool GetMouseButtonDown(int key) noexcept;
		bool GetMouseButtonUp(int key) noexcept;

		void DisableCursor() noexcept;
		void EnableCursor() noexcept;

		glm::vec2 GetMousePosition() noexcept;
	private:
		GLFWwindow* m_Context;
	};
}
#endif // !INPUT_H

