#include "../library/window.h"



int main()
{
	//initializes everything 
	Window window;


	//render loop
	while (window.isOpen())
	{
		window.update();
	}

	window.terminate();
	return 0;

}