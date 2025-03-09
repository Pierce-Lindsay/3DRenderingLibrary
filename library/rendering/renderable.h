#pragma once
#include "../rendererEssentials.h"
#include "glData.h"
#include "material.h"

class Renderable 
{
	VAO vao;
	Material* material;
public:
	Renderable(std::vector <float>& vertices, Material* material);
	~Renderable();

	void draw(glm::mat4 modelMat);
};