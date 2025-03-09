#pragma once 
#include "../rendererEssentials.h"
#include "model.h"

//window needs to be initialized first!!!
class Scene
{
private:
	glm::vec4 clearColor = BLACK;

	void updateClearColor();

	std::vector <Model*> models;

public:

	void init();
	void update();
	void setClearColor(glm::vec4 color);
	void draw();

	void addModel(Model* model);
};