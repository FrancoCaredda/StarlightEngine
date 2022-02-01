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

	virtual ~MainWindow();
private:
	Starlight::IVertexArray* m_VAO;
	Starlight::IVertexBuffer* m_VBO;
	Starlight::IIndexBuffer* m_IBO;

	Starlight::IShaderProgram* m_Program;
	Starlight::Camera m_Camera;

	bool m_Draw = false;
};


#endif // !MAIN_WINDOW_H
