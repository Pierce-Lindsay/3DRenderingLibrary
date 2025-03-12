#include "material.h"

//expecting shortented name (shader.shader) for example
Material::Material(std::string shaderName, std::string textureName, glm::vec4 color) : shaderName{shaderName}, color{color}, 
textureName{textureName}
{
	shad::initShaderAndCheckIfExists(shaderName); 
	program = shad::getProgram(shaderName);

	if (textureName != "none")
	{
		Texture::addTextureIfNotExists(textureName);
		texture = Texture::getTexture(textureName);
	}

}

GLuint Material::getProgram()
{
	return program;
}

bool Material::equals(Material* m)
{
	if (m->program == program && m->shaderName == shaderName && m->color == color)
		return true;
	return false;
}

Material Material::deepCopy()
{
	Material newMat(*this);
	return newMat;
}


glm::vec4 Material::getColor()
{
	return color;
}
void Material::setColor(glm::vec4 c)
{
	color = c;
}

bool Material::isTextured()
{
	if (texture == NULL)
		return false;
	else
		return true;
}

Texture* Material::getTexture()
{
	return texture;
}