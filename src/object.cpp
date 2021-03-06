#include <GL/glew.h>
#include <GL/glut.h>

#include <fstream>
#include <string>
#include <vector>
#include <sstream>


#include <stdio.h>
#include <object.h>
#include <game.h>


/// @param pos The position of this object in gamespace
/// @param g   The game to which this object belongs
Object::Object(glm::vec3 pos,Game* g)
{
  position = pos;
  game = g;
  buffersInitialised = false;
  vertexData = NULL;
  triDat = NULL;
  textureNumber = 0;
  billboard = false;
  forward = glm::vec3(1,0,0);
  up = glm::vec3(0,1,0);
  right = glm::vec3(0,0,1);
  xySlew = 0;
  glGenBuffers(1, &objectBO);
  VAO = (GLuint)-1;
  objectData.objectColour = glm::vec4(1);
  objectData.shinyness = 0.000001;
  objectData.isGrassy = 0;
  objectData.objectType = OT_STANDARD_OBJECT;
  updateMatrix();
}

/// Frees the data used by this object (esp the buffers in the GPU)
Object::~Object()
{
  if (vertexData!=NULL)
    delete vertexData;
  if (triDat!=NULL)
    delete triDat;
  if (buffersInitialised)
  {
  	glDeleteBuffersARB(1,&vertexVBO);
  	glDeleteBuffersARB(1,&indexVBO);
  }
}

/// Accesses the position of this object
glm::vec3 Object::getPosition()
{
  return position;
}

/// Changes the position of the object.
void Object::setPosition(glm::vec3 pos)
{
  position = pos;
  updateMatrix();
}

/// Renders this object to the screen, using the VBOs that were 
/// initialised using the addPoint, addTriangle and pushTriangleData
/// functions
/// @param refreshTime Number of milliseconds since the last rendering
/// @param cameraPos   Position of the camera in 3-space
void Object::Render(int refreshTime, glm::vec3 cameraPos)
{
  // Rotate the object if it is a billboard
  if (billboard)
  {
    right = glm::cross(glm::normalize(cameraPos-position),up);
    forward = glm::cross(up,right);
    updateMatrix();
  }
  // Only do something if we have data	(THIS IS THE MAIN BOTTLENECK!)
	if (buffersInitialised)
	{
    // Load our transformation matrix etc
    game->mainShader->setObjectData(objectBO);
    // Select this object's texture
    glBindTexture(GL_TEXTURE_2D,textureNumber);
    // Use our data

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,numberOfTriangles*3,GL_UNSIGNED_INT,0);
  }
}

/// Reset the data.  Clear the internal arrays, and the GPU arrays.
/// Reserve space for p point and t triangles
/// @param p Number of points
/// @param t Number of triangles
void Object::clearTriangleData(int p, int t)
{
  // Clear all the data and the buffers (if required)
  if (triDat!=NULL)
  { 
    delete triDat;
    triDat = NULL;
  }
  if (vertexData!=NULL)
  {
    delete vertexData;
    vertexData = NULL;
  }
  triDat = new int[t*3];
  vertexData = new VertexDatum[p];
  if (buffersInitialised)
  {
  	glDeleteBuffersARB(1,&vertexVBO);
	  glDeleteBuffersARB(1,&indexVBO);
  }
  numberOfTriangles = t;
  numberOfPoints = p;
  // Now make buffers
	glGenBuffersARB(1,&indexVBO);
  glGenBuffersARB(1,&vertexVBO);
}
/// Add a new point to the object.  All points are taken relative to the origin of the object
/// @param i The index of the vertex to change
/// @param point The position of this point, relative to the object origin
/// @param r The red component of the colour
/// @param b The blue component of the colour
/// @param g The green component of the colour
void Object::addPoint(int i,glm::vec3 point,glm::vec3 normal, float r, float g, float b)
{
  // Add it to the internal array
	vertexData[i].position = point;
	vertexData[i].normal = normal;
	vertexData[i].colour = glm::vec4(r,g,b,1);
  vertexData[i].texMix = glm::vec4(-1);
}


void Object::setTextureMix(int point,float a, float b, float c, float d)
{
  vertexData[point].texMix = glm::vec4(a,b,c,d);
}

