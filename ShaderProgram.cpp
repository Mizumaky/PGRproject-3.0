#include "ShaderProgram.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::map<std::string, ShaderProgram> SPManager::s_programs; //yes i need this here

SPManager::SPManager() = default;

SPManager::~SPManager() {
	//iterate through the program map (.second = the GLuint) and delete everything
	for (auto& item : s_programs) {
		glDeleteProgram(item.second.program);
	}
	s_programs.clear();
}


std::string SPManager::readShader(const std::string & filename) {
	//prepare file
	std::string shaderCode;
	std::ifstream file(filename.c_str(), std::ios::in);
	if (!file.good()) {
		std::cout << "ERROR: Can't read file " << filename << std::endl;
		std::terminate();
	}
	//find start and end
	file.seekg(0, std::ios::end);
	shaderCode.resize(static_cast<unsigned int>(file.tellg()));
	file.seekg(0, std::ios::beg);
	//read
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint SPManager::createShader(const GLenum shaderType, const std::string & source, const std::string & name) {
	//create shader handle and prepare the string
	const GLuint shader = glCreateShader(shaderType);
	const char* p_shaderSource = source.c_str();
	const int shaderCodeSize = source.size();
	//load source into opengl and compile
	glShaderSource(shader, 1, &p_shaderSource, &shaderCodeSize);
	glCompileShader(shader);
	int compileResult = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	//check for errors
	if (compileResult == GL_FALSE) {
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, nullptr, &shaderLog[0]);
		std::cout << "ERROR: Can't compile shader: " << name << std::endl << &shaderLog[0] << std::endl;
		std::terminate();
	}
	return shader;
}

void SPManager::createProgram(const std::string & shaderName, const std::string & vsFilename, const std::string & fsFilename) {
	//check if program with this name already exists
	const std::map<std::string, ShaderProgram>::iterator programsIterator = s_programs.find(shaderName);
	if (programsIterator != s_programs.end()) {
		std::cout << "ERROR: Shader program with name '" << shaderName << "' already exists" << std::endl;
		std::terminate();
	}
	//read the shader files and save the code
	const std::string vertexShaderCode = readShader(vsFilename);
	const std::string fragmentShaderCode = readShader(fsFilename);
	//compile the shaders
	const GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	const GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

	//create the program handle
	const GLuint program = glCreateProgram();
	//attach shaders
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	//link it
	glLinkProgram(program);
	int linkResult = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	//check for link errors
	if (linkResult == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::cout << "ERROR: Can't link program" << std::endl << &programLog[0] << std::endl;
		std::terminate();
	}

	//TODO find attrib pointers and create the struct- DONE

	ShaderProgram shaderProgram;
	shaderProgram.program = program;

	// get position and color attributes locations
	shaderProgram.posLocation = glGetAttribLocation(shaderProgram.program, "position");
	shaderProgram.colorLocation = glGetAttribLocation(shaderProgram.program, "color");
	// get uniforms locations
	shaderProgram.PVMmatrixLocation = glGetUniformLocation(shaderProgram.program, "PVMmatrix");

	//add the shader program to the list (if not already present)
	s_programs[shaderName] = shaderProgram;
}

ShaderProgram SPManager::getShader(const std::string & shaderName) {
	const std::map<std::string, ShaderProgram>::iterator programsIterator = s_programs.find(shaderName);
	if (programsIterator == s_programs.end()) {
		std::cout << "ERROR: Shader program with name '" << shaderName << "' doesn't exists" << std::endl;
		std::terminate();
	}
	return s_programs[shaderName];
}

void SPManager::deleteShader(const std::string & shaderName) {
	const auto& programsIterator = s_programs.find(shaderName);
	if (programsIterator == s_programs.end()) {
		std::cout << "ERROR: Shader program with name '" << shaderName << "' doesn't exists" << std::endl;
		std::terminate();
	}
	s_programs.erase(shaderName);
}
