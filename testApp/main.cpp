#include "../library/renderer.h"


int main()
{
	//initializes everything first time instance is grabed from anywhere
	Renderer* renderer = Renderer::GetInstance();


	std::vector <float> vertices = {
		0.0, 0.5, 0.0, 1.0,
		0.5, -0.5, 0.0, 1.0,
		-0.5, -0.5, 0.0, 1.0 };

	Model* m = new Model(vertices);
	renderer->addModelToActiveScene(m);

	//render loop
	while (renderer->active())
	{
		renderer->update();
	}

	delete(m);
	m = NULL;
	renderer->terminate();
	return 0;

}