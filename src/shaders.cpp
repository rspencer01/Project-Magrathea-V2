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
  objectDataPosition = (GLuint)-1;
  frameDataPosition = (GLuint)-1;
  frameData.colour[0] = 1;
  frameData.colour[1] = 1;
  frameData.colour[2] = 1;
  frameData.colour[3] = 1;
  glGenBuffers(1, &frameDataBO);
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
  // Set the attribute locations
  glVertexAttribPointerARB(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),0);
  glVertexAttribPointerARB(1,4,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(3*sizeof(float)));
  glVertexAttribPointerARB(2,2,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(10*sizeof(float)));
  glVertexAttribPointerARB(3,3,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(7*sizeof(float)));
  glVertexAttribPointerARB(4,4,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(12*sizeof(float)));
  setFrameData();
}

GLuint ShaderProgram::getVariablePosition(const char* name)
{
  // A std::string for hasing purposes
  std::string vName (name);
  // If we don't know this variable, find out its location
  if (variableLocations.count(vName)==0)
    variableLocations[vName] = glGetUniformLocation(ShaderProgramID, name);
  // Die nicely if we need to
  //if (variableLocations[vName]==0xFFFFFFFF)
  //  DIE2("Cannot find shader variable",name);
  // Return the answer
  return variableLocations[vName];
}

void ShaderProgram::setMatrix(const char* varName, float* value)
{
  glUniformMatrix4fv(getVariablePosition(varName),1,GL_TRUE,value);
}

void ShaderProgram::setInt(const char* varName, unsigned int value)
{
  glUniform1i(getVariablePosition(varName),value);
}

void ShaderProgram::setFloat(const char* varName, float value)
{
  glUniform1f(getVariablePosition(varName),value);
}

void ShaderProgram::setVec3(const char* varName, float* value)
{
  glUniform3f(getVariablePosition(varName),value[0],value[1],value[2]);
}

void ShaderProgram::setObjectData(GLuint bo)
{
  if (objectDataPosition == (GLuint) -1)
  {
    objectDataPosition = glGetUniformBlockIndex(ShaderProgramID,"objectData");
    glUniformBlockBinding(ShaderProgramID, objectDataPosition, 0);
  }
  glBindBufferBase(GL_UNIFORM_BUFFER,0,bo);
}

void ShaderProgram::setFrameData()
{
  glBindBuffer(GL_UNIFORM_BUFFER, frameDataBO);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(frameData), &frameData, GL_DYNAMIC_DRAW);

  if (frameDataPosition == (GLuint) -1)
  {
    frameDataPosition = glGetUniformBlockIndex(ShaderProgramID,"frameData");
    glUniformBlockBinding(ShaderProgramID, frameDataPosition, 1);
  }
  glBindBufferBase(GL_UNIFORM_BUFFER,1,frameDataBO);
}