#include <grassManager.h>
#include <gtc\noise.hpp>

GrassManager::GrassManager(Game* parent)
{
  printf("New grass manager\n");
  game = parent;
  shader = new ShaderProgram();
  shader->LoadShader("../shaders/grassVertexShader.shd", GL_VERTEX_SHADER);
  shader->LoadShader("../shaders/grassGeometryShader.shd", GL_GEOMETRY_SHADER);
  shader->LoadShader("../shaders/grassFragmentShader.shd", GL_FRAGMENT_SHADER);
  // Compile and load them
  shader->CompileAll();
  shader->Load();
  vertexData = new VertexDatum[GRASS_SIZE*GRASS_SIZE];
  for (int i = 0;i<GRASS_SIZE;i++)
    for (int j = 0;j<GRASS_SIZE;j++)
    {
      terrainBit a = game->getTerrainBit(int(i*0.3f),int(j*0.3f));
      terrainBit b = game->getTerrainBit(int(i*0.3f),int(j*0.3f)+1);
      terrainBit c = game->getTerrainBit(int(i*0.3f)+1,int(j*0.3f));
      terrainBit d = game->getTerrainBit(int(i*0.3f)+1,int(j*0.3f)+1);
      terrainBit h;
      h.position = glm::mix(glm::mix(a.position,b.position,j*0.3f-int(j*0.3f)),
                            glm::mix(c.position,d.position,j*0.3f-int(j*0.3f)),i*0.3f-int(i*0.3f));
      float grassyness = (1.f-i*0.3f+int(i*0.3f))*
                         ((1.f-j*0.3f+int(j*0.3f))*(a.type==grass)+
                         (j*0.3f-int(j*0.3f))*(b.type==grass))+
                         (i*0.3f-int(i*0.3f))*
                         ((1.f-j*0.3f+int(j*0.3f))*(c.type==grass)+
                         (j*0.3f-int(j*0.3f))*(d.type==grass))
                         ;

      vertexData[i*GRASS_SIZE+j].colour = glm::vec4(0.2,0.4,0.13,1);
      vertexData[i*GRASS_SIZE+j].normal = glm::vec3(0,1,0);
      vertexData[i*GRASS_SIZE+j].position = glm::vec3(i*0.3f,
                                                     h.position.y,
                                                     j*0.3f);
      vertexData[i*GRASS_SIZE+j].texMix = glm::vec4(grassyness);
      vertexData[i*GRASS_SIZE+j].texture = glm::vec2(-1);
    }
  glGenBuffersARB(1,&vertexPositionBO);
  glBindBufferARB(GL_ARRAY_BUFFER,vertexPositionBO);
  glBufferDataARB(GL_ARRAY_BUFFER, GRASS_SIZE*GRASS_SIZE*sizeof(VertexDatum),vertexData,GL_STATIC_DRAW);
}

void GrassManager::Render(int,glm::vec3)
{
  shader->Load();
  glBindBufferBase(GL_UNIFORM_BUFFER,1,game->mainShader->getFrameDataBufferNumber());
  glBindBufferARB(GL_ARRAY_BUFFER,vertexPositionBO);
  glVertexAttribPointerARB(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),0);
  glVertexAttribPointerARB(1,4,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(3*sizeof(float)));
  glVertexAttribPointerARB(2,2,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(10*sizeof(float)));
  glVertexAttribPointerARB(3,3,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(7*sizeof(float)));
  glVertexAttribPointerARB(4,4,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(12*sizeof(float)));
  glDrawArrays(GL_POINTS,0,GRASS_SIZE*GRASS_SIZE);
  game->mainShader->Load();
}