#pragma once 
#include "../rendererEssentials.h"
#include "model.h"

//window needs to be initialized first!!!
class Scene
{
private:
	glm::vec4 clearColor = ren::BLACK;

	void updateClearColor();

	std::vector <Model*> models;

	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	double lastAspectRatio;

public:

	void init(double aspectRatio);
	void update(double aspectRatio);
	void setClearColor(glm::vec4 color);
	void draw();

	void addModel(Model* model);

	void updateProjection(double aspectRatio);
};