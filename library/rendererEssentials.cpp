#include "rendererEssentials.h"


GLuint activeProgram = 1000000;

glm::mat4 activeCamera;

glm::mat4 activeProjection;

void ren::setActiveProgram(GLuint program)
{
	//only do something if this program is different
	if (activeProgram != program)
	{
		activeProgram = program;
		glUseProgram(activeProgram);
	}
	
}

void ren::setActiveCamera(glm::mat4 cam)
{
	activeCamera = cam;
}

void ren::setActiveProjection(glm::mat4 proj)
{
	activeProjection = proj;
}

glm::mat4 ren::getActiveCamera()
{
	return activeCamera;
}

glm::mat4 ren::getActiveProjection()
{
	return activeProjection;
}

GLuint ren::getActiveProgram()
{
	return activeProgram;
}
