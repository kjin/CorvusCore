#ifndef GL_PROGRAM_MANAGER_H_
#define GL_PROGRAM_MANAGER_H_

#include <string>
#include "cocos2d.h"

class GLProgramManager {
private:
	std::string _shaderDirectory;
public:
	static GLProgramManager* getInstance();

	// Sets the default shader directory
	void setShaderDirectory(std::string shaderDirectory)
	{
		_shaderDirectory = shaderDirectory;
	}
	// Gets a shader or creates it if it doesn't exist.
	cocos2d::GLProgram* getProgram(const char* programIdentifier);
private:
	GLProgramManager();

	// Constructs a shader of the form ./shaderDir/programIdentifier.(vert, frag)
	cocos2d::GLProgram* createProgram(const char* programIdentifier);
};

#endif
