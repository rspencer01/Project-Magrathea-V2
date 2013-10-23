#include <stdio.h>
#include <images.h>

/// Genertate a new texture from scratch
GLuint newTexture()
{
  GLuint returnValue;
  glGenTextures(1,&returnValue);
	glBindTexture(GL_TEXTURE_2D,returnValue);

  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );

  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

  return returnValue;
}

GLuint textureFromBMP(const char* filePath)
{
	printf("Loading texture %s\n",filePath);
	FILE* fp = fopen(filePath,"rb");
	int width,height;
	GLuint returnValue = newTexture();
	fseek(fp,0x12,0);
	fread(&width,4,1,fp);
	fseek(fp,0x16,0);
	fread(&height,4,1,fp);

	char* data = new char[width*height*3];
	fseek(fp,0x36,0);
	fread(data,1,width*height*3,fp);
  
  char* rgbaData = new char[width*height*4];
  for (int i = 0;i<width*height;i++)
  {
    rgbaData[i*4 ]   = data[i*3];
    rgbaData[i*4 +1] = data[i*3+1];
    rgbaData[i*4 +2] = data[i*3+2];
    rgbaData[i*4 +3] = 255;
    if ((rgbaData[i*4]==-1) && (rgbaData[i*4+2]==-1) &&(rgbaData[i*4+2]==0))
      rgbaData[i*4+3] = 0;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData);
	delete data;
  delete rgbaData;
	fclose(fp);

	return returnValue;
}

GLuint textureFromRAW(const char* filePath)
{
	printf("Loading texture %s\n",filePath);
	FILE* fp = fopen(filePath,"rb");
	int width,height;
	GLuint returnValue = newTexture();
	width = height = 1024;
	char* data = new char[width*height*3];
	fread(data,1,width*height*3,fp);
  
  char* rgbaData = new char[width*height*4];
  for (int i = 0;i<width*height;i++)
  {
    rgbaData[i*4 ]   = data[i*3];
    rgbaData[i*4 +1] = data[i*3+1];
    rgbaData[i*4 +2] = data[i*3+2];
    rgbaData[i*4 +3] = 255;
    if ((rgbaData[i*4]==-1) && (rgbaData[i*4+2]==-1) &&(rgbaData[i*4+2]==0))
      rgbaData[i*4+3] = 0;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData);
	delete data;
  delete rgbaData;
	fclose(fp);

	return returnValue;
}


GLuint textureFromTGA(const char* filePath)
{
	printf("Loading texture %s\n",filePath);
	FILE* fp = fopen(filePath,"rb");
  unsigned char inp;
  fseek(fp,2,0);
  fread(&inp,1,1,fp);
  unsigned short width;
  unsigned short height;
  fseek(fp,12,0);
  fread(&inp,1,1,fp);
  width = inp;
  fread(&inp,1,1,fp);
  width += inp<<8;
  fread(&inp,1,1,fp);
  height = inp;
  fread(&inp,1,1,fp);
  height += inp<<8;

  fread(&inp,1,1,fp);
  if (inp!=32)
  {
    fprintf(stderr,"Error loading texture:  All TGA files must be 32 bit.\n");
    return -1;
  }
  fread(&inp,1,1,fp);

  char* rgbaData = new char[width*height*4];
  fread(rgbaData,4,height*width,fp);
  GLuint returnValue = newTexture();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData);

  delete rgbaData;
	fclose(fp);

	return returnValue;

}