/// Adds a new triangle to the object.  Indexes are the same as the order the points were added
/// @param i The index of the triangle to edit
/// @param a The index of the first point
/// @param b The index of the second point
/// @param c The index of the third point
void Object::addTriangle(int i, int a,int b, int c)
{
  // Add it to the internal array
	triDat[i*3] = a;
	triDat[i*3+1] = b;
	triDat[i*3+2] = c;
}

/// Constructs new VBOs and pushes all the data to the GPU
void Object::pushTriangleData()
{
  // Make our VAO.  Not sure why leaving this out stops the first region from rendering... does the vao need to know about glBufferData?
  if (VAO==(GLuint)-1)
    glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);
	// set it as the current one,
	glBindBufferARB(GL_ARRAY_BUFFER, vertexVBO);
	// ... and blit the data in.
	glBufferDataARB(GL_ARRAY_BUFFER, numberOfPoints*sizeof(VertexDatum),vertexData,GL_STATIC_DRAW);

	// set it as the current one,
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	// ... and blit the data in.
  glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, numberOfTriangles*3*sizeof(int),triDat,GL_STATIC_DRAW);
  
  updateVAO();
	// Finally set the variables that need setting
	buffersInitialised = true;
}

void Object::updateVAO()
{
  if (VAO==(GLuint)-1)
    glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);
  glBindBufferARB(GL_ARRAY_BUFFER,vertexVBO);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointerARB(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointerARB(1,4,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointerARB(2,2,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(10*sizeof(float)));
  glEnableVertexAttribArray(3);
  glVertexAttribPointerARB(3,3,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(7*sizeof(float)));
  glEnableVertexAttribArray(4);
  glVertexAttribPointerARB(4,4,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(12*sizeof(float)));
  glBindVertexArray(0);
}

void Object::updateTriangleData()
{

  glDeleteBuffersARB(1,&vertexVBO);
  glGenBuffersARB(1,&vertexVBO);
  glBindBufferARB(GL_ARRAY_BUFFER,vertexVBO);
  glBufferDataARB(GL_ARRAY_BUFFER, numberOfPoints*sizeof(VertexDatum),vertexData,GL_STATIC_DRAW);

  updateVAO();
}

void Object::editTextureCoord(int i, float u, float v)
{
	vertexData[i].texture = glm::vec2(u,v);
}

/// Rotates the object to match the given new axis
/// @param basisX The new X axis
/// @param basisY The new Y axis
void Object::rotate(glm::vec3 basisX,glm::vec3 basisY)
{
  forward = glm::normalize(basisX);
  up = glm::normalize(basisY);
  right = glm::normalize(glm::cross(up,forward));
  updateMatrix();
}

/// Sets the global object colour
void Object::setColour(glm::vec4 col)
{
  objectData.objectColour = col;
  updateObjectBO();
}

/// Updates the object translation and rotation matrix
void Object::updateMatrix()
{
  // This works.  You can check it yourself.
  objectData.transformMatrix = glm::mat4(glm::vec4(forward,0),
                                         glm::vec4(up,0) + glm::vec4(xySlew,0,0,0),
                                         glm::vec4(right,0),
                                         glm::vec4(position,1));
  updateObjectBO();
}

/// WARNING: Only call this function if you are sure that you will never 
/// edit the vertices again.  That will cause a seg fault
/// Only to be called after the triangle data has been set of an object
/// that is either massive, or very common and that will never animate
/// (eg trees)
void Object::freeze()
{
  if (triDat!=NULL)
  {
    delete[] triDat;
    triDat = NULL;
  }
  if (vertexData!=NULL)
  {
    delete[] vertexData;
    vertexData = NULL;
  }
}

void Object::updateObjectBO()
{
  
  glBindBuffer(GL_UNIFORM_BUFFER, objectBO);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(objectData), &objectData, GL_DYNAMIC_DRAW);
}


