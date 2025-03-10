#include "../library/renderer.h"
#include "../library/math/shape.h"
#include <chrono>

double elapsedTime = 0;
double totalFrames = 0;

int main()
{
	//initializes everything first time instance is grabed from anywhere
	Renderer* renderer = Renderer::GetInstance();

	//Note!!!, if delete something made here, there will be dangling pointers in renderer!!!!, 
	// call delete in renderer on model id# first!!!!
	std::vector <Transformer*> ts;

	Transformer* t = new Transformer(glm::vec3(0, 0, -1), glm::vec3(1, 1, 1), 0, glm::vec3(0, 0, 1));
	Model* m = new Model(ShapeType::CUBE, t);

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			for (int k = 0; k < 100; k++)
			{
				ts.push_back(new Transformer(glm::vec3(-50 + i , -50 + j , -k), glm::vec3(0.1, 0.1, 0.1), 0, glm::vec3(0, 1, 0)));
			}
		}

			
	}

	Instance* inst1 = renderer->addModelAsInstanceToActiveScene(m, ts);
	delete(m);
	m = NULL;
	t = NULL;

	//Model* m2 = new Model(ShapeType::CUBE, t2);

	//m->mergeHereWithSameMaterial(m2);
	//delete(m2);
	//m2 = NULL;

	//renderer->addModelToActiveScene(m);

	
	auto start = std::chrono::steady_clock::now();
	double lastTime = 0;
	double thisTime = 0;
	//render loop
	while (renderer->active())
	{
		//t2->rotate(0.2, glm::vec3(0, 1,0));
		//t->move(glm::vec3(-0.005, 0, 0));
		inst1->model->transformer->rotate(0.1, glm::vec3(0, 0.5, 1));
		renderer->update();

		

		//just for convenience to check efficiency
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = now - start;
		elapsedTime = elapsed.count();
		double diffTime = elapsedTime - lastTime;
		lastTime = elapsedTime;
		

		//std::cout << "elapsedTime: " << elapsedTime << '\n';
		if(elapsedTime >= 30)
			std::cout << "Framerate: " <<1.0/diffTime<< '\n';

		totalFrames++;
	}

	renderer->terminate();
	return 0;

}