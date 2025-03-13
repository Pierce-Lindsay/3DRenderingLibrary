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
	std::vector <glm::mat4> ts;
	Material* mat = new Material("basicShaderTextured.shader", "stones_texture.jpg", ren::RED);
	Transformer* t = new Transformer(glm::vec3(0, 0, -1), glm::vec3(5, 5, 5), 0, glm::vec3(0, 0, 1));
	Model* m = new Model(ShapeType::CUBE, t, mat);

	/*
	
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			for (int k = 0; k < 100; k++)
			{
				ts.push_back(Transformer::quickMakeModel(glm::vec3(-50 + i , -50 + j , -50 + k), glm::vec3(0.1, 0.1, 0.1), 0, glm::vec3(0, 1, 0)));
			}
		}

			
	}
	*/
	
	//Instance* inst1 = renderer->addModelAsInstanceToActiveScene(m, ts);
	//delete(m);
	//m = NULL;
	//mat = NULL;
	//t = NULL;
	

	renderer->addModelToActiveScene(m);
	
	auto start = std::chrono::steady_clock::now();
	double lastTime = 0;
	double thisTime = 0;
	//render loop
	while (renderer->active())
	{
		//inst1->model->transformer->rotate(0.1, glm::vec3(0, 0.5, 1));
		//inst1->model->getBatch()->getMaterial()->setColor(glm::vec4(glm::cos(long double(totalFrames / 1000.0f))+0.1, glm::sin(-long double(totalFrames / 1000.0f)) +0.1, 0.1, 1.0f));
		//renderer->getActiveScene()->getCamera()->setAt(renderer->getActiveScene()->getCamera()->getAt() + glm::vec3(0.01, 0, 0));
		renderer->update();
		//t->rotate(0.1, glm::vec3(0.4, 1, 0));
		
		

		//just for convenience to check efficiency
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = now - start;
		elapsedTime = elapsed.count();
		double diffTime = elapsedTime - lastTime;
		lastTime = elapsedTime;
		

		//std::cout << "elapsedTime: " << elapsedTime << '\n';
		//if(elapsedTime >= 20)
		//	std::cout << "Framerate: " <<1.0/diffTime<< '\n';

		//std::cout << "elapsedTime: " << elapsedTime << '\n';
		//if (elapsedTime >= 10)
		//	std::cout << "Avg Framerate: " << totalFrames/elapsedTime << '\n';

		totalFrames++;
	}

	renderer->terminate();
	return 0;

}