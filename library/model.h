#pragma once
#include "math/transformer.h"
#include "math/shape.h"
#include"rendering/batch.h"

//the main structure that is used for handling a thing that gets rendered along with transformation
class Model
{
private:
	Model* parent = NULL;
	Batch* batch = NULL;
	Transformer* transformer = NULL;
	//shouldn't really be used much, mainly here for convenience, renderable already has material defined in it
	Material* material = NULL;

	unsigned int id;

public:

	//just pass in vertices with this constructor, default transformer, use default material if null
	Model(std::vector <float>& vertices, Transformer* transformer = NULL, Material* material = NULL);
	Model(ShapeType sType, Transformer* transformer = NULL, Material* material = NULL);

	//needs material because material is part of renderable not model
	void checkInitDefaults();

	~Model();

	void draw();

	//this is for batching, its takes the other model, uses its transformation matrix as an offset, and then if
	//the other model has the same material, it batchtes it in this models batch, assumes both objects base vertices are
	//centered at 0,0
	void mergeHereWithSameMaterial(Model* other);

	//uses hierarchy from parents to recursivley determine the correct model matrix
	glm::mat4 determineHierarchyModelMat();

};