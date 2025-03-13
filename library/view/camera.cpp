#include "camera.h"

Camera::Camera(const glm::vec3& eyePos, const glm::vec3& lookAtPos, const glm::vec3& up) 
	: eyePos{ eyePos }, lookAtPos{ lookAtPos }, up{up}
{
	transformer = new Transformer();
	setupLookAt();
}

Camera::~Camera()
{
	delete(transformer);
	transformer = NULL;
}


void Camera::setupLookAt()
{
	matrix = glm::lookAt(eyePos, lookAtPos, up);

	edited = false;
}


void Camera::setEye(const glm::vec3& eye)
{
	if (eye != eyePos)
	{
		eyePos = eye;
		edited = true;
	}
}
void Camera::setAt(const glm::vec3& at)
{
	if (at != lookAtPos)
	{
		lookAtPos = at;
		edited = true;
	}
}
void Camera::setUp(const glm::vec3& _up)
{
	if (_up != up)
	{
		up = _up;
		edited = true;
	}
		
}

glm::vec3 Camera::getEye()
{
	return eyePos;
}
glm::vec3 Camera::getAt()
{
	return lookAtPos;
}
glm::vec3 Camera::getUp()
{
	return up;
}


glm::mat4 Camera::getMatrix()
{
	if (edited)
		setupLookAt();

	return transformer->getModelMat() * matrix;
}