#pragma once
#include "rendererEssentials.h"
#include "shader.h"
#include <string>


class Material 
{
	private:
	//what shader does this object use
	std::string shaderName;
	GLuint program;

public:

	Material(std::string shaderName);

	GLuint getProgram();

	//lazy more java style
	bool equals(Material* m);

	Material deepCopy();
};