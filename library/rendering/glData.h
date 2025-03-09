#pragma once
#include "../rendererEssentials.h"
#include <vector>

class VAO
{

private:

	GLuint VAOid;
	GLuint VBOid;
	GLuint EBOid;

	std::vector <float> vertices;
	std::vector <unsigned int> indicies;
	bool hasEBO = false;

	void buildEBO();
	void buildVBO();
	void buildAttributes();


public:
	
	

	VAO(std::vector <float>& vertices, std::vector <unsigned int>& indicies);
	VAO(std::vector <float>& vertices);
	void bind();
	void unbind();

	int getVerticesSize();
	bool isUsingEBO();
	int getIndiciesSize();



};