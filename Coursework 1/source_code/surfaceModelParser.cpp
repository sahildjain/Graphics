#include "surfaceModelParser.h"

using namespace std;

typedef vector<string> VECSTRING;
typedef vector<Vertex> VECVERTEX;

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

VECVERTEX addVertices(VECVERTEX vertices, string line, int index) {
  int counter = 0;
  char * l = &line[0];
  char * token = strtok(l, " ");
  float x, y, z;
  while(counter < 3) {
    //cout << index << endl;
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
    cout << vertex.index << " " << vertex.x << " " << vertex.y << " " << vertex.z << " " << vertex.index << endl;
  }
}

int main(void) {
  char * filename = "../data/face.vtk";
  VECSTRING lines = getLines(filename);
  VECVERTEX vertices = getVertices(lines);
}
