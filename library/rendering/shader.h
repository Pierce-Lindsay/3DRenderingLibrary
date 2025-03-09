#include "../rendererEssentials.h"
#include <filesystem>
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct shader_sources {
	std::string vertex_source;
	std::string tcs_source;
	std::string tes_source;
	std::string geo_source;
	std::string fragment_source;
};

class Shader
{
private:
	GLuint program;
	GLuint vertex_shader;
	GLuint TCS_shader;
	GLuint TES_shader;
	GLuint geo_shader;
	GLuint fragment_shader;
	shader_sources s_s;
public:
	Shader(std::string filepath);
	shader_sources get_sources(std::string filepath);
	GLuint getProgram();

};