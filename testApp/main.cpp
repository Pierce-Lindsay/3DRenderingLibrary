#include "../library/renderer.h"
#include "../library/math/shape.h"


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

	Model* m = new Model(ShapeType::SQUARE);
	renderer->addModelToActiveScene(m);

	//Model* m2 = new Model(ShapeType::TRIANGLE);
	//renderer->addModelToActiveScene(m2);

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