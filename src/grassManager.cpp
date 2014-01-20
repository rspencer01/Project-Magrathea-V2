#include <grassManager.h>

GrassManager::GrassManager(Game* parent)
{
  game = parent;
  shader = new ShaderProgram();
  /*
  shader->LoadShader("../shaders/grassVertexShader.shd", GL_VERTEX_SHADER);
  shader->LoadShader("../shaders/grassGeometryShader.shd", GL_GEOMETRY_SHADER);
  shader->LoadShader("../shaders/grassFragmentShader.shd", GL_FRAGMENT_SHADER);
  // Compile and load them
  shader->CompileAll();
  shader->Load();
  */
}

void GrassManager::Render(int,glm::vec3)
{
}