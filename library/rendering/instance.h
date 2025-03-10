#pragma once
#include "../rendererEssentials.h"
#include "../model.h"

//needs model* to be defined to work, takes a model, makes an instance out of it
class Instance
{
private:
	

public:

	Model* model;

	//initialize Instance with a much of model matrices so we know know what to do with the instances
	Instance(Model* modelToCopy, std::vector <Transformer*> instTs);
	~Instance();

	void add(Transformer* instT);

	void drawInstances();

};