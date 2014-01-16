#include <testobj.h>
#include <images.h>
#include <cmath>
#include <gtx\random.hpp>
#include <gtc\noise.hpp>

Water::Water(glm::vec3 pos,Game* parent) : Object(pos,parent)
{
  int waterSize = 600;
  int detail = 1;
  textureNumber = textureFromTGA("../assets/water.tga",true);
  clearTriangleData((waterSize+1)*(waterSize+1),waterSize*waterSize*2);
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<(waterSize+1);y++)
		for (int x = 0; x<(waterSize+1);x++)
		{
      addPoint(y*(waterSize+1)+x,
               glm::vec3((float)x*detail,
                       0,
			                 (float)y*detail),
                       glm::vec3(0,1,0),
                       1,1,1);
      editTextureCoord(y*(waterSize+1)+x,4.f*x/(waterSize+1),4.f*y/(waterSize+1));
		}
	
  // Populate one triangle (for now) per block
	for (int y = 0; y<waterSize;y++)
		for (int x = 0; x<waterSize;x++)
		{
      addTriangle((y*waterSize+x)*2,
                  y*(waterSize+1) + x,
			            (y+1)*(waterSize+1) + x,
			            y*(waterSize+1) + (x+1));
      addTriangle((y*waterSize+x)*2+1,
                  y*(waterSize+1) + x+1,
			            (y+1)*(waterSize+1) + x,
			            (y+1)*(waterSize+1) + (x+1));
		}
  pushTriangleData();
  objectData.shinyness = 0.05;
  objectData.objectColour[3] = 0.7;
  objectData.objectType = OT_WATER;
  updateObjectBO();
  reflectiveTexture = textureFromTGA("../assets/MixedGround.tga",false);

	GLenum FBOstatus;
	
	// Try to use a texture depth component
  glActiveTexture(GL_TEXTURE4);
	glGenTextures(1, &reflectiveTexture);
	glBindTexture(GL_TEXTURE_2D, reflectiveTexture);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_FLOAT, 0);
	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	
	// create a framebuffer object
	glGenFramebuffersEXT(1, &reflectiveBuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, reflectiveBuffer);
	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, reflectiveTexture, 0);

  // create the depthbuffer
  glGenRenderbuffersEXT(1,&reflectiveDepthBuffer);
  glBindRenderbufferEXT(GL_RENDERBUFFER,reflectiveDepthBuffer);
  glRenderbufferStorageEXT(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,1024,1024);
  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,GL_DEPTH_ATTACHMENT_EXT,GL_RENDERBUFFER_EXT,reflectiveDepthBuffer);
	// check FBO status
	FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE)
		DIE("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");
	
	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

}

void Water::Render(int refreshTime, glm::vec3 cameraPos)
{
  // Save our viewport
  glGetIntegerv(GL_VIEWPORT,oldViewport);
  // Set the viewport to be the size of the texture
  glViewport(0,0,1024,1024);

  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,reflectiveBuffer);
  glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_2D,reflectiveTexture);
  // ... which we clear
  glClearColor(0.0,0.0,1.0,1);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // Talk about the correct texture
  glActiveTexture(GL_TEXTURE3);
  game->mainShader->frameData.cullLevel = position.y;
  game->mainShader->frameData.isReflection = 1;
  game->mainShader->setFrameData();
  game->sky->Render(0,game->camera->Position);
  game->RenderScene(0);
  game->mainShader->frameData.cullLevel = -1000000;
  game->mainShader->frameData.isReflection = 0;
  game->mainShader->setFrameData();
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);

  glViewport(oldViewport[0],oldViewport[1],oldViewport[2],oldViewport[3]);
  glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_2D,reflectiveTexture);
  glActiveTexture(GL_TEXTURE3);
  Object::Render(refreshTime,cameraPos);
}