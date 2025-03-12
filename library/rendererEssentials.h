#pragma once
#include "dependencies/include/Gladstuff/glad/glad.h"
#include "dependencies/include/GLFW/glfw3.h"
#include "dependencies/include/STB/stb_image.h"
#include "dependencies/include/glm/glm.hpp"
#include "dependencies/include/glm/gtc/matrix_transform.hpp"
#include "dependencies/include/glm/gtc/type_ptr.hpp"

//kinda like a singleton but not a class, forced to only be 1 instance of vars cause only in cpp file
namespace ren
{
	const glm::vec4 BLACK = { 0.0, 0.0, 0.0, 1.0 };
	const glm::vec4 WHITE = { 1.0, 1.0, 1.0, 1.0 };
	const glm::vec4 RED = { 1.0, 0.0, 0.0, 1.0 };
	const glm::vec4 BLUE = { 0.0, 0.0, 1.0, 1.0 };
	const glm::vec4 GREEN = { 0.0, 0.0, 1.0, 1.0 };

	//also has important globals

	//sets program as current program in use
	void setActiveProgram(GLuint program);

	void setActiveCamera(glm::mat4 cam);

	void setActiveProjection(glm::mat4 proj);

	glm::mat4 getActiveCamera();

	glm::mat4 getActiveProjection();

	GLuint getActiveProgram();

}