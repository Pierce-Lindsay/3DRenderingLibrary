#include "transformer.h"


Transformer::Transformer()
{
	initModelMat();
}

Transformer::Transformer(glm::vec3 pos, glm::vec3 scale, float rotation, glm::vec3 rotationAxis) : 
	pos{pos}, dialation{scale}, savedRotAmt{rotation}, savedRotAxis{rotationAxis}
{
	initModelMat();
}

void Transformer::initModelMat()
{
	//reverse order as required to work with glm

	//only multiply required matrixes, matrix multiplication is slow!!!!
	modelMat = glm::mat4(1.0f);

	if(glm::length2(pos) != 0.0)
		modelMat = glm::translate(modelMat, pos);

	if(rotation != 0.0)
		modelMat = glm::rotate(modelMat, glm::radians(rotation), rotationAxis);

	if(savedRotAmt != 0.0)
		modelMat = glm::rotate(modelMat, glm::radians(savedRotAmt), savedRotAxis);

	if(!(dialation.x == 1.0 && dialation.y == 1.0 && dialation.z == 1.0))
		modelMat = glm::scale(modelMat, dialation);
	//reset chnage check
	changedTransform = false;
		
}

glm::mat4 Transformer::getModelMat()
{
	//only recalculate is something changed

	if (changedTransform)
		initModelMat();


	return modelMat;
}



//this function is not used for updates per frame, its used sfor setting a fixed initial rotation on an axis
void Transformer::setSavedRot(float totalRotation, glm::vec3 axis)
{
	if(totalRotation != savedRotAmt || axis != savedRotAxis)
		changedTransform = true;

	savedRotAmt = totalRotation;
	savedRotAxis = axis;
}

void Transformer::rotate(float rot, glm::vec3 axis)
{
	if (rot != 0.0 || rotationAxis != axis)
	{
		changedTransform = true;
		rotation += rot;
		rotationAxis = axis;
	}
		
		
}


void Transformer::setRotate(float rotTotal, glm::vec3 axis)
{
	if (rotTotal != rotation || axis != rotationAxis)
	{
		changedTransform = true;
		rotation = rotTotal;
		rotationAxis = axis;
	}
	
}

void Transformer::setPos(glm::vec3 newPos)
{
	if (pos != newPos)
	{
		changedTransform = true;
		pos = newPos;
	}
	
}

void Transformer::move(glm::vec3 delta)
{
	//length 2 computes no sqrt but we dont care abt that
	if (glm::length2(delta) != 0)
	{
		changedTransform = true;
		pos += delta;
	}
	
}

void Transformer::setScale(glm::vec3 scale)
{
	if (dialation != scale)
	{
		changedTransform = true;
		dialation = scale;
	}

}

void Transformer::changeScaleByDelta(glm::vec3 delta)
{
	if (glm::length2(delta) != 0)
	{
		changedTransform = true;
		dialation += delta;
	}
}

void Transformer::changeScaleByFactor(glm::vec3 factor)
{
	//doing these condistionals is always faster than our matrix multiplications
	if (!(factor.x == 1.0 && factor.y == 1.0 && factor.z == 1.0))
	{
		changedTransform = true;
		dialation.x *= factor.x;
		dialation.y *= factor.y;
		dialation.z *= factor.z;
	}
}

void Transformer::changeScaleByUniform(float uniform)
{
	//doing these condistionals is always faster than our matrix multiplications
	if (uniform != 1.0)
	{
		changedTransform = true;
		dialation *= uniform;
	}
}

const glm::vec3& Transformer::getPos()
{
	return pos;
}

const glm::vec3& Transformer::getScale()
{
	return dialation;
}

const float Transformer::getRotation()
{
	return rotation;
}

const glm::vec3& Transformer::getRotationAxis()
{
	return rotationAxis;
}

const glm::vec3& Transformer::getInitialRotationAxis()
{
	return savedRotAxis;
}

const float Transformer::getInitialRotation()
{
	return savedRotAmt;
}


Transformer Transformer::deepCopy()
{
	Transformer newT(pos, dialation, savedRotAmt, savedRotAxis);
	newT.setRotate(rotation, rotationAxis);
	newT.modelMat = modelMat;
	//just in case
	newT.changedTransform = true;
	return newT;
}


//quick fast way to generate a matrix if you don't want the frills of an actuall transformer object
glm::mat4 Transformer::quickMakeModel(glm::vec3 pos, glm::vec3 scale, float rotation, glm::vec3 rotationAxis)
{
	glm::mat4 modelMat = glm::mat4(1.0f);

	
	if (glm::length2(pos) != 0.0)
		modelMat = glm::translate(modelMat, pos);

	if (rotation != 0.0)
		modelMat = glm::rotate(modelMat, glm::radians(rotation), rotationAxis);

	if (!(scale.x == 1.0 && scale.y == 1.0 && scale.z == 1.0))
		modelMat = glm::scale(modelMat,scale);

	//std::cout << "Mat vec3: " << modelMat[3].x << ", " << modelMat[3].y << ", " << modelMat[3].z << '\n';

	return modelMat;
}