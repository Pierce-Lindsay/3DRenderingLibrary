//one of the main classes for generating vertices and indexes for mathmatical shapes
#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>

enum class ShapeType
{
	SQUARE,
	TRIANGLE,
	TRIANGULAR_PYRAMID,
	CUBE,
};

class Shape
{
private:
	//add normals and tex coords eventually!!!!
	std::vector <float> vertices;
	std::vector <unsigned int> indicies;

public:

	//most basic constructor
	Shape(ShapeType type);
	Shape();

	static std::unordered_map <ShapeType, Shape> typeToShape;

	  std::vector <float>& getVertices();
	 std::vector <unsigned int>& getIndicies();
};