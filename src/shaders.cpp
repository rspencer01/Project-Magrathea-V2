#include <magrathea.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <shaders.h>
#include <assert.h>

GLuint gSampler;

/// Gets rid of all the 0x0D values in a file (kills the GLSL compiler)
/// @param program The shader program to sanatise
/// @param size    The size of said program
void sanatiseShader(char* program, int size)
{
  // Loop through the file, replacing '\r' with newlines
  for (int i = 0;i<size;i++)
   if (program[i]==0x0D)
      program[i] = 0x0A;
}

/// Ask OpenGL to create a new shader program, and kill the program if there was an error
ShaderProgram::ShaderProgram()
{
  // Construct the program we are going to use
  ShaderProgramID = glCreateProgramObjectARB();
  // If there was an error, let us know
  if (ShaderProgramID == 0) 
    DIE("Error creating new shader program");
}

/// Load a shader program from a source file.
/// @param shaderPath The path to the source file
/// @param shaderType The type of shader object to load (fragment or vertex)
void ShaderProgram::LoadShader(const char* shaderPath, GLenum shaderType)
{
  // Create us a new shader
  GLuint ShaderObj = glCreateShaderObjectARB(shaderType);
  // If something went wrong, tell us about it
  if (ShaderObj == 0) 
    DIE("Error creating shader object");
  // Now open the shader source.
  FILE* fp = fopen(shaderPath,"rb");
  if (fp==NULL)
    DIE2("Cannot open shader source",shaderPath);
  // Find the length of the file
  fseek(fp,0,SEEK_END);
  int fileSize = ftell(fp);
  rewind(fp);
  // Read in the entire file
  const GLchar* progSource = new GLchar[fileSize];
  fread((void*)progSource,fileSize,1,fp);
  // Sanatise the shader
  sanatiseShader((char*)progSource,fileSize);
  // And tell opengl that it is the source code
  glShaderSourceARB(ShaderObj, 1, &progSource, &fileSize);
  // Now we are done with these, get rid of them
  delete progSource;
  fclose(fp);
  // Attempt to compile the shader
  glCompileShaderARB(ShaderObj);
  // If there is an error, tell us about it
  GLint success;
  glGetObjectParameterivARB(ShaderObj, GL_OBJECT_COMPILE_STATUS_ARB, &success);
  if (success==0) 
  {
    GLchar InfoLog[1024];
    glGetInfoLogARB(ShaderObj, 1024, NULL, InfoLog);
    DIE3("Error compiling shader",shaderPath, InfoLog);
  }
  // Attach the compiled object to the program
  glAttachShader(ShaderProgramID, ShaderObj);
}

/// Compile the loaded shaders into the program
void ShaderProgram::CompileAll()
{
  // Bind the attributes to the right locations
  glBindAttribLocation(ShaderProgramID,0,"inPosition");
  glBindAttribLocation(ShaderProgramID,1,"inColour");
  glBindAttribLocation(ShaderProgramID,2,"inTex");
  glBindAttribLocation(ShaderProgramID,3,"inNorm");
  glBindAttribLocation(ShaderProgramID,4,"inTexShades");
  // Link the program
  glLinkProgram(ShaderProgramID);
  // If there is an error...
  GLint Success = 0;
  glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &Success);
	if (Success == 0) 
  {
    GLchar ErrorLog[1024] = { 0 };
		glGetProgramInfoLog(ShaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
    DIE2("Error linking shader program:", ErrorLog);
	}
  // Confirm that this is valid
  glValidateProgram(ShaderProgramID);
  // Again witht the error
  glGetProgramiv(ShaderProgramID, GL_VALIDATE_STATUS, &Success);
  if (!Success) 
  {
    GLchar ErrorLog[1024] = { 0 };
    glGetProgramInfoLog(ShaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
    DIE2("Invalid shader program:", ErrorLog);
  }
}

/// Load the program into GPU memory, ready to be run
void ShaderProgram::Load()
{
  // Now load this program
  glUseProgram(ShaderProgramID);
  variableLocations.clear();
  objPos = (GLuint)-1;
}

/// The object matrix is set so often that looking it up (even in a map) each time
/// is far too costly.  This function specifically caches that matrix (unlike
/// setMatrix which does a generic matrix).
/// @param value The value to set the matrix to.
void ShaderProgram::setObjectMatrix(float* value)
{
  if (objPos==(GLuint)-1)
    objPos = glGetUniformLocation(ShaderProgramID, "objectMatrix");
  glUniformMatrix4fv(objPos,1,GL_TRUE,value);
}

void ShaderProgram::setMatrix(const char* varName, float* value)
{
  std::string vName (varName);
  if (variableLocations.count(vName)==0)
  {
    variableLocations[vName] = glGetUniformLocation(ShaderProgramID, varName);
  }
  if (variableLocations[vName]==0xFFFFFFFF)
  {
    printf("ERROR: Cannot find matrix variable '%s' in shader\n",varName);
    return;
  }
  glUniformMatrix4fv(variableLocations[vName],1,GL_TRUE,value);
}

void ShaderProgram::setInt(const char* varName, unsigned int value)
{
  std::string vName (varName);
  if (variableLocations.count(vName)==0)
  {
    variableLocations[vName] = glGetUniformLocation(ShaderProgramID, varName);
  }
  if (variableLocations[vName]==0xFFFFFFFF)
  {
    printf("ERROR: Cannot find integer variable '%s' in shader\n",varName);
    return;
  }
  glUniform1i(variableLocations[vName],value);
}

void ShaderProgram::setFloat(const char* varName, float value)
{
  std::string vName (varName);
  if (variableLocations.count(vName)==0)
  {
    variableLocations[vName] = glGetUniformLocation(ShaderProgramID, varName);
  }
  if (variableLocations[vName]==0xFFFFFFFF)
  {
    printf("ERROR: Cannot find float variable '%s' in shader\n",varName);
    return;
  }
  glUniform1f(variableLocations[vName],value);
}

void ShaderProgram::setVec3(const char* varName, float* value)
{
  std::string vName (varName);
  if (variableLocations.count(vName)==0)
  {
    variableLocations[vName] = glGetUniformLocation(ShaderProgramID, varName);
  }
  if (variableLocations[vName]==0xFFFFFFFF)
  {
    printf("ERROR: Cannot find vec3 variable '%s' in shader\n",varName);
    return;
  }
  //glUniform3fv(variableLocations[vName],3,value);
  glUniform3f(variableLocations[vName],value[0],value[1],value[2]);
}