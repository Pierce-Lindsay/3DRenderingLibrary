#pragma once
#include "rendererEssentials.h"
#include "view/window.h"
#include <mutex>

//singleton, there should definitly obly ever be 1 renderer
class Renderer 
{
private:

    //force these to be private 
    Renderer() {}
    ~Renderer() {}

	static Renderer* instance;
	//used for multi-thread safety
	static std::mutex mutex;

	Window window;
	Scene activeScene;
public:
   
    // N0 cloning
    Renderer(Renderer& other) = delete;
	//no assigning
    void operator=(const Renderer&) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates renderer, initializes the renderer and stores it 
     * into the static field. On subsequent runs, it returns renderer
     */

    static Renderer* GetInstance();

	void init();
	void update();
	bool active();
	void terminate();
	
};