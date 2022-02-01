#ifndef CAMERA_H
#define CAMERA_H

#include "defines.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Starlight
{
	class STARLIGHT_API Camera
	{
	public:
		Camera() = default;
		Camera(const glm::vec3& position, const glm::vec3& direction);

		void SetPosition(const glm::vec3& position) noexcept;
		void SetDirection(const glm::vec3& direction) noexcept;

		inline glm::vec3 GetPosition() const noexcept { return m_Position; }
		inline glm::vec3 GetDirection() const noexcept { return m_Direction; }
		inline glm::vec3 GetUp() const noexcept { return m_Up; }
		inline glm::mat4 GetView() const noexcept { return m_View; }

		~Camera() = default;
	private:
		glm::mat4 m_View = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::vec3 m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Position  = glm::vec3(0.0f, 0.0f,  0.0f);
		glm::vec3 m_Up		  = glm::vec3(0.0f, 1.0f,  0.0f);
	};
}

#endif // !CAMERA_H


