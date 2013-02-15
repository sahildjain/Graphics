#include "surfaceModelParser.h"

using namespace std;

typedef vector<string> VECSTRING;
typedef vector<Vertex> VECVERTEX;
typedef vector<Polygon> VECPOLYGON;
typedef vector<TextureMapping> VECTEXTURE;

// returns a vector of the lines in the vtk file
VECSTRING getLines(const char * filename) {
  VECSTRING lines;
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
int getLineNum(VECSTRING lines, string str) {
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
VECVERTEX addVertices(VECVERTEX vertices, string line, int index) {
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
  return vertices;
}

//gets vertices from the vtk file
VECVERTEX getVertices(VECSTRING lines) {
  string line;
  VECVERTEX vertices;
  int start = getLineNum(lines, "POINTS") + 1;
  int end = getLineNum(lines, "POLYGONS");
  int index = 0;
  for(int i = start; i < end; i++, index += 3) {
    line = lines[i];
    vertices = addVertices(vertices, line, index);
  }
  return vertices;
}

// adds polygons to the vector
VECPOLYGON addPolygon(VECPOLYGON polygons, string line) {
  Polygon polygon;
  char * l = &line[0];
  char * token = strtok(l, " ");  
  token = strtok(NULL, " ");
  polygon.first = atoi(token);
  token = strtok(NULL, " ");
  polygon.second = atoi(token);
  token = strtok(NULL, " ");
  polygon.third = atoi(token);
  polygons.push_back(polygon);
  return polygons;
}

// gets polygons from the vtk file
VECPOLYGON getPolygons(VECSTRING lines) {
  string line;
  VECPOLYGON polygons;
  int start = getLineNum(lines, "POLYGONS") + 1;
  int end = getLineNum(lines, "POINT_DATA");
  for(int i = start; i < end; i++) {
    line = lines[i];
    polygons = addPolygon(polygons, line);
  }
  return polygons;
}

VECTEXTURE addTextureMappings(VECTEXTURE textures, string line, int index) {
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
  return textures;
}

VECTEXTURE getTextureMappings(VECSTRING lines) {
  string firstline;
  string secondline;
  VECTEXTURE textures;
  int start = getLineNum(lines, "TEXTURE_COORDINATES") + 1;
  int end = lines.size() - 3;
  int index = 0;
  for(int i = start; i < end; i++, index += 9) {
    firstline = lines[i];
    secondline = lines[++i];
    string textureString = firstline + secondline;
    textures = addTextureMappings(textures, textureString, index);
  }
    cout << "here" << endl;
  return textures;
}

// prints out each line in the input vector
void printLines(VECSTRING lines) {
  for(VECSTRING::iterator it = lines.begin(); it != lines.end(); ++it) {
    cout << *it << endl;
  }
}

// prints out each vertex in the input vector
void printVertices(VECVERTEX vertices) {
  for(VECVERTEX::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    Vertex vertex = *it;
    cout << vertex.index << ": [" << vertex.x << ", " << vertex.y << ", " << vertex.z << "]" << endl;
  }
}

// prints out each polygon in the input vector
void printPolygons(VECPOLYGON polygons) {
  for(VECPOLYGON::iterator it = polygons.begin(); it != polygons.end(); ++it) {
    Polygon polygon = *it;
    cout << polygon.first << " " << polygon.second << " " << polygon.third << endl;
  }
}

void printTextureMappings(VECTEXTURE textures) {
  for(VECTEXTURE::iterator it = textures.begin(); it != textures.end(); ++it) {
    TextureMapping texture = *it;
    cout << texture.index << ": [" << texture.x << ", " << texture.y << "]" << endl;
  }
}

int main(void) {
  char * filename = "../data/face.vtk";
  VECSTRING lines = getLines(filename);
  VECVERTEX vertices = getVertices(lines);
  VECPOLYGON polygons = getPolygons(lines);
  VECTEXTURE textures = getTextureMappings(lines);
  printTextureMappings(textures);
}
