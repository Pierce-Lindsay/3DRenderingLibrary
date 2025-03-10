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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void VAO::bind()
{
	glBindVertexArray(VAOid);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}


int VAO::getVerticesSize()
{
	return vertices.size();
}
bool VAO::isUsingEBO()
{
	return hasEBO;
}
int VAO::getIndiciesSize()
{
	return indicies.size();
}

const std::vector <float>& VAO::getVertices()
{
	return vertices;
}

const std::vector <unsigned int>& VAO::getIndicies()
{
	return indicies;
}