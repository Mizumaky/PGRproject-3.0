#pragma once
#include <map>
#include <string>

#include "CoreLibs.h"


typedef struct Shader {
    // identifier for the shader program
    GLuint program;          // = 0;
    // vertex attributes locations
    GLint posLocation;       // = -1;
    GLint colorLocation;     // = -1;
    GLint PVMmatrixLocation;    // = -1;
} Shader;



class ShaderManager
{
public:
	virtual ~ShaderManager(); //TODO do i need this?
	//custom constructor for an OpenGL program
	static void createShader(const std::string& shaderName, const std::string& vsFilename, const std::string& fsFilename);
	//other functions
	static void deleteShader(const std::string& shaderName);
	static GLuint getShaderProgram(const std::string& shaderName);
	static GLuint getShaderPosLoc(const std::string& shaderName);
	static GLuint getShaderColLoc(const std::string& shaderName);
	static GLuint getShaderPVMLoc(const std::string& shaderName);

private:
	//map with all the programs
	static std::map<std::string, Shader> s_shaders;
	//helper functions
	static Shader getShader(const std::string& shaderName);
	static std::string readShader(const std::string& filename);
	static GLuint compileShader(GLenum shaderType, const std::string& source, const std::string& name);
};
