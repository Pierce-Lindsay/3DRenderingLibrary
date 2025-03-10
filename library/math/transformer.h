#pragma once
#include "../rendererEssentials.h"
#include "../dependencies/include/glm/gtx/norm.hpp"

//handles transfromations of a model
class Transformer
{
private:
	glm::vec3 pos = { 0.0, 0.0, 0.0 };
	float rotation = { 0 };
	glm::vec3 rotationAxis = { 0, 0, 1 };
	glm::vec3 dialation = { 1.0, 1.0, 1.0 };
	glm::mat4 modelMat = glm::mat4(1.0f);
	glm::vec3 savedRotAxis = glm::vec3(0, 0, 1);
	float savedRotAmt = 0;

	bool changedTransform = false;

	void initModelMat();

public:

	Transformer();
	Transformer(glm::vec3 pos, glm::vec3 scale, float rotation, glm::vec3 rotationAxis);


	//this class is designed to be optimized, only ever recompute matrices if one of our values actually changes!!!!, 
	//and only do it once(per update), so at max once per frame
	void rotate(float rot, glm::vec3 axis);

	void setSavedRot(float rot, glm::vec3 axis);


	void setRotate(float rotTotal, glm::vec3 axis);

	void setPos(glm::vec3 newPos);

	void move(glm::vec3 delta);

	void setScale(glm::vec3 scale);

	void changeScaleByDelta(glm::vec3 delta);

	void changeScaleByFactor(glm::vec3 factor);

	void changeScaleByUniform(float uniform);

	const glm::vec3& getPos();

	const glm::vec3& getScale();

	const float getRotation();

	const glm::vec3& getRotationAxis();

	const glm::vec3& getInitialRotationAxis();

	const float getInitialRotation();

	glm::mat4 getModelMat();

};