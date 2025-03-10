#pragma once
#include "../rendererEssentials.h"
#include "glData.h"
#include "material.h"

class Batch
{
private:
	VAO vao;
	Material* material;
	bool isInstanced = false;
public:
	//if we were to change these vertices later, they could change our shapes which are supposed to be constant
	//for that reason, we are not taking in a reference
	Batch(std::vector <float> vertices, std::vector <unsigned int> indicies, Material* material);
	Batch(std::vector <float> vertices, Material* material);
	~Batch();

	//note these methods add new data to our batch, the new center point will be the center of all the points we pass in
	//we need to make sure said center is at 0,0 after applying offset to points
	//for offset to work properly, the passed in batch should already be centered at 0, 0, we can use the translation of 
	//the passed in modelMat, half it and find the new correct center 

	//also note!, as for now, will not be allowing individual vertices in a batch to be edited -> for all intents and purposes
	//if you make it batch, your commiting to the relationship of all those vertices
	void addToBatch(Batch* otherBatch, glm::mat4& offsetModelMat);

	void draw(glm::mat4& modelMat);

	const VAO& getVAO();

	Material* getMaterial();

	void setupForInstancing(std::vector <glm::mat4>& instModels);
};