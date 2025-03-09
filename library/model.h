#pragma once
#include "math/transformer.h"
#include "math/shape.h"
#include"rendering/renderable.h"

//the main structure that is used for handling a thing that gets rendered along with transformation
class Model
{
private:
	Model* parent = NULL;
	Renderable* renderable = NULL;
	Transformer* transformer = NULL;

	unsigned int id;

public:

	//just pass in vertices with this constructor, default transformer, use default material if null
	Model(std::vector <float>& vertices, Material* material = NULL);
	Model(ShapeType sType, Material* material = NULL);
	~Model();

	void draw();

	//uses hierarchy from parents to recursivley determine the correct model matrix
	glm::mat4 determineHierarchyModelMat();

};