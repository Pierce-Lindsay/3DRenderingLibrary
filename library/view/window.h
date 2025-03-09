#pragma once
#include "../rendererEssentials.h"
#include <iostream>
#include "scene.h"



class Window {

private:

	GLFWwindow* window = NULL;

public:
	void init();
	bool isOpen();
	void update();
	void terminate();
	GLFWwindow* getWindow();
};
