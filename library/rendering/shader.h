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
	void initShaderIfNotFound(std::string filepath);

	GLuint getProgram(std::string shaderName);

	const std::string defaultShader = "basicShader.shader";
};