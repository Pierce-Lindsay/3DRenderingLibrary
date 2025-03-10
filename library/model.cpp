#include "model.h"

unsigned int idCounter = 0;

Model::Model(std::vector <float>& vertices, Transformer* transformer, Material* material) 
	:transformer{transformer}, material{material}
{
	checkInitDefaults();

	//above func makes sure material and transformer are defined
	batch = new Batch(vertices, this->material);
}

Model::Model(std::vector <float>& vertices, std::vector <unsigned int>& indicies, Transformer* transformer, Material* material)
	:transformer{ transformer }, material{ material }
{
	checkInitDefaults();

	//above func makes sure material and transformer are defined
	batch = new Batch(vertices, indicies, this->material);
}

Model::Model(ShapeType sType, Transformer* transformer, Material* material)
	:transformer{ transformer }, material{ material }
{
	checkInitDefaults();

	Shape s(sType);
	std::vector <float> verts = s.getVertices();
	std::vector <unsigned int> inds = s.getIndicies();
	batch = new Batch(verts, inds, this->material);

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
	delete(batch);
	batch = NULL;

	material = NULL;
	//note deleting batch should delete material
}


void Model::draw()
{
	glm::mat4 temp = determineHierarchyModelMat();
	batch->draw(temp);
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


//this is for batching, its takes the other model, uses its transformation matrix as an offset, and then if
	//the other model has the same material, it batchtes it in this models batch
void Model::mergeHereWithSameMaterial(Model* other)
{
	//note, this is using the absolute modelmat, not the hierarchical one, this
	//is because we want to sever ties with any previous object
	glm::mat4 mat = other->transformer->getModelMat();
	batch->addToBatch(other->batch, mat);
}


//returns deep copy of this Model
Model* Model::deepCopy()
{
	//easierst way is to just do deep copies of the thinsg we needs for Models constructor
	VAO oldVAO = batch->getVAO();
	auto oldVerts = oldVAO.getVertices();
	auto oldInds = oldVAO.getIndicies();

	std::vector <float> newVerts;
	std::vector <unsigned int> newInds;

	for (int i = 0; i < oldVerts.size(); i++)
		newVerts.push_back(oldVerts[i]);

	for (int i = 0; i < oldInds.size(); i++)
		newInds.push_back(oldInds[i]);

	Transformer* trans = new Transformer(transformer->deepCopy());
	Material* newMat = new Material(material->deepCopy());
	Model* newM = new Model(newVerts, newInds, trans, newMat);
	return newM;
}


Batch* Model::getBatch()
{
	return batch;
}