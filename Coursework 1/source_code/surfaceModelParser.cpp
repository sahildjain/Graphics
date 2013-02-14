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

// prints out each entry in the input vector
void printLines(VECSTRING lines) {
  for(VECSTRING::iterator it = lines.begin(); it != lines.end(); ++it) {
    cout << *it << endl;
  }
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

VECVERTEX addVertices(VECVERTEX vertices, string line) {
  int counter = 0;
  char * l = &line[0];
  char * token = strtok(l, " ");
  while(counter < 3) {
    Vertex vertex;
    float x = (float) atof(token);
    vertex.x = x;
    token = strtok(NULL, " ");
    float y = (float) atof(token);
    vertex.y = y;
    token = strtok(NULL, " ");
    float z = (float) atof(token);
    vertex.z = z;
    vertices.push_back(vertex);
    token = strtok(NULL, " ");
    counter++;
  }
  return vertices;
}

VECVERTEX getVertices(VECSTRING lines) {
  string line;
  VECVERTEX vertices;
  for(int start = getLineNum(lines, "POINTS") + 1; start < getLineNum(lines, "POLYGONS"); start++) {
    line = lines.at(start);
    vertices = addVertices(vertices, line);
  }
  return vertices;
}

void printVertices(VECVERTEX vertices) {
  for(VECVERTEX::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    Vertex vertex = *it;
    cout << vertex.x << " " << vertex.y << " " << vertex.z << endl;
  }
}

int main(void) {
  char * filename = "../data/face.vtk";
  VECSTRING lines = getLines(filename);
  int start = getLineNum(lines, "POINTS");
  cout << start << endl;
  int end = getLineNum(lines, "POLYGONS");
  cout << end << endl;
  VECVERTEX vertices = getVertices(lines);
  printVertices(vertices);
}
