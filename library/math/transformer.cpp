#include "transformer.h"


Transformer::Transformer()
{
	modelMat = glm::mat4(1.0f);
	modelMat = glm::scale(modelMat, dialation);
	modelMat = glm::rotate(modelMat, glm::radians(rotation), rotationAxis);
	modelMat = glm::translate(modelMat, pos);	
}


glm::mat4 Transformer::getModelMat()
{
	return modelMat;
}
