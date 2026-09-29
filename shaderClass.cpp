#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//create vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach vertex shader scource to the object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compiles the shader
	glCompileShader(vertexShader);

	//create fragment shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//attach fragment shader scource to the object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//compiles the shader
	glCompileShader(fragmentShader);

	//create shader program object
	ID = glCreateProgram();

	//attach the shaders to the program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//wraps up the shaders into the shader program
	glLinkProgram(ID);

	//deletes the now useless shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}