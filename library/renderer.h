#pragma once
#include "rendererEssentials.h"
#include "view/window.h"
#include "rendering/shader.h"
#include "rendering/batch.h"
#include "rendering/instance.h"
#include <mutex>

//singleton, there should definitly obly ever be 1 renderer
class Renderer 
{
private:

    //force these to be private 
    Renderer() {}
    ~Renderer() {}

    //private because is only called once by GetInstance the first time
   //inititilize 
    void init();

	static Renderer* instance;
	//used for multi-thread safety
	static std::mutex mutex;

	Window window;
	Scene* activeScene;

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

   

    
	//update renderer, lifeblood of our render loop
	void update();
    //checks if the renderer is still active
	bool active();
    //terminates renderer
	void terminate();

    void setActiveScene(Scene* scene);

    void addModelToActiveScene(Model* model);

    //adds an amount of instanced variations of provided model into the scene ewual to size of instanceTransforms
    Instance* addModelAsInstanceToActiveScene(Model* model, std::vector <Transformer*>& instanceTransformers);
  
};