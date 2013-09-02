#include <gl\glew.h>
#include <gl\glut.h>
#include <stdio.h>
#include <shaders.h>
#include <assert.h>

GLuint glTransformationMatrixLocation;
GLuint glProjectionMatrixLocation;
GLuint gSampler;

/*
/// Loads a shader into the given shader program
/// @param ShaderProgram The program to compile this shader into
/// @param shaderPath The path to the file containing the shader source code
/// @param ShaderType The type of shader (fragment/vertex)
void LoadShader(GLuint ShaderProgram, const char* shaderPath, GLenum ShaderType)
{

}

static void CompileShaders()
{

}  

*/
void loadShaders()
{
  printf("Initialising shaders\n");
  //CompileShaders();
}

void setTransformationMatrix(float* mat)
{
  glUniformMatrix4fv(glTransformationMatrixLocation,1,GL_TRUE,mat);
}
void setProjectionMatrix(float* mat)
{
  glUniformMatrix4fv(glProjectionMatrixLocation,1,GL_TRUE,mat);
}

ShaderProgram::ShaderProgram()
{
  constructProgram();
  // Now load the two shaders
  LoadShader("../shaders/vertexShader.shd", GL_VERTEX_SHADER);
  LoadShader("../shaders/fragmentShader.shd", GL_FRAGMENT_SHADER);
  // Compile...
  CompileAll();
}

void ShaderProgram::constructProgram()
{
  // Construct the program we are going to use
  ShaderProgramID = glCreateProgram();
  // If there was an error, let us know
  if (ShaderProgramID == 0) 
  {
    fprintf(stderr, "Error creating shader program\n");
    while(1);
  }
}

void ShaderProgram::LoadShader(const char* shaderPath, GLenum ShaderType)
{
  // Create us a new shader
  GLuint ShaderObj = glCreateShader(ShaderType);
  // If something went wrong, tell us about it
  if (ShaderObj == 0) 
  {
    fprintf(stderr, "Error creating shader type %d\n", ShaderType);
    while(1);
  }
  // Now open the shader source.
  FILE* fp = fopen(shaderPath,"r");
  // Find the length of the file
  fseek(fp,0,SEEK_END);
  int fileSize = ftell(fp);
  rewind(fp);
  // Read in the entire file
  const GLchar* p = new GLchar[fileSize];
  fread((void*)p,fileSize,1,fp);
  // And tell opengl that it is the source code
  glShaderSource(ShaderObj, 1, &p, &fileSize);
  // Now we are done with these, get rid of them
  delete p;
  fclose(fp);
  // Attempt to compile the shader
  glCompileShader(ShaderObj);
  // If there is an error, tell us about it
  GLint success;
  glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
  if (!success) 
  {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
    fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
    while(1);
  }
  // Attach the compiled object to the program
  glAttachShader(ShaderProgramID, ShaderObj);
}

void ShaderProgram::CompileAll()
{
  // Link them
  glLinkProgram(ShaderProgramID);
  // If there is an error...
  GLint Success = 0;
  glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &Success);
	if (Success == 0) 
  {
    GLchar ErrorLog[1024] = { 0 };
		glGetProgramInfoLog(ShaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
    while(1);
	}
  // Confirm that this is valid
  glValidateProgram(ShaderProgramID);
  // Again witht the error
  glGetProgramiv(ShaderProgramID, GL_VALIDATE_STATUS, &Success);
  if (!Success) 
  {
    GLchar ErrorLog[1024] = { 0 };
    glGetProgramInfoLog(ShaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    while(1);
  }
  // Now load this program
  glUseProgram(ShaderProgramID);
  // Get all the locations of the variables we want
  glTransformationMatrixLocation = glGetUniformLocation(ShaderProgramID, "gWorld");
  glProjectionMatrixLocation = glGetUniformLocation(ShaderProgramID, "gProj");
  gSampler = glGetUniformLocation(ShaderProgramID, "gSampler");
  glUniform1i(gSampler, 0);
  assert(gSampler != 0xFFFFFFFF);
  assert(glTransformationMatrixLocation != 0xFFFFFFFF);
  assert(glProjectionMatrixLocation != 0xFFFFFFFF);
}
