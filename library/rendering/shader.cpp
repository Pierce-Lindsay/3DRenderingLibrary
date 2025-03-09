#include "shader.h"



shader_sources Shader::get_sources(std::string filepath)
{
	shader_sources s_s;

	std::string shader_source;
	std::ifstream file;
	file.open(filepath);
	if (file.is_open())
		std::cout << "shaders file opened" << '\n';
	//create modes for pushing data
	//a mode will be true until proven otherwise
	enum class shader_push_mode {
		VERTEX,
		TCS,
		TES,
		GEO,
		FRAGMENT,
	};
	shader_push_mode mode = shader_push_mode::VERTEX;
	while (file)
	{
		//get the current line of file
		std::string line;
		std::getline(file, line);

		if (line == "//shader vertex")
		{
			mode = shader_push_mode::VERTEX;
		}
		else if (line == "//shader tcs")
		{
			mode = shader_push_mode::TCS;
		}
		else if (line == "//shader tes")
		{
			mode = shader_push_mode::TES;
		}
		else if (line == "//shader geometry")
		{
			mode = shader_push_mode::GEO;
		}
		else if (line == "//shader fragment")
		{
			mode = shader_push_mode::FRAGMENT;
		}


		switch (mode)
		{
		case shader_push_mode::VERTEX:
		{
			s_s.vertex_source.append(line);
			s_s.vertex_source.append("\n");
			break;
		}
		case shader_push_mode::TES:
		{
			s_s.tes_source.append(line);
			s_s.tes_source.append("\n");
			break;
		}
		case shader_push_mode::TCS:
		{
			s_s.tcs_source.append(line);
			s_s.tcs_source.append("\n");
			break;
		}
		case shader_push_mode::GEO:
		{
			s_s.geo_source.append(line);
			s_s.geo_source.append("\n");
			break;
		}
		case shader_push_mode::FRAGMENT:
		{
			s_s.fragment_source.append(line);
			s_s.fragment_source.append("\n");
			break;
		}
		default:
			break;
		}

	}

	file.close();



	return s_s;
}

Shader::Shader(std::string filepath)
{

	filepath.insert(0, "/library/rendering/shaders/");
	filepath.insert(0, std::filesystem::current_path().string());
	
	std::cout << "attempting to open: " << filepath << '\n';
	s_s = get_sources(filepath);
	 const GLchar* vertex_shader_source[]{ s_s.vertex_source.c_str()};
	 const GLchar* TCS_shader_source[]{ s_s.tcs_source.c_str()};
	 const GLchar* TES_shader_source[]{ s_s.tes_source.c_str() };
	 const GLchar* geo_shader_source[]{ s_s.geo_source.c_str() };
	 const GLchar* fragment_shader_source[]{ s_s.fragment_source.c_str() };
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	TCS_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(TCS_shader, 1, TCS_shader_source, NULL);
	glCompileShader(TCS_shader);

	TES_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(TES_shader, 1, TES_shader_source, NULL);
	glCompileShader(TES_shader);

	geo_shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geo_shader, 1, geo_shader_source, NULL);
	glCompileShader(geo_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	std::cout << program << '\n';


	glAttachShader(program, vertex_shader);


	if (s_s.tcs_source.empty() == false)
		glAttachShader(program, TCS_shader);



	if (s_s.tes_source.empty() == false)
		glAttachShader(program, TES_shader);





	if (s_s.geo_source.empty() == false)
		glAttachShader(program, geo_shader);


	glAttachShader(program, fragment_shader);
	std::cout << program << '\n';
	glLinkProgram(program);
	std::cout << program << '\n';
	std::cout << fragment_shader_source << '\n';
	//program contains shaders so they can be deleted now
	glDeleteShader(vertex_shader);
	glDeleteShader(TCS_shader);
	glDeleteShader(TES_shader);
	glDeleteShader(geo_shader);
	glDeleteShader(fragment_shader);
}


GLuint Shader::getProgram()
{
	return program;
}



