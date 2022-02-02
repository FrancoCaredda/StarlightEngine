#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Starlight.h"

class MainWindow : public Starlight::AWindow
{
public:
	MainWindow(const std::string& title, int width, int height)
		: Starlight::AWindow(title, width, height) { }

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	void ProcessInput(float deltaTime) noexcept;

	virtual ~MainWindow();
private:
	Starlight::IVertexArray* m_VAO;
	Starlight::IVertexBuffer* m_VBO;
	Starlight::IIndexBuffer* m_IBO;
	Starlight::Input* m_Input;

	Starlight::IShaderProgram* m_Program;
	Starlight::Camera m_Camera;

	float m_Yaw = 0.0f, m_Pitch = 0.0f;

	glm::vec2 m_PreviousMousePosition = glm::vec2(0.0, 0.0);

	bool m_Draw = false;
};


#endif // !MAIN_WINDOW_H
