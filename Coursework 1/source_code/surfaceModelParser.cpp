#include "surfaceModelParser.h"

typedef vector<string> VECSTRING;
typedef vector<Vertex> VECVERTEX;
typedef vector<Polygon> VECPOLYGON;
typedef vector<TextureMapping> VECTEXTURE;

VECVERTEX vertices;
VECPOLYGON polygons;
VECTEXTURE textures;
VECSTRING lines;

VECSTRING getLinesVector() {
  return lines;
}

VECVERTEX getVerticesVector() {
  return vertices;
}

VECPOLYGON getPolygonsVector() {
  return polygons;
}

VECTEXTURE getTexturesVector() {
  return textures;
}

// returns a vector of the lines in the vtk file
VECSTRING getLines(const char * filename) {
  string line;
  ifstream file (filename);
  if(file.is_open()) {
    while(file.good()) {
      getline(file, line);
      lines.push_back(line);
    }
    file.close();
  }
  return lines;
}

//gets the line number of where str first occurs
int getLineNum(string str) {
  int i = 0;
  VECSTRING::iterator it = lines.begin();
  string line = *it;
  char * l = &line[0];
  char * strcopy = &str[0];
  char * token = strtok(l, " ");
  while(strcmp(token, strcopy)) {
    it++;
    i++;
    line = *it;
    l = &line[0];
    token = strtok(l, " ");
  }
  return i;
}

//adds vertices to the vector
void addVertices(string line, int index) {
  int counter = 0;
  char * l = &line[0];
  char * token = strtok(l, " ");
  float x, y, z;
  while(counter < 3) {
    Vertex vertex;
    vertex.index = index;
    x = (float) atof(token);
    vertex.x = x;
    token = strtok(NULL, " ");
    y = (float) atof(token);
    vertex.y = y;
    token = strtok(NULL, " ");
    z = (float) atof(token);
    vertex.z = z;
    vertices.push_back(vertex);
    token = strtok(NULL, " ");
    counter++;
    index++;
  }
}

//gets vertices from the vtk file
void getVertices() {
  string line;
  int start = getLineNum("POINTS") + 1;
  int end = getLineNum("POLYGONS");
  int index = 0;
  for(int i = start; i < end; i++, index += 3) {
    line = lines[i];
    addVertices(line, index);
  }
}

// adds polygons to the vector
void addPolygon(string line) {
  Polygon * polygon = new Polygon();
  char * l = &line[0];
  char * token = strtok(l, " ");  
  token = strtok(NULL, " ");
  int id = atoi(token);
  polygon->first = &vertices[id];
  vertices[id].polygonPointers.push_back(polygon);
  token = strtok(NULL, " ");
  id = atoi(token);
  polygon->second = &vertices[id];
  vertices[id].polygonPointers.push_back(polygon);
  token = strtok(NULL, " ");
  id = atoi(token);
  polygon->third = &vertices[id];
  vertices[id].polygonPointers.push_back(polygon);
  polygons.push_back(*polygon);
}

// gets polygons from the vtk file
void getPolygons() {
  string line;
  int start = getLineNum("POLYGONS") + 1;
  int end = getLineNum("POINT_DATA");
  for(int i = start; i < end; i++) {
    line = lines[i];
    addPolygon(line);
  }
}

VECTEXTURE addTextureMappings(string line, int index) {
  char * l = &line[0];
  int counter = 0;
  char * token = strtok(l, " ");  
  while(counter < 9) {
    TextureMapping textureMapping;
    textureMapping.x = (float) atof(token);
    token = strtok(NULL, " ");
    textureMapping.y = (float) atof(token);
    textureMapping.index = index;
    textures.push_back(textureMapping);
    if(counter < 8) { 
      token = strtok(NULL, " ");
    }
    index++;
    counter++;
  }
}

VECTEXTURE getTextureMappings() {
  string firstline;
  string secondline;
  int start = getLineNum("TEXTURE_COORDINATES") + 1;
  int end = lines.size() - 3;
  int index = 0;
  for(int i = start; i < end; i++, index += 9) {
    firstline = lines[i];
    secondline = lines[++i];
    string textureString = firstline + secondline;
    addTextureMappings(textureString, index);
  }
}

/*
Normal getPolygonNormal(Polygon polygon, VECVERTEX vertices) {
  Vertex v1 = vertices[polygon.first];
  Vertex v2 = vertices[polygon.second];
  Vertex v3 = vertices[polygon.third];
  float vector1[3] = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
  float vector2[3] = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};
  Normal normal;
  normal.x = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
  normal.y = 0.0 - ();
}

Cood getNormal(Cood vec1 , Cood vec2)
{
Cood normal;
normal.x = (vec1.y * vec2.z) - (vec1.y * vec2.z);
normal.y =-((vec1.x * vec2.z) - (vec1.z * vec2.x));
normal.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
return normal;
}
*/

// prints out each line in the input vector
void printLines() {
  for(VECSTRING::iterator it = lines.begin(); it != lines.end(); ++it) {
    cout << *it << endl;
  }
}

// prints out each vertex in the input vector
void printVertices() {
  for(VECVERTEX::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    Vertex vertex = *it;
    cout << vertex.index << ": [" << vertex.x << ", " << vertex.y << ", " << vertex.z << "] adjacent sides: " << vertex.polygonPointers.size() << endl;
  }
}

// prints out each polygon in the input vector
void printPolygons() {
  for(VECPOLYGON::iterator it = polygons.begin(); it != polygons.end(); ++it) {
    Polygon polygon = *it;
    cout << polygon.first->index << " " << polygon.second->index << " " << polygon.third->index << endl;
  }
}

void printTextureMappings() {
  for(VECTEXTURE::iterator it = textures.begin(); it != textures.end(); ++it) {
    TextureMapping texture = *it;
    cout << texture.index << ": [" << texture.x << ", " << texture.y << "]" << endl;
  }
}

int main(void) {
  char * filename = "../data/face.vtk";
  getLines(filename);
  getVertices();
  getPolygons();
  getTextureMappings();
}
