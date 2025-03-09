#include "../library/renderer.h"



int main()
{
	//initializes everything first time instance is grabed from anywhere
	Renderer* renderer = Renderer::GetInstance();


	//render loop
	while (renderer->active())
	{
		renderer->update();
	}

	renderer->terminate();
	return 0;

}