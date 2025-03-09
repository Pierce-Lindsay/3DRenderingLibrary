#include "model.h"

unsigned int idCounter = 0;

Model::Model(std::vector <float> vertices)
{
	renderable = new Renderable(vertices);
	transformer = new Transformer();
	id = idCounter;
	idCounter++;
}


Model::~Model()
{
	delete(transformer);
	transformer = NULL;
	delete(renderable);
	renderable = NULL;
}


void Model::draw()
{
	renderable->draw(determineHierarchyModelMat());
}

//uses hierarchy from parents to recursivley determine the correct model matrix
glm::mat4 Model::determineHierarchyModelMat()
{
	//no parent so just return this ones model mat
	if (parent == NULL)
	{
		return transformer->getModelMat();
	}
	else
	{
		return parent->determineHierarchyModelMat() * transformer->getModelMat();
	}
}