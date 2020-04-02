#pragma once
#include <map>
#include <string>

#include "CoreLibs.h"


typedef struct ShaderProgram {
    // identifier for the shader program
    GLuint program;          // = 0;
    // vertex attributes locations
    GLint posLocation;       // = -1;
    GLint colorLocation;     // = -1;
    GLint PVMmatrixLocation;    // = -1;
} ShaderProgram;



class SPManager
{
public:
	SPManager();
	virtual ~SPManager();
	//custom constructor for an OpenGL program
	static void createProgram(const std::string& shaderName, const std::string& vsFilename, const std::string& fsFilename);
	//other functions
	static ShaderProgram getShader(const std::string& shaderName);
	static void deleteShader(const std::string& shaderName);

private:
	//map with all the programs
	static std::map<std::string, ShaderProgram> s_programs;
	//helper functions
	static std::string readShader(const std::string& filename);
	static GLuint createShader(GLenum shaderType, const std::string& source, const std::string& name);
};
