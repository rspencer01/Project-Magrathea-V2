#include <GL/glew.h>
#include <GL/glut.h>

#include <fstream>
#include <string>
#include <vector>
#include <sstream>


#include <stdio.h>
#include <object.h>


/// @param pos The position of this object in gamespace
/// @param g   The game to which this object belongs
Object::Object(Vector3 pos,Game* g)
{
  position = pos;
  game = g;
  buffersInitialised = false;
  vertexData = NULL;
  triDat = NULL;
  textureNumber = -1;
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
Vector3 Object::getPosition()
{
  return position;
}

void Object::setPosition(Vector3 pos)
{
  position = pos;
}


/// Renders this object to the screen, using the VBOs that were 
/// initialised using the addPoint, addTriangle and pushTriangleData
/// functions
void Object::Render()
{
  // Only do something if we have data	
	if (buffersInitialised)
	{
   /* glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureNumber);*/
    glEnableVertexAttribArrayARB(0);
    glEnableVertexAttribArrayARB(1);
    glEnableVertexAttribArrayARB(2);
    glEnableVertexAttribArrayARB(3);

    glBindBufferARB(GL_ARRAY_BUFFER,vertexVBO);
    // Get the position data
    glVertexAttribPointerARB(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),0);
    glVertexAttribPointerARB(1,4,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(3*sizeof(float)));
    glVertexAttribPointerARB(2,2,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(10*sizeof(float)));
    glVertexAttribPointerARB(3,3  ,GL_FLOAT,GL_FALSE,sizeof(VertexDatum),(void*)(7*sizeof(float)));
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,indexVBO);
    glDrawElements(GL_TRIANGLES,numberOfTriangles*3,GL_UNSIGNED_INT,0);
    glDisableVertexAttribArrayARB(0);
    glDisableVertexAttribArrayARB(1);
    glDisableVertexAttribArrayARB(2);
    glDisableVertexAttribArrayARB(3);
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
    delete triDat;
  if (vertexData!=NULL)
    delete vertexData;
  triDat = new int[t*3];
  vertexData = new VertexDatum[p];
  if (buffersInitialised)
  {
  	glDeleteBuffersARB(1,&vertexVBO);
	  glDeleteBuffersARB(1,&indexVBO);
  }
  numberOfTriangles = t;
  numberOfPoints = p;
}
/// Add a new point to the object.  All points are taken relative to the origin of the object
/// @param i The index of the vertex to change
/// @param point The position of this point, relative to the object origin
/// @param r The red component of the colour
/// @param b The blue component of the colour
/// @param g The green component of the colour
void Object::addPoint(int i,Vector3 point,Vector3 normal, float r, float g, float b)
{
	// Point is relative to the position of the object
	point = point + position;
  // Add it to the internal array
	vertexData[i].px = point.x;
	vertexData[i].py = point.y;
	vertexData[i].pz = point.z;
	vertexData[i].nx = normal.x;
	vertexData[i].ny = normal.y;
	vertexData[i].nz = normal.z;
	vertexData[i].red = r;
	vertexData[i].green = g;
	vertexData[i].blue = b;
  vertexData[i].alpha = 1.f;

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
	// Now make a buffers
	glGenBuffersARB(1,&vertexVBO);
	// set it as the current one,
	glBindBufferARB(GL_ARRAY_BUFFER, vertexVBO);
	// ... and blit the data in.
	glBufferDataARB(GL_ARRAY_BUFFER, numberOfPoints*sizeof(VertexDatum),vertexData,GL_STATIC_DRAW);

	// Now make a buffer...
	glGenBuffersARB(1,&indexVBO);
	// set it as the current one,
	glBindBufferARB(GL_ARRAY_BUFFER, indexVBO);
	// ... and blit the data in.
	glBufferDataARB(GL_ARRAY_BUFFER, numberOfTriangles*3*sizeof(int),triDat,GL_STATIC_DRAW);

	// Finally set the variables that need setting
	buffersInitialised = true;
}

void Object::updateTriangleData()
{
  glBindBufferARB(GL_ARRAY_BUFFER,vertexVBO);
  glBufferSubDataARB(GL_ARRAY_BUFFER,0,numberOfPoints*sizeof(VertexDatum),vertexData);
}

void Object::editTextureCoord(int i, float u, float v)
{
	vertexData[i].texx = u;
	vertexData[i].texy = v;
}


void Object::loadFromOBJFile(const char* filePath)
{
  /*
  // Let the user know what we are doing
  printf("Loading model from \"%s\"\n",filePath);
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
      iss>>vertexData[vertexCount].px>>vertexData[vertexCount].py>>vertexData[vertexCount].pz;
      // Make this thing coloured
      vertexData[vertexCount].red = vertexData[vertexCount].blue = vertexData[vertexCount].green = vertexData[vertexCount].alpha = 1.f; 
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
      std::vector<int> tmp;tmp.push_back(fx);tmp.push_back(fy);tmp.push_back(fz);
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
  printf("File has %d vertices and %d triangles\n",numberOfPoints,numberOfTriangles);
	triDat = new int[numberOfTriangles*3];
	for (int i = 0; i<numberOfTriangles;i++)
		addTriangle(i,tri[i][0]-1,tri[i][1]-1,tri[i][2]-1);
	pushTriangleData();
  */
}
