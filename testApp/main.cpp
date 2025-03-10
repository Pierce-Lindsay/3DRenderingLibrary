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
	Transformer* t = new Transformer(glm::vec3(3, 1, -3), glm::vec3(2, 2, 2), 45, glm::vec3(0, 0, 1));
	Model* m = new Model(ShapeType::SQUARE, t);

	Transformer* t2 = new Transformer(glm::vec3(0.5, -0.5, -1), glm::vec3(2, 2, 2), 0, glm::vec3(1, 0, 0));
	Model* m2 = new Model(ShapeType::TRIANGULAR_PYRAMID, t2);
	

	renderer->addModelToActiveScene(m);
	renderer->addModelToActiveScene(m2);

	
	auto start = std::chrono::steady_clock::now();
	
	//render loop
	while (renderer->active())
	{
		t2->rotate(0.2, glm::vec3(1, 0,0));
		t->move(glm::vec3(-0.005, 0, 0));
		t->rotate(0.1, glm::vec3(0, 0, 1));
		renderer->update();

		

		//just for convenience to check efficiency
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = now - start;
		elapsedTime = elapsed.count();
		

		//std::cout << "elapsedTime: " << elapsedTime << '\n';
		//if(elapsedTime >= 30)
		//	std::cout << "Average Framerate: " << totalFrames/elapsedTime << '\n';

		totalFrames++;
	}

	renderer->terminate();
	return 0;

}