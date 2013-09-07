#include <stdio.h>
#include <shadow.h>
#include <graphics.h>

ShadowManager::ShadowManager()
{
  maxShadowDistance = 1200;
  minShadowDistance = 800;
  shadowBoxSize = 100;

	GLenum FBOstatus;
	
	// Try to use a texture depth component
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
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texID, 0);
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
  projMatrix[0] = 1.0/shadowBoxSize;
  projMatrix[1] = 0;
  projMatrix[2] = 0;
  projMatrix[3] = 0;

  projMatrix[4] = 0;
  projMatrix[5] = 1.0/shadowBoxSize;
  projMatrix[6] = 0;
  projMatrix[7] = 0;

  projMatrix[8] = 0;
  projMatrix[9] = 0;
  // 4096 is the maximum distance
  projMatrix[10] = -1.0/(maxShadowDistance-minShadowDistance);

  projMatrix[11] = -minShadowDistance/(maxShadowDistance-minShadowDistance);

  projMatrix[12] = 0;
  projMatrix[13] = 0;
  projMatrix[14] = 0;
  projMatrix[15] = 1;


  shader = new ShaderProgram();
  shader->LoadShader("../shaders/vertexShadowShader.shd", GL_VERTEX_SHADER);
  shader->LoadShader("../shaders/fragmentShadowShader.shd", GL_FRAGMENT_SHADER);
  shader->CompileAll();
  shader->setMatrix("projectionMatrix",&projMatrix[0]);
  camera = new Camera(shader,"transformationMatrix");
  camera->Position = Vector3(0,200,0);
  camera->RotateX(-3.1415/2);
  sinceLastRefresh = 10000;
  theta = 0;
}

int oldViewport[4];

bool ShadowManager::readyForWriting(int refreshTime)
{
  sinceLastRefresh += refreshTime;
  if (sinceLastRefresh<2000)
    return false;
  shader->Load();
  glGetIntegerv(GL_VIEWPORT,oldViewport);
  glViewport(0,0,TEXTURE_SIZE,TEXTURE_SIZE);
  shader->setMatrix("projectionMatrix",&projMatrix[0]);
  shader->setInt("otherTexture",3);
  camera->Render();
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboID);	//Rendering offscreen
  glActiveTexture(GL_TEXTURE7);
  glBindTexture(GL_TEXTURE_2D,texID);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  sinceLastRefresh = 0;
  return true;
}

void ShadowManager::readyForReading(ShaderProgram* mainShader)
{
  glActiveTexture(GL_TEXTURE7);
  glBindTexture(GL_TEXTURE_2D,texID);
  mainShader->Load();
  mainShader->setMatrix("lightTransformMatrix",camera->getTransformationMatrix());
  mainShader->setMatrix("lightProjectionMatrix",&projMatrix[0]);
  mainShader->setInt("shadowTexture",7);
  mainShader->setInt("otherTexture",3);
  glViewport(oldViewport[0],oldViewport[1],oldViewport[2],oldViewport[3]);
}

void ShadowManager::relocate(Vector3 newPos, int refreshTime)
{
  theta += refreshTime / 1000.0 *3.1415*2*2.0/600.0;
  camera->Position.x = newPos.x + 1000*sin(theta);
  camera->Position.y = newPos.y + 1000*cos(theta);
  camera->Position.z = newPos.z;
  camera->ViewDir = (newPos-camera->Position).normal();
}
