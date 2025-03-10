#include "scene.h"


//ensures that glfw and glad are defined
void Scene::init(double aspectRatio)
{
	updateClearColor();
	cameraMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	updateProjection(aspectRatio);
	ren::setActiveCamera(cameraMatrix);
	
}

void Scene::update(double aspectRatio)
{
	if (aspectRatio != lastAspectRatio)
		updateProjection(aspectRatio);	
		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::setClearColor(glm::vec4 color)
{
	clearColor = color;
	updateClearColor();
}

void Scene::updateClearColor()
{
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	glEnable(GL_DEPTH_TEST);
}

void Scene::draw()
{
	for (int i = 0; i < models.size(); i++)
	{
		models[i]->draw();
	}

	for (int i = 0; i < instances.size(); i++)
	{
		instances[i]->drawInstances();
	}
}


void Scene::addModel(Model* model)
{
	models.push_back(model);
}

void Scene::addInstance(Instance* instance)
{
	instances.push_back(instance);
}

void Scene::updateProjection(double aspectRatio)
{
	lastAspectRatio = aspectRatio;
	projectionMatrix = glm::perspective(glm::radians(120.0), lastAspectRatio, 0.1, 50.0);
	ren::setActiveProjection(projectionMatrix);
}