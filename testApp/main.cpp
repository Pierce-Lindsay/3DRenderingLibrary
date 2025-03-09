#include "../library/renderer.h"


int main()
{
	//initializes everything first time instance is grabed from anywhere
	Renderer* renderer = Renderer::GetInstance();


	std::vector <float> vertices = {
		0.0, 0.5, 0.0, 1.0,
		0.5, -0.5, 0.0, 1.0,
		-0.5, -0.5, 0.0, 1.0 };


	std::vector <float> vertices2 = {
		1.0, 0.5, 0.0, 1.0,
		0.5, -0.5, 0.0, 1.0,
		-0.5, -0.5, 0.0, 1.0 };

	Model* m = new Model(vertices);
	Model* m2 = new Model(vertices2);
	renderer->addModelToActiveScene(m);
	renderer->addModelToActiveScene(m2);

	//render loop
	while (renderer->active())
	{
		renderer->update();
	}

	delete(m);
	m = NULL;

	delete(m2);
	m2 = NULL;
	renderer->terminate();
	return 0;

}