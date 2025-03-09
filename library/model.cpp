#include "model.h"

unsigned int idCounter = 0;

Model::Model(std::vector <float>& vertices, Material* material) 
{
	if (material == NULL)
		material = new Material(shad::defaultShader);

	
	renderable = new Renderable(vertices, material);
	transformer = new Transformer();
	id = idCounter;
	idCounter++;
}

Model::Model(ShapeType sType, Material* material)
{
	if (material == NULL)
		material = new Material(shad::defaultShader);

	Shape s(sType);
	std::vector <float> verts = s.getVertices();
	std::vector <unsigned int> inds = s.getIndicies();
	renderable = new Renderable(verts, inds, material);
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