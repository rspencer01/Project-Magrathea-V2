#include <gl\glew.h>
#include <gl\glut.h>
#include <stdio.h>
#include <shaders.h>

static const char* pFS = "                                                    \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 FragColor;                                                           \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);                                     \n\
}";

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
}  


void loadShaders()
{
  printf("Initialising shaders\n");
  CompileShaders();
}