#pragma once
#include "../rendererEssentials.h"

//handles transfromations of a model
class Transformer
{
private:
	glm::vec3 pos = { 0.0, 0.0, 0.0 };
	float rotation = { 0 };
	glm::vec3 rotationAxis = { 0, 0, 1 };
	glm::vec3 dialation = { 1.0, 1.0, 1.0 };
	glm::mat4 modelMat;

public:

	Transformer();


	glm::mat4 getModelMat();

};