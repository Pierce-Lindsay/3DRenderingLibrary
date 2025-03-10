#include "model.h"

unsigned int idCounter = 0;

Model::Model(std::vector <float>& vertices, Transformer* transformer, Material* material) 
	:transformer{transformer}, material{material}
{
	checkInitDefaults();

	//above func makes sure material and transformer are defined
	renderable = new Renderable(vertices, this->material);
}

Model::Model(ShapeType sType, Transformer* transformer, Material* material)
	:transformer{ transformer }, material{ material }
{
	checkInitDefaults();

	Shape s(sType);
	std::vector <float> verts = s.getVertices();
	std::vector <unsigned int> inds = s.getIndicies();
	renderable = new Renderable(verts, inds, this->material);

}

void Model::checkInitDefaults()
{
	//defaults!!!
	if (material == NULL)
		material = new Material(shad::defaultShader);

	if (transformer == NULL)
		transformer = new Transformer();

	//always do this no matter what
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
	glm::mat4 temp = determineHierarchyModelMat();
	renderable->draw(temp);
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