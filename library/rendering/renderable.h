#pragma once
#include "../rendererEssentials.h"
#include "shader.h"
#include "glData.h"

class Renderable 
{
	VAO vao;
public:
	Renderable(std::vector <float>& vertices);

	void draw(glm::mat4 modelMat);
};