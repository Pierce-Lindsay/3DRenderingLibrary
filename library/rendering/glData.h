#pragma once
#include "../rendererEssentials.h"
#include <vector>

class VAO
{
public:
	GLuint VAOid;
	GLuint VBOid;
	std::vector <float> vertices;

	VAO(std::vector <float>& vertices);
	void bind();
};