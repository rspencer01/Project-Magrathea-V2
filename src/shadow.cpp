#include <stdio.h>
#include <math.h>
#include <shadow.h>
#include <graphics.h>

ShadowManager::ShadowManager(ShaderProgram* mainShader)
{
  shader = mainShader;

  maxShadowDistance = 1200;
  minShadowDistance = 800;
  shadowBoxSize = 100;

	GLenum FBOstatus;
	
	// Try to use a texture depth component
  glActiveTexture(GL_TEXTURE7);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	
	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	// Remove artefact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	
	// No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available 
  glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, TEXTURE_SIZE, TEXTURE_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// create a framebuffer object
	glGenFramebuffersEXT(1, &fboID);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboID);

	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texID, 0);
	// Instruct openGL that we won't bind a color texture with the currently binded FBO
	glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
	
	// check FBO status
	FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE)
		printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");
	
	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

  //BuildPerspProjMat(projMatrix,10,1,3,100);
  projMatrix[0] = 1.f/shadowBoxSize;
  projMatrix[4] = 0;
  projMatrix[8] = 0;
  projMatrix[12] = 0;

  projMatrix[1] = 0;
  projMatrix[5] = 1.f/shadowBoxSize;
  projMatrix[9] = 0;
  projMatrix[13] = 0;

  projMatrix[2] = 0;
  projMatrix[6] = 0;
  // 4096 is the maximum distance
  projMatrix[10] = -1.f/(maxShadowDistance-minShadowDistance);

  projMatrix[14] = -minShadowDistance/(maxShadowDistance-minShadowDistance);

  projMatrix[3] = 0;
  projMatrix[7] = 0;
  projMatrix[11] = 0;
  projMatrix[15] = 1;

  camera = new Camera(shader->frameData.lightCameraMatrix,shader->frameData.cameraPos);
  camera->setPosition(glm::vec3(0.f,200.f,0.f));
  camera->RotateX(-3.1415f/2);

  // Set the shadow texture to this one's texture
  glActiveTexture(GL_TEXTURE7);
  glBindTexture(GL_TEXTURE_2D,texID);
  // And set the shadow projection matrix

  memcpy(shader->frameData.lightProjectionMatrix,projMatrix,16*sizeof(float));
  theta = 0.2;
}

/// Prepare the shadow manager for writing to the shadow texture.
void ShadowManager::readyForWriting(int refreshTime)
{
  // Save our viewport
  glGetIntegerv(GL_VIEWPORT,oldViewport);
  // Set the viewport to be the size of the texture
  glViewport(0,0,TEXTURE_SIZE,TEXTURE_SIZE);
  shader->frameData.viewHeight = TEXTURE_SIZE;
  shader->frameData.viewWidth = TEXTURE_SIZE;
  // Tell the shader we are rendering shadows
  shader->frameData.isShadow = 1;
  // Set the camera matrix
  camera->Render();
  shader->setFrameData();
  // Render offscreen to the texture...
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboID);
  glActiveTexture(GL_TEXTURE7);
  glBindTexture(GL_TEXTURE_2D,texID);
  // ... which we clear
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // Talk about the correct texture
  glActiveTexture(GL_TEXTURE3);
}

void ShadowManager::readyForReading(ShaderProgram* mainShader)
{
  // We are not rendering shadows anymore
  shader->frameData.isShadow = 0;
  shader->setFrameData();
  // We will use the old viewport
  glViewport(oldViewport[0],oldViewport[1],oldViewport[2],oldViewport[3]);
  shader->frameData.viewWidth = oldViewport[2];
  shader->frameData.viewHeight = oldViewport[3];
  // Render to the screen
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
}

void ShadowManager::relocate(glm::vec3 newPos, int refreshTime)
{
  theta += refreshTime / 1000.f *3.1415f*2*2.f/600.f;
  camera->setPosition(newPos+1000.f * glm::vec3(sin(theta),cos(theta),0));
  camera->setViewDirection(glm::normalize(newPos-camera->getPosition()));
}
