#include "material.h"

//expecting shortented name (shader.shader) for example
Material::Material(std::string shaderName) : shaderName{shaderName}
{
	shad::initShaderIfNotFound(shaderName);
	program = shad::getProgram(shaderName);
}

GLuint Material::getProgram()
{
	return program;
}