#pragma once
#include "../rendererEssentials.h"
#include <iostream>
#include "scene.h"



class Window {

private:

	GLFWwindow* window = NULL;

	int height = 1080;
	int width = 1920;

public:
	void init();
	bool isOpen();
	void update();
	void terminate();
	GLFWwindow* getWindow();

	float getAspectRatio();
};
