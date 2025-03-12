#include "shape.h"


std::unordered_map <ShapeType, Shape> Shape::typeToShape;

Shape::Shape()
{

}

//most basic constructor
Shape::Shape(ShapeType type)
{
	//will probably have raw data files later, for now, this will be embedded

	//check if there is a shape we can't copy that is already of this type
	if (!(typeToShape.find(type) == typeToShape.end())) {
		// found so dont add new shader
		this->vertices = typeToShape[type].getVertices();
		this->indicies = typeToShape[type].getIndicies();
	}
	else
	{
		std::cout << "creating new shape" << '\n';

		switch (type) {
			case ShapeType::TRIANGLE:
			{
				vertices = {
				//vertices         //texCoords
				0.0, 1.0, 0.0, 1.0, 0.5, 0,
				0.866, -0.5, 0.0, 1.0, 0.577, 0.75, 
				-0.866, -0.5, 0.0, 1.0, 0.077, 0.75 };

				indicies = {
					2, 1, 0
				};
				break;
			}
			case ShapeType::SQUARE:
			{
				vertices = {
				// vertices         //tex coords
				0.5, 0.5, 0.0, 1.0, 1, 0,
				0.5, -0.5, 0.0, 1.0, 1, 1,
				-0.5, -0.5, 0.0, 1.0, 0, 1,
				-0.5, 0.5, 0.0, 1.0 , 0, 0 };

				indicies = {
					2, 1, 0,
					3, 2, 0
				};
				break;
			}
			case ShapeType::TRIANGULAR_PYRAMID:
			{
				vertices = {
				-0.5, -0.2887,-0.2041, 1.0, 0.5, 0,
				0.0,0.5774, -0.2041, 1.0, 0.577, 0.75,
				0.5, -0.2887, -0.2041, 1.0, 0.077, 0.75,
				0.0, 0.0, 0.6125, 1.0, 0.077, 0.25 };

				

				indicies = {
					0, 1, 2, 
					2, 1, 3,
					3, 1, 0,
					3, 0, 2
				};

				break;
			}
			case ShapeType::CUBE:
			{
				vertices = {
					//vertices    //texcorrds
				-0.5, -0.5, 0.5, 1.0, 0, 1,
				-0.5, 0.5, 0.5, 1.0, 0, 0,
				0.5, 0.5, 0.5, 1.0, 1, 0,
				0.5, -0.5, 0.5, 1.0, 1, 1,
				-0.5, -0.5, -0.5, 1.0, 1, 0,
				-0.5, 0.5, -0.5, 1.0, 1, 1,
				0.5, 0.5, -0.5, 1.0, 0, 1,
				0.5, -0.5, -0.5, 1.0 ,0, 0 };


				

				indicies = {
					2, 1, 0,
					3, 2, 0,
					6, 2, 3,
					7, 6, 3,
					5, 6, 7,
					4, 5, 7,
					1, 5, 4,
					0, 1, 4,
					7, 3, 0,
					4, 7, 0,
					2, 6, 5,
					1, 2, 5};

				break;
			}
		}

		typeToShape[type] = *this;
	}
}




  std::vector <float>& Shape::getVertices()
{
	return vertices;
}
  std::vector <unsigned int>& Shape::getIndicies()
{
	return indicies;
}





