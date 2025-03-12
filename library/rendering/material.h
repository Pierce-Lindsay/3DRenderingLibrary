#pragma once
#include "rendererEssentials.h"
#include "shader.h"
#include "texture.h"
#include <string>


class Material 
{
	private:
	//what shader does this object use
	std::string shaderName;
	GLuint program;

	glm::vec4 color;

	std::string textureName;
	Texture* texture = NULL;


public:

	Material(std::string shaderName, std::string textureName = "none", glm::vec4 color = ren::WHITE);

	GLuint getProgram();

	//lazy more java style
	bool equals(Material* m);

	Material deepCopy();

	glm::vec4 getColor();
	void setColor(glm::vec4 c);
	bool isTextured();
	Texture* getTexture();
};