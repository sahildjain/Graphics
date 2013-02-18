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

Polygon setNormalForPolygon(Polygon polygon) {
  Vector normal;
  Vertex v1 = *polygon.first;
  Vertex v2 = *polygon.second;
  Vertex v3 = *polygon.third;
  Vector vec1;
  vec1.x = v1.x - v2.x;
  vec1.y = v1.y - v2.y;
  vec1.z = v1.z - v2.z;
  Vector vec2;
  vec2.x = v3.x - v1.x;
  vec2.y = v3.y - v1.y;
  vec2.z = v3.z - v1.z;
  float x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
  float y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
  float z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
  float length = sqrt(x * x + y * y + z * z);
  normal.x = x / length;
  normal.y = y / length;
  normal.z = z / length;
  polygon.normal = normal;
  return polygon;
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
  *polygon = setNormalForPolygon(*polygon);
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

void setVertexNormals() {
  for(VECVERTEX::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    Vertex v = *it;
    int index = v.index;
    Vertex * vertex = &v;
    Vector average;
    average.x = 0.0;
    average.y = 0.0;
    average.z = 0.0;
    vector<Polygon *> polygonPointers = v.polygonPointers;
    float size = vertex->polygonPointers.size();
    for(vector<Polygon *>::iterator iter = polygonPointers.begin(); iter != polygonPointers.end(); ++iter) {
      Polygon * p = *iter;
      average.x += p->normal.x;
      average.y += p->normal.y;
      average.z += p->normal.z;
    }
    float temp1 = average.x / size;
    float temp2 = average.y / size;
    float temp3 = average.z / size;
    float length = (temp1 * temp1 + temp2 * temp2 + temp3 * temp3);
    average.x = average.x / length;
    average.y = average.y / length;
    average.z = average.z / length;
    vertices[index].normal = average;
  }
}

// prints out each line
void printLines() {
  for(VECSTRING::iterator it = lines.begin(); it != lines.end(); ++it) {
    cout << *it << endl;
  }
}

// prints out each vertex
void printVertices() {
  for(VECVERTEX::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    Vertex vertex = *it;
    cout << vertex.index << ": [" << vertex.x << ", " << vertex.y << ", " << vertex.z << "] adjacent sides: " << vertex.polygonPointers.size() << endl;
  }
}

// prints out each polygon
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

void printPolygonNormals() {
  int counter = 0;
  for(VECPOLYGON::iterator it = polygons.begin(); it != polygons.end(); ++it, ++counter) {
    Polygon polygon = *it;
    Vector n = polygon.normal;
    cout << counter << ": [" << n.x << ", " << n.y << ", " << n.z << "]" << endl;
  }
}

void printVertexNormals() {
  for(VECVERTEX::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    Vertex vertex = *it;
    cout << vertex.index << " normal: [" << vertex.normal.x << ", " << vertex.normal.y << ", " << vertex.normal.z << "]" << endl;
  }
}

int main(void) {
  char * filename = "../data/face.vtk";
  getLines(filename);
  getVertices();
  getPolygons();
  getTextureMappings();
  setVertexNormals();
  //printVertexNormals();
}
