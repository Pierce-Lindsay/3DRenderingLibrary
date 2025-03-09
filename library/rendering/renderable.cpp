#include "renderable.h"

void bindUniformMat4(glm::mat4 matrix, std::string name)
{
	glUniformMatrix4fv(glGetUniformLocation(ren::getActiveProgram(),
		name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}


Renderable::Renderable(std::vector <float>& vertices, std::vector <unsigned int>& indicies, Material* material) :
	vao(vertices, indicies), material{material}
{

}

Renderable::Renderable(std::vector <float>& vertices, Material* material) :
	vao(vertices), material{ material }
{}

Renderable::~Renderable()
{
	delete(material);
	material = NULL;
}

void Renderable::draw(glm::mat4& modelMat)
{
	
	ren::setActiveProgram(material->getProgram());

	bindUniformMat4(modelMat, "modelMatrix");
	bindUniformMat4(ren::getActiveCamera(), "cameraMatrix");
	bindUniformMat4(ren::getActiveProjection(), "projMatrix");
	vao.bind();
	//draw type depends on whether the objects has an ebo
	if(vao.isUsingEBO())
		glDrawElements(GL_TRIANGLES, GLsizei(vao.getIndiciesSize()), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, GLsizei(vao.getVerticesSize()));

	vao.unbind();
}






