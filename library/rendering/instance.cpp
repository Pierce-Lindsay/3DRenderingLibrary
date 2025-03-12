#include "instance.h"


//initialize Instance with a much of model matrices so we know know what to do with the instances
//deep copies model, so we can edit teh stuff inside
Instance::Instance(Model* modelToCopy, std::vector <Transformer*>& instTs)
{
	//first of all our model is a deep copy of model passed in so we can mess with stuff
	model = modelToCopy->deepCopy();
	
	//next turn Transformer* into models

	std::vector <glm::mat4> models;

	for (int i = 0; i < instTs.size(); i++)
	{
		//this is slow, computing thsi sequentially for a bagillion matrices sucks
		models.push_back(instTs[i]->getModelMat());
	}
	model->getBatch()->setupForInstancing(models);

}

Instance::Instance(Model* modelToCopy, std::vector <glm::mat4>& instTs)
{
	//first of all our model is a deep copy of model passed in so we can mess with stuff
	model = modelToCopy->deepCopy();
	model->getBatch()->setupForInstancing(instTs);
}

void Instance::add(Transformer* instT)
{

}

void Instance::drawInstances()
{
	model->draw();
}


Instance::~Instance()
{
	delete(model);
	model = NULL;
}