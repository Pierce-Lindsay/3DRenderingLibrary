#include "renderer.h"


Renderer* Renderer::instance{ nullptr };
std::mutex Renderer::mutex;

/**
 * The first time we call GetInstance we will lock the storage location
 *      and then we make sure again that the variable is null and then we
 *      set the value.
 */
Renderer* Renderer::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex);
	if (instance == nullptr)
	{
		instance = new Renderer;
		instance->init();
	}
	return instance;
}



//initialize dependencies(window, opengl)
void Renderer::init()
{
	window.init();
	//default scene, make sure things init before calling it
	activeScene = new Scene;
	activeScene->init(window.getAspectRatio());
}


void Renderer::update()
{
	activeScene->update(window.getAspectRatio());

	activeScene->draw();

	window.update();
}
//check if renderer is active
bool Renderer::active()
{
	return window.isOpen();
}
//free memory and terminate renderer
void Renderer::terminate()
{
	window.terminate();
}

void Renderer::setActiveScene(Scene* scene)
{
	//this could be memory unsafe, what happens to the memory where activeScene is?
	delete(activeScene);
	activeScene = scene;
}

void Renderer::addModelToActiveScene(Model* model)
{
	activeScene->addModel(model);
}

