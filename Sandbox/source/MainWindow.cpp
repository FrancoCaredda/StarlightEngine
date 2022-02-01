#include "MainWindow.h"

#include <iostream>

using namespace Starlight;

void MainWindow::Start()
{
	std::vector<float> data = {
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f
	};

	std::vector<uint32_t> indecies = { 0, 1, 2 };

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

	try
	{
		m_ShaderProgram = CreateProgram("Shaders/object.vert.glsl", "Shaders/object.frag.glsl");
		m_ShaderProgram->Link();
		m_ShaderProgram->Bind();
		m_Draw = true;
	}
	catch (std::exception& e)
	{
		SL_ERROR(e.what());
		m_Draw = false;
	}
}

void MainWindow::Update(float deltaTime)
{
	if (m_Draw)
		Renderer::DrawIndecies(m_VAO, m_IBO, m_ShaderProgram);
}

MainWindow::~MainWindow()
{
	delete m_IBO;
	delete m_VAO;
	delete m_VBO;
	delete m_ShaderProgram;
}
