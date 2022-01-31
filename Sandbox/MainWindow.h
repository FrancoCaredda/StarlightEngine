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

	virtual ~MainWindow() { }
};


#endif // !MAIN_WINDOW_H
