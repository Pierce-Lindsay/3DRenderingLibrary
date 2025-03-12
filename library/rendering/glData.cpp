#include "glData.h"

VAO::VAO(std::vector <float>& vertices, std::vector <unsigned int>& indicies )
{
	hasEBO = true;
	this->vertices = vertices;
	this->indicies = indicies;

	//build proper items
	glGenVertexArrays(1, &VAOid);
	glBindVertexArray(VAOid);

	buildVBO();
	buildEBO();
	buildAttributes();

	//unbind VAO
	unbind();
}


VAO::VAO(std::vector <float>& vertices)
{
	hasEBO = false;
	this->vertices = vertices;

	//build proper items
	glGenVertexArrays(1, &VAOid);
	glBindVertexArray(VAOid);

	buildVBO();
	buildAttributes();
	//unbind VAO
	unbind();
}


void VAO::buildEBO()
{
	//EBO
	glGenBuffers(1, &EBOid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOid);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicies.size(), indicies.data(), GL_STATIC_DRAW);
}


void VAO::buildVBO()
{
	//VBO
	glGenBuffers(1, &VBOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
}
void VAO::buildAttributes()
{
	//ATTRIBS
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VAO::bind()
{
	glBindVertexArray(VAOid);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}


size_t VAO::getVerticesSize()
{
	return vertices.size();
}
bool VAO::isUsingEBO()
{
	return hasEBO;
}
size_t VAO::getIndiciesSize()
{
	return indicies.size();
}

size_t VAO::getInstancesAmount()
{
	return instanceModels.size();
}

const std::vector <float>& VAO::getVertices()
{
	return vertices;
}

const std::vector <unsigned int>& VAO::getIndicies()
{
	return indicies;
}

void VAO::setupForInstancing(std::vector <glm::mat4>& instModels)
{
	instanceModels = instModels;
	std::cout << "instModels count" << instanceModels.size() << '\n';
	isInstanced = true;
	//sloppy to start for clarity, will clean up later

	bind();
	//bind our vao and add an intantance VBO to it
	//VBO
	
	glGenBuffers(1, &instanceVBOid);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBOid);
	//first of all 
	//vectors are cotignuous
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instanceModels.size(), instanceModels.data(), GL_STATIC_DRAW);


	//add attribs to this buffer
	//we need for attributes cause max is vec4, and mat4 as 4 vec4s
	std::size_t sz = sizeof(glm::vec4);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sz, (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sz, (void*)(1 * sz));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sz, (void*)(2 * sz));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sz, (void*)(3 * sz));

	//says how to split the guys up
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	unbind();


}