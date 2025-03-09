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
	activeScene.init();
}


void Renderer::update()
{
	window.update();
	activeScene.update();
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