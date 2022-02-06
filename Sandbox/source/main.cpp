#include "Starlight.h"

#include "MainWindow.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (!Starlight::Application::Init())
	{
		SL_FATAL("Application isn\'t initialized");
		return -1;
	}

	Starlight::AWindow* window = new MainWindow("Sandbox", 1200, 900);

	Starlight::Application::SetCurrentContext(window);

	if (!Starlight::Renderer::Init(OPENGL_API, 1200, 900))
	{
		SL_FATAL("Renderer isn\'t initialized");
		return -2;
	}

	Starlight::Application::Start();
	Starlight::Application::Update();

	delete window;
	window = nullptr;

	Starlight::Application::Shutdown();

	return 0;
}