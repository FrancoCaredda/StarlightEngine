#include "MainWindow.h"

#include "glm/glm.hpp"

#include <iostream>

using namespace Starlight;

void MainWindow::Start()
{
	m_Input = new Input(this);
	m_Input->DisableCursor();

	Renderer::SetMainCamera(&m_Camera);
	Renderer::SetProjection(glm::perspective(glm::radians(45.0f), (float)m_Width / (float)m_Height, 0.1f, 1000.0f));

	std::vector<float> data = {
		-0.5f, -0.5f, 1.0f,		1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 1.0f,		0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 1.0f,		0.0f, 0.0f, 1.0f
	};

	std::vector<uint32_t> indecies = { 0, 1, 2, 2, 1, 3 };

	m_VBO = CreateVertexBuffer();

	m_VBO->Allocate(data.size() * sizeof(float));
	m_VBO->Write(data.data(), data.size() * sizeof(float), 0);
	m_VBO->Bind();

	m_IBO = CreateIndexBuffer();
	m_IBO->Allocate(indecies.size() * sizeof(uint32_t));
	m_IBO->Write(indecies, indecies.size() * sizeof(uint32_t), 0);
	m_IBO->Bind();

	m_VAO = CreateVertexArray();
	m_VAO->SetVertexLayout({
		{0, {3, 6 * sizeof(float), 0}},
		{1, {3, 6 * sizeof(float), 3 * sizeof(float)}}
	});
	m_VAO->AttachVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);
	m_VAO->Bind();

	ShaderLibrary::CreateShaderProgram("object", "Shaders/object.vert.glsl", "Shaders/object.frag.glsl");
	m_Program = ShaderLibrary::GetShaderProgram("object");

	m_Program->Bind();

	glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 3.0f, -5.0f));
	m_Program->SetUniformMat4f("u_Model", model);
}

void MainWindow::Update(float deltaTime)
{
	ProcessInput(deltaTime);
	m_PreviousMousePosition = m_Input->GetMousePosition();
	Renderer::DrawIndecies(m_VAO, m_IBO, m_Program);
}

void MainWindow::ProcessInput(float deltaTime) noexcept
{
	float x = 0, y = 0, z = 0;

	float sensetivity = 0.05;
	float movementSpeed = 5.0f;

	glm::vec2 mousePosition = m_Input->GetMousePosition();
	glm::vec2 deltaPosition = mousePosition - m_PreviousMousePosition;

	deltaPosition *= sensetivity;

	m_Pitch += deltaPosition.y;
	m_Yaw += -deltaPosition.x;

	if (m_Pitch > 90.0f)
		m_Pitch = 90.0f;
	else if (m_Pitch < -90.0f)
		m_Pitch = -90.0f;

	x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch)) * deltaTime;
	y = glm::sin(glm::radians(m_Pitch)) * deltaTime;
	z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch)) * deltaTime;

	glm::vec3 direction = { x, y, z };

	glm::vec3 position = m_Camera.GetPosition();

	if (m_Input->GetKeyPressed(GLFW_KEY_W))
		position += m_Camera.GetDirection() * movementSpeed * deltaTime;
	if (m_Input->GetKeyPressed(GLFW_KEY_S))
		position -= m_Camera.GetDirection() * movementSpeed * deltaTime;
	if (m_Input->GetKeyPressed(GLFW_KEY_A))
		position += glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) * movementSpeed * deltaTime;
	if (m_Input->GetKeyPressed(GLFW_KEY_D))
		position -= glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) * movementSpeed * deltaTime;

	m_Camera.SetPosition(position);
	m_Camera.SetDirection(direction);
}

MainWindow::~MainWindow()
{
	delete m_IBO;
	delete m_VAO;
	delete m_VBO;
}
