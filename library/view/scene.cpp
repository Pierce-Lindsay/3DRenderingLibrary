#include "scene.h"


//ensures that glfw and glad are defined
void Scene::init(double aspectRatio)
{
	updateClearColor();
	activeCamera = new Camera(DEFAULT_CAM_EYE, DEFAULT_CAM_LOOKAT, DEFAULT_CAM_UP);
		//default camera values
	ren::setActiveCamera(activeCamera->getMatrix());
	perspectiveAspectRatio = aspectRatio;
	resetProjection();
}

Scene::~Scene()
{
	delete(activeCamera);
	activeCamera = NULL;

	models.clear();
	instances.clear();
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

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
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

void Scene::setFOV(double d)
{
	if (d != perspectiveFOV)
	{
		perspectiveFOV = d;
		projectionChanged = true;
	}
}

void Scene::setFar(double d)
{
	if (d != perspectiveFar)
	{
		perspectiveFar = d;
		projectionChanged = true;
	}
}

void Scene::setNear(double d)
{
	if (d != perspectiveNear)
	{
		perspectiveNear = d;
		projectionChanged = true;
	}
	
}


double Scene::getFOV()
{
	return perspectiveFOV;
}

double Scene::getFar()
{
	return perspectiveFar;
}

double Scene::getNear()
{
	return perspectiveNear;
}

void Scene::update(double currentWindowAspectRatio)
{
	if (currentWindowAspectRatio != perspectiveAspectRatio)
	{
		perspectiveAspectRatio = currentWindowAspectRatio;
		projectionChanged = true;
	}

	if (projectionChanged)
		resetProjection();

	//to be safe for now, just reassigned amera
	ren::setActiveCamera(activeCamera->getMatrix());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Scene::resetProjection()
{
	projectionMatrix = glm::perspective(glm::radians(perspectiveFOV), perspectiveAspectRatio, perspectiveNear, perspectiveFar);
	ren::setActiveProjection(projectionMatrix);

	projectionChanged = false;
}

Camera* Scene::getCamera()
{
	return activeCamera;
}