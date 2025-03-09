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

		if (type == ShapeType::TRIANGLE)
		{
			vertices = {
			0.0, 0.5, 0.0, 1.0,
			0.5, -0.5, 0.0, 1.0,
			-0.5, -0.5, 0.0, 1.0 };

			indicies = {
				0, 1, 2
			};
		}
		else if (type == ShapeType::SQUARE)
		{
			vertices = {
			0.5, 0.5, 0.0, 1.0,
			0.5, -0.5, 0.0, 1.0,
			-0.5, -0.5, 0.0, 1.0,
			-0.5, 0.5, 0.0, 1.0 };

			indicies = {
				0, 1, 2,
				0, 2, 3
			};
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





