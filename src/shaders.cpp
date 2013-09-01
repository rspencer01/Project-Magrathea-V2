#include <gl\glew.h>
#include <gl\glut.h>
#include <stdio.h>
#include <shaders.h>
#include <assert.h>

GLuint glTransformationMatrixLocation;
GLuint glProjectionMatrixLocation;
GLuint gSampler;

static void LoadShader(GLuint ShaderProgram, const char* shaderPath, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) 
    {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        while(1);
    }

    FILE* fp = fopen(shaderPath,"r");
    fseek(fp,0,SEEK_END);
    int fileSize = ftell(fp);
    rewind(fp);

    const GLchar* p = new GLchar[fileSize];
    fread((void*)p,fileSize,1,fp);
    GLint Lengths[1];
    Lengths[0]= fileSize;
    glShaderSource(ShaderObj, 1, &p, Lengths);
    delete p;
    fclose(fp);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        while(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
    
}

static void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    LoadShader(ShaderProgram, "../shaders/vertexShader.shd", GL_VERTEX_SHADER);
    LoadShader(ShaderProgram, "../shaders/fragmentShader.shd", GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        while(1);
	}

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        while(1);
    }

   glUseProgram(ShaderProgram);
   glTransformationMatrixLocation = glGetUniformLocation(ShaderProgram, "gWorld");
   glProjectionMatrixLocation = glGetUniformLocation(ShaderProgram, "gProj");
   gSampler = glGetUniformLocation(ShaderProgram, "gSampler");
   glUniform1i(gSampler, 0);
   assert(gSampler != 0xFFFFFFFF);
   assert(glTransformationMatrixLocation != 0xFFFFFFFF);
   assert(glProjectionMatrixLocation != 0xFFFFFFFF);
}  


void loadShaders()
{
  printf("Initialising shaders\n");
  CompileShaders();
}

void setTransformationMatrix(float* mat)
{
  glUniformMatrix4fv(glTransformationMatrixLocation,1,GL_TRUE,mat);
}
void setProjectionMatrix(float* mat)
{
  glUniformMatrix4fv(glProjectionMatrixLocation,1,GL_TRUE,mat);
}
