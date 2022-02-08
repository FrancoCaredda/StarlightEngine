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

	std::vector<Vertex> newData = {
				// POSITIONS		 // NORMALS			  // TEXTURE COORDS
		Vertex{{-0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
		Vertex{{-0.5f,  0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
		Vertex{{ 0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
		Vertex{{ 0.5f,  0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}}
	};

	if (ShaderLibrary::CreateShaderProgram("object", "Shaders/object.vert.glsl", "Shaders/object.frag.glsl") != true)
	{
		SL_ERROR("Something went wrong with creating object shader");
	}

	if (!ShaderLibrary::CreateShaderProgram("normals", "Shaders/normals.vert.glsl", "Shaders/normals.geom.glsl", "Shaders/normals.frag.glsl"))
	{
		SL_ERROR("Something went wrong with creating normals shader");
	}

	std::vector<uint32_t> indecies = { 0, 1, 2, 2, 1, 3 };

	m_Mesh = new Mesh();
	m_Mesh->SetVertecies(newData);
	m_Mesh->SetIndecies(indecies);
		
	m_Mesh->WriteData();

	m_Program = ShaderLibrary::GetShaderProgram("object");

	m_Program->Bind();

	m_Model = glm::rotate(glm::mat4(1.0f), glm::radians(-250.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Model = glm::translate(m_Model, glm::vec3(0.0f, 0.0f, 2.0f));
	m_Program->SetUniformMat4f("u_Model", m_Model);

	m_Material.Diffuse = CreateTexture2D(RGB, "Textures/brick.jpg");
	m_Material.Diffuse->SetActiveSlot(1);
	m_Material.Diffuse->Bind();

	m_Program->SetUniformi("u_Material.Diffuse", 1);
}

void MainWindow::Update(float deltaTime)
{
	ProcessInput(deltaTime);
	m_PreviousMousePosition = m_Input->GetMousePosition();

	m_Mesh->Bind();
	m_Program->Bind();

	m_Material.Diffuse->SetActiveSlot(1);
	m_Material.Diffuse->Bind();
	m_Program->SetUniformi("u_Material.Diffuse", 1);
	Renderer::DrawIndecies(m_Mesh->GetVertexArray(), m_Mesh->GetIndexBuffer(), m_Program);

	IShaderProgram* normals = ShaderLibrary::GetShaderProgram("normals");
	normals->Bind();
	normals->SetUniformf("u_Magnitude", 0.1f);
	normals->SetUniformMat4f("u_Model", m_Model);
	Renderer::DrawIndecies(m_Mesh->GetVertexArray(), m_Mesh->GetIndexBuffer(), normals);
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

	m_Pitch = glm::clamp(m_Pitch, -90.0f, 90.0f);
	
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
	delete m_Mesh;
}
