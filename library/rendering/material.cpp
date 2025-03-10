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

bool Material::equals(Material* m)
{
	if (m->program == program && m->shaderName == shaderName)
		return true;
	return false;
}

Material Material::deepCopy()
{
	Material newMat(*this);
	return newMat;
}