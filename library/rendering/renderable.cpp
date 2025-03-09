#include "renderable.h"


Renderable::Renderable(std::vector <float>& vertices) :
	vao(vertices)
{

}

void Renderable::draw(glm::mat4 modelMat)
{
	
	//will pass in materials program in teh future, if program is the same, do nothing
	glUseProgram(activeProgram);
	unsigned int modelLoc = glGetUniformLocation(activeProgram, "modelMatrix");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}