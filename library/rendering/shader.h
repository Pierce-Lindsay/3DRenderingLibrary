#include "../rendererEssentials.h"
#include <filesystem>
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>



namespace shad
{
	void initShaderAndCheckIfExists(std::string filename);
	void initShaderAndCheckIfExists(std::string filepath, std::string filename);

	GLuint getProgram(std::string shaderName);

	void initShaders();

	const std::string defaultShader = "basicShader.shader";
};