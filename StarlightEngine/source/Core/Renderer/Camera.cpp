#include "Camera.h"

namespace Starlight
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& direction)
		: m_Position(position), m_Direction(glm::normalize(direction))
	{
		glm::vec3 right = glm::cross(m_Direction, glm::vec3(0.0f, 1.0f, 0.0f));
		m_Up = glm::cross(m_Direction, right);

		m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
	}

	void Camera::SetPosition(const glm::vec3& position) noexcept
	{
		m_Position = position;

		glm::vec3 right = glm::cross(m_Direction, glm::vec3(0.0f, 1.0f, 0.0f));
		m_Up = glm::cross(m_Direction, right);

		m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
	}
	
	void Camera::SetDirection(const glm::vec3& direction) noexcept
	{
		m_Direction = glm::normalize(direction);

		glm::vec3 right = glm::cross(m_Direction, glm::vec3(0.0f, 1.0f, 0.0f));
		m_Up = glm::cross(m_Direction, right);

		m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
	}
}
