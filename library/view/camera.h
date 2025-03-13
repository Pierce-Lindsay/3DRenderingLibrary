#pragma once
#include "rendererEssentials.h"
#include "math/transformer.h"

//note transformer is applied to the camera after look at


const glm::vec3 DEFAULT_CAM_EYE{0, 0, 10};
const glm::vec3 DEFAULT_CAM_LOOKAT{0, 0, 0};
const glm::vec3 DEFAULT_CAM_UP{0, 1, 0};


class Camera
{
private:

	glm::vec3 eyePos;
	glm::vec3 lookAtPos;
	glm::vec3 up;

	bool edited = true;

	void setupLookAt();

	glm::mat4 matrix;

public:
	//public for convenience
	Transformer* transformer;
	
	Camera(const glm::vec3& eyePos,const glm::vec3& lookAtPos, const glm::vec3& up);
	~Camera();

	void setEye(const glm::vec3& eye);
	void setAt(const glm::vec3& at);
	void setUp(const glm::vec3& up);

	glm::vec3 getEye();
	glm::vec3 getAt();
	glm::vec3 getUp();

	glm::mat4 getMatrix();
};