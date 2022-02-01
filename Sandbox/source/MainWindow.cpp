#include "MainWindow.h"

#include <iostream>

using namespace Starlight;

void MainWindow::Start()
{
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
	Renderer::DrawIndecies(m_VAO, m_IBO, m_Program);
}

MainWindow::~MainWindow()
{
	delete m_IBO;
	delete m_VAO;
	delete m_VBO;
}