void Object::loadFromOBJFile(const char* filePath)
{
  // Let the user know what we are doing
  logi.log("Loading model from \"%s\"",filePath);
  // Do all the stuff to set this up as new
  if (triDat!=NULL)
    delete triDat;
  if (vertexData!=NULL)
    delete vertexData;
  if (buffersInitialised)
  {
  	glDeleteBuffersARB(1,&vertexVBO);
    glDeleteBuffersARB(1,&indexVBO);
  }
  
  // Get the input stream
  std::ifstream infile(filePath);
  std::string line;
  // Count the vertices to allocate enough space
  numberOfPoints = 0;
  while (std::getline(infile, line))
  {
    if (line.length()>2)
    {
	    if (line[0]=='v' && line[1]==' ')
		    numberOfPoints++;
    }
  }
  // Allocate the vertex space
  vertexData = new VertexDatum[numberOfPoints];
  // Vectors of vectors to hold triangles and normals
  std::vector<std::vector<int> > tri;
  std::vector<std::vector<int> > norm;
  std::vector<std::pair<float,float> > textures;
  // What vertex are we on now
  int vertexCount = 0;
  // Now iterate through the file
  infile.close();
  infile.open(filePath);
  infile.seekg(0,infile.beg);
  while (std::getline(infile, line))
  {
    // Not a valid line
    if (line.length()<3)
      continue;
    // A vertex line
    if (line[0]=='v' && line[1]==' ')
    {
      // Parse this string
      std::istringstream iss(line.substr(2,100));
      // x,y,z space separated
      iss>>vertexData[vertexCount].position.x>>vertexData[vertexCount].position.y>>vertexData[vertexCount].position.z;
      // Make this thing coloured
      vertexData[vertexCount].colour = glm::vec4(1); 
      vertexCount++;
    }
    // A normal
    if (line[0]=='v' && line[1]=='n')
    {
      // Parse this string
      std::istringstream iss(line.substr(3,100));
      float fx,fy,fz;
      // x,y,z space separated
      iss>>fx>>fy>>fz;
      std::vector<int> tmp;tmp.push_back((int)fx);tmp.push_back((int)fy);tmp.push_back((int)fz);
      norm.push_back(tmp);
    }
    // Texture coords
    if (line[0]=='v' && line[1]=='t')
    {
      // Parse this string
      std::istringstream iss(line.substr(2,100));
      float fx,fy;
      // x,y,z space separated
      iss>>fx>>fy;
      textures.push_back(std::make_pair(fx,fy));
    }
    if (line[0]=='f' && line[1]==' ')
    {
			line = line.substr(2,100);
			int a = -1;
			int b = -1;
			int c = -1;
      int ta,tb,tc;
			while (line.length()>0)
			{
				int nsp = line.find(' ',0);
				std::string t = line.substr(0,nsp);
				if (a==-1)
				{
					a = atoi(t.substr(0,t.find('\\')).c_str());
          ta = atoi(t.substr(t.find('\\')+1,t.find('\\')).c_str());
				}
				else
				{
					if (b==-1)
					{
						b = atoi(t.substr(0,t.find('\\')).c_str());
            tb = atoi(t.substr(t.find('\\')+1,t.find('\\')).c_str());
					}
					else
					{
						if (c==-1)
						{
							c = atoi(t.substr(0,t.find('\\')).c_str());
              tc = atoi(t.substr(t.find('\\')+1,t.find('\\')).c_str());
						}
						else
						{
							b = c;
              tb = c;
							c = atoi(t.substr(0,t.find('\\')).c_str());
              tc = atoi(t.substr(t.find('\\')+1,t.find('\\')).c_str());
						}
						std::vector<int> p;p.push_back(a);p.push_back(b);p.push_back(c);
            editTextureCoord(a,textures[ta].first,textures[ta].second);
            editTextureCoord(b,textures[tb].first,textures[tb].second);
            editTextureCoord(c,textures[tc].first,textures[tc].second);
						tri.push_back(p);
					}
				}
				if (nsp==-1)
					break;
				line = line.substr(nsp+1,100);
			}

    }

  }
  numberOfTriangles = tri.size();
  logi.log("File has %d vertices and %d triangles",numberOfPoints,numberOfTriangles);
	triDat = new int[numberOfTriangles*3];
	for (int i = 0; i<numberOfTriangles;i++)
		addTriangle(i,tri[i][0]-1,tri[i][1]-1,tri[i][2]-1);
	pushTriangleData();
}
