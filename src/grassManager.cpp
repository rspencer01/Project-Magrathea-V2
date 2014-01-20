#include <grassManager.h>

GrassManager::GrassManager(Game* parent)
{
  game = parent;
  shader = new ShaderProgram();
  shader->LoadShader("../shaders/grassVertexShader.shd", GL_VERTEX_SHADER);
  shader->LoadShader("../shaders/grassFragmentShader.shd", GL_FRAGMENT_SHADER);
  // Compile and load them
  shader->CompileAll();
  shader->Load();
  vertexData = new VertexDatum[GRASS_SIZE*GRASS_SIZE];
  for (int i = 0;i<GRASS_SIZE;i++)
    for (int j = 0;j<GRASS_SIZE;j++)
    {
      vertexData[i*GRASS_SIZE+j].colour = glm::vec4(0,0,0,1);
      vertexData[i*GRASS_SIZE+j].normal = glm::vec3(0,1,0);
      vertexData[i*GRASS_SIZE+j].position = glm::vec3(i,0,j);
      vertexData[i*GRASS_SIZE+j].texMix = glm::vec4(-1);
      vertexData[i*GRASS_SIZE+j].texture = glm::vec2(-1);
    }
  glGenBuffersARB(1,&vertexPositionBO);
  glBindBufferARB(GL_ARRAY_BUFFER,vertexPositionBO);
  glBufferDataARB(GL_ARRAY_BUFFER, GRASS_SIZE*GRASS_SIZE*sizeof(VertexDatum),vertexData,GL_STATIC_DRAW);
}

void GrassManager::Render(int,glm::vec3)
{
  shader->Load();
  glBindBufferBase(GL_UNIFORM_BUFFER,1,game->mainShader->frameDataBO);
  glBindBufferARB(GL_ARRAY_BUFFER,vertexPositionBO);
  glVertexAttribPointerARB(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),0);
  glVertexAttribPointerARB(1,4,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(3*sizeof(float)));
  glVertexAttribPointerARB(2,2,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(10*sizeof(float)));
  glVertexAttribPointerARB(3,3,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(7*sizeof(float)));
  glVertexAttribPointerARB(4,4,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(12*sizeof(float)));
  glDrawArrays(GL_POINTS,0,GRASS_SIZE*GRASS_SIZE);
  game->mainShader->Load();
}