#include "shader.h"


struct shader_sources {
	std::string vertex_source;
	std::string tcs_source;
	std::string tes_source;
	std::string geo_source;
	std::string fragment_source;
};


void checkFailedCompile(GLuint shader, std::string shaderName)
{
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		std::cout << "Error in " << shaderName << " Shader!" << '\n';

		// Provide the infolog in whatever manor you deem best.
		for (int i = 0; i < errorLog.size(); i++)
		{
			std::cout << errorLog[i];
		}
		// Exit with failure.
		glDeleteShader(shader); // Don't leak the shader.
		return;
	}
}


//every shader that is created is stored in this map and will return the program
 std::unordered_map <std::string, GLuint> shaderToProgram;


 GLuint program;
 GLuint vertex_shader;
 GLuint TCS_shader;
 GLuint TES_shader;
 GLuint geo_shader;
 GLuint fragment_shader;
 shader_sources s_s;

shader_sources get_sources(std::string filepath)
{
	shader_sources s_s;

	std::string shader_source;
	std::ifstream file;
	file.open(filepath);
	if (file.is_open())
		std::cout << filepath << " file opened" << '\n';
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

bool checkIfShaderExistsInMap(std::string name)
{
	if (!(shaderToProgram.find(name) == shaderToProgram.end())) {
		// found so dont add new shader
		return true;
	}
	return false;
}

void initShader(std::string fullPath, std::string name)
{
	std::cout << "attempting to open: " << fullPath << '\n';
	s_s = get_sources(fullPath);
	const GLchar* vertex_shader_source[]{ s_s.vertex_source.c_str() };
	const GLchar* TCS_shader_source[]{ s_s.tcs_source.c_str() };
	const GLchar* TES_shader_source[]{ s_s.tes_source.c_str() };
	const GLchar* geo_shader_source[]{ s_s.geo_source.c_str() };
	const GLchar* fragment_shader_source[]{ s_s.fragment_source.c_str() };
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	checkFailedCompile(vertex_shader, "Vertex");

	TCS_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(TCS_shader, 1, TCS_shader_source, NULL);
	glCompileShader(TCS_shader);

	checkFailedCompile(TCS_shader, "TCS");

	TES_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(TES_shader, 1, TES_shader_source, NULL);
	glCompileShader(TES_shader);

	checkFailedCompile(TES_shader, "TES");

	geo_shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geo_shader, 1, geo_shader_source, NULL);
	glCompileShader(geo_shader);

	checkFailedCompile(geo_shader, "GEO");

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	checkFailedCompile(fragment_shader, "Fragment");

	program = glCreateProgram();

	glAttachShader(program, vertex_shader);

	if (s_s.tcs_source.empty() == false)
		glAttachShader(program, TCS_shader);



	if (s_s.tes_source.empty() == false)
		glAttachShader(program, TES_shader);





	if (s_s.geo_source.empty() == false)
		glAttachShader(program, geo_shader);


	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	//program contains shaders so they can be deleted now
	glDeleteShader(vertex_shader);
	glDeleteShader(TCS_shader);
	glDeleteShader(TES_shader);
	glDeleteShader(geo_shader);
	glDeleteShader(fragment_shader);

	//add filepath with corresponsing program to map
	shaderToProgram[name] = program;
}

void shad::initShaderAndCheckIfExists(std::string filename)
{
	if (checkIfShaderExistsInMap(filename))
		return;

	std::string name = filename;

	filename.insert(0, "/assets/shaders/");
	filename.insert(0, std::filesystem::current_path().string());

	initShader(filename, name);

}


void shad::initShaderAndCheckIfExists(std::string filepath, std::string filename)
{
	if (checkIfShaderExistsInMap(filename))
		return;

	std::string name = filepath;

	initShader(filepath, filename);
}
	


void shad::initShaders()
{
	std::string path = "/assets/shaders/";
	path.insert(0, std::filesystem::current_path().string());

	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		initShaderAndCheckIfExists(entry.path().string(), entry.path().filename().string());
	}
}



GLuint shad::getProgram(std::string shaderName)
{
	return shaderToProgram[shaderName];
}



