#include "GLProgramManager.h"

using namespace cocos2d;
using namespace std;

static GLProgramManager* _sharedGLProgramManager = nullptr;

GLProgramManager::GLProgramManager()
	: _shaderDirectory("shaders") {}

GLProgramManager* GLProgramManager::getInstance()
{
	if (_sharedGLProgramManager == nullptr) {
		_sharedGLProgramManager = new (std::nothrow) GLProgramManager();
	}
	return _sharedGLProgramManager;
}

// Gets a shader or creates it if it doesn't exist.
GLProgram* GLProgramManager::getProgram(const char* programIdentifier)
{
	GLProgram* program = GLProgramCache::getInstance()->getGLProgram(programIdentifier);
	if (program == nullptr)
	{
		program = this->createProgram(programIdentifier);
	}
	return program;
}

// Constructs a shader of the form ./shaderDir/programIdentifier.(vert, frag)
GLProgram* GLProgramManager::createProgram(const char* programIdentifier)
{
	string vertPath = _shaderDirectory + "/" + programIdentifier + ".vert";
	string fragPath = _shaderDirectory + "/" + programIdentifier + ".frag";
	GLProgram* program = nullptr;
	try
	{
		program = GLProgram::createWithFilenames(vertPath.c_str(), fragPath.c_str());
		GLProgramCache::getInstance()->addGLProgram(program, programIdentifier);
	}
	catch (exception e)
	{
		CCLOG("Error: Shader was not found.");
	}
	return program;
}
