#include "glData.h"

VAO::VAO(std::vector <float>& vertices)
{
	this->vertices = vertices;
	glGenVertexArrays(1, &VAOid);
	glBindVertexArray(VAOid);


	glGenBuffers(1, &VBOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void VAO::bind()
{
	glBindVertexArray(VAOid);
}