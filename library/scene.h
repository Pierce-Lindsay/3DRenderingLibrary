#pragma once 
#include "rendererEssentials.h"

//window needs to be initialized first!!!
class Scene
{
private:
	glm::vec4 clearColor = BLACK;

	void updateClearColor();


public:

	void initScene();
	void update();
	void setClearColor(glm::vec4 color);
};