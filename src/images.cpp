#include <stdio.h>
#include <images.h>

GLuint textureFromBMP(char* filePath)
{
	printf("Loading texture %s\n",filePath);
	FILE* fp = fopen(filePath,"rb");
	int width,height;
	GLuint returnValue;
	fseek(fp,0x12,0);
	fread(&width,4,1,fp);
	fseek(fp,0x16,0);
	fread(&height,4,1,fp);

	glGenTextures(1,&returnValue);
	glBindTexture(GL_TEXTURE_2D,returnValue);

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	char* data = new char[width*height*3];
	fseek(fp,0x36,0);
	fread(data,1,width*height*3,fp);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	delete data;
	fclose(fp);

	return returnValue;
}