#pragma once 
#include "../rendererEssentials.h"
#include "model.h"
#include "../rendering/instance.h"

//window needs to be initialized first!!!


//to be safe with pointers and heap allocated objects, the only places we keep relativley permanent pointers to objs are here
//and within the respective classes instances and models, if we delete from here, and make sure any version anywhere else
//that may be accessed is set to NULL, we're good
class Scene
{
private:
	glm::vec4 clearColor = ren::BLACK;

	void updateClearColor();

	std::vector <Model*> models;
	std::vector <Instance*> instances;

	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	double lastAspectRatio;

public:

	void init(double aspectRatio);
	void update(double aspectRatio);
	void setClearColor(glm::vec4 color);
	void draw();

	void addModel(Model* model);
	void addInstance(Instance* instance);

	void updateProjection(double aspectRatio);
};