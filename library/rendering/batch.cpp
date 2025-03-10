#include "batch.h"

void bindUniformMat4(glm::mat4 matrix, std::string name)
{
	glUniformMatrix4fv(glGetUniformLocation(ren::getActiveProgram(),
		name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void bindUniformBool(bool b, std::string name)
{
	glUniform1i(glGetUniformLocation(ren::getActiveProgram(),
		name.c_str()), b);
}


Batch::Batch(std::vector <float> vertices, std::vector <unsigned int> indicies, Material* material) :
	vao(vertices, indicies), material{material}
{

}

Batch::Batch(std::vector <float> vertices, Material* material) :
	vao(vertices), material{ material }
{}

Batch::~Batch()
{
	delete(material);
	material = NULL;
}

void Batch::draw(glm::mat4& modelMat)
{
	
	ren::setActiveProgram(material->getProgram());

	bindUniformMat4(modelMat, "modelMatrix");
	bindUniformMat4(ren::getActiveCamera(), "cameraMatrix");
	bindUniformMat4(ren::getActiveProjection(), "projMatrix");
	bindUniformBool(isInstanced, "isInstanced");



	vao.bind();
	//draw type depends on whether the objects has an ebo

	//also depends on whether we are instanced or not

	if (isInstanced)
	{
		if (vao.isUsingEBO())
			glDrawElementsInstanced(GL_TRIANGLES, GLsizei(vao.getIndiciesSize()), GL_UNSIGNED_INT, 0, vao.getInstancesAmount());
		else
			glDrawArraysInstanced(GL_TRIANGLES, 0, GLsizei(vao.getVerticesSize()), vao.getInstancesAmount());
	}
	else
	{
		if (vao.isUsingEBO())
			glDrawElements(GL_TRIANGLES, GLsizei(vao.getIndiciesSize()), GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, GLsizei(vao.getVerticesSize()));
	}



	vao.unbind();
}


const VAO& Batch::getVAO()
{
	return vao;
}
  Material* Batch::getMaterial()
{
	return material;
}


void Batch::addToBatch(Batch* otherBatch, glm::mat4& offsetModelMat)
{
	//if material is different, we're not batching!!!, that defeats the point
	//Material* m = otherBatch->getMaterial();
	if (!material->equals(otherBatch->getMaterial()))
	{
		std::cout << "can't add batch at memory " << otherBatch << "material doesn't match this ones" << '\n';
		return;
	}
		

	//the translation data of our offset is in the righmost column x, y z, w
	glm::vec3 newCenterOfBatch = glm::vec3(offsetModelMat[3]) * -0.5f;
	std::cout << "actual model matrix delta in batch: " << newCenterOfBatch.x << ", "
		<< newCenterOfBatch.y << ", " << newCenterOfBatch.z << '\n';

	//apply matrix to the data, this is gonna be expensive but we only need to do it once

	VAO otherVAO = otherBatch->getVAO();
	auto otherVerts = otherVAO.getVertices();
	auto otherInds = otherVAO.getIndicies();

	auto ourVerts = vao.getVertices();
	auto ourInds = vao.getIndicies();

	//now i hope i can edit these

	//dont edit the vertices!!!, just multiply them with matrices
	std::vector <glm::vec4> newPoints;
	int indOffset = ourVerts.size()/4;

	//4 nums per vertex, they should always be divisible by 4
	for (int i = 0; i<otherVerts.size(); i += 4)
	{
		//for each set of verts, grab them from the vertices list, and them multiply them by the offsetMatrix
		glm::vec4 newPoint = offsetModelMat * glm::vec4(otherVerts[i], otherVerts[i + 1], otherVerts[i + 2], otherVerts[i + 3]);

		//now this vertex in with our current batches vertices
		ourVerts.push_back(newPoint.x);
		ourVerts.push_back(newPoint.y);
		ourVerts.push_back(newPoint.z);
		ourVerts.push_back(newPoint.w);
	}

	//update our indicies
	//std::cout << "otherInds" << otherInds.size() << '\n';
	//std::cout << "ourInds" << ourInds.size() << '\n';

	
	for (int i = 0; i < otherInds.size(); i++)
	{
		ourInds.push_back(otherInds[i] + indOffset );
	}


	/*
	//finally we can create a new VAO with the new indicies and vertices
	for (int i = 0; i < ourVerts.size(); i += 4)
	{
		std::cout << ourVerts[i] << ", " << ourVerts[i + 1] << ", " << ourVerts[i + 2] << ", " << ourVerts[i + 3] << '\n';
	}

	for (int i = 0; i < ourInds.size(); i += 3)
	{
		std::cout << ourInds[i] << ", " << ourInds[i + 1] << ", " << ourInds[i + 2] << '\n';
	}

	*/
	//finally, move all our points, by the offset from before
	//t be efficient, this is gonna look disgusting

	//either 0, 1, 2, 3

	
	int currentSubtractor = 0;

	for (int i = 0; i < ourVerts.size(); i++)
	{
		if (currentSubtractor >= 4)
			currentSubtractor = 0;


		if (currentSubtractor == 0)
			ourVerts[i] += newCenterOfBatch.x;
		else if (currentSubtractor == 1)
			ourVerts[i] += newCenterOfBatch.y;
		else if (currentSubtractor == 2)
			ourVerts[i] += newCenterOfBatch.z;

		currentSubtractor++;
	}

	
	
	/*
	//finally we can create a new VAO with the new indicies and vertices
	for (int i = 0; i < ourVerts.size(); i+=4)
	{
		std::cout << ourVerts[i] << ", " << ourVerts[i + 1] << ", " << ourVerts[i + 2] << ", " << ourVerts[i + 3] << '\n';
	}

	for (int i = 0; i < ourInds.size(); i += 3)
	{
		std::cout << ourInds[i] << ", " << ourInds[i + 1] << ", " << ourInds[i + 2] <<  '\n';
	}


	//std::cout << "ourVerts:" << ourVerts.size() << '\n';
	//std::cout << "ourInds:" << ourInds.size() << '\n';

	*/
	vao = VAO(ourVerts, ourInds);
			
}


void Batch::setupForInstancing(std::vector <glm::mat4>& instModels)
{
	isInstanced = true;

	//now we have to rebuild vao for instancing as it needs new attrib arrays
	vao.setupForInstancing(instModels);
}





