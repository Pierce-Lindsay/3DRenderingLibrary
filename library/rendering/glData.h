#pragma once
#include "../rendererEssentials.h"
#include <vector>
#include <iostream>

class VAO
{

private:

	GLuint VAOid;
	GLuint VBOid;
	GLuint EBOid;
	GLuint instanceVBOid;

	std::vector <float> vertices;
	std::vector <unsigned int> indicies;
	std::vector <glm::mat4> instanceModels;
	bool hasEBO = false;

	bool isInstanced = false;

	void buildEBO();
	void buildVBO();
	void buildAttributes();


public:
	
	VAO(std::vector <float>& vertices, std::vector <unsigned int>& indicies);
	VAO(std::vector <float>& vertices);
	void bind();
	void unbind();

	size_t getVerticesSize();
	bool isUsingEBO();
	size_t getIndiciesSize();

	const std::vector <float>& getVertices();

	const std::vector <unsigned int>& getIndicies();

	//requires significent restructuring
	void setupForInstancing(std::vector <glm::mat4>& instModels);

	size_t getInstancesAmount();
	//add way to clean up and delete buffers
};