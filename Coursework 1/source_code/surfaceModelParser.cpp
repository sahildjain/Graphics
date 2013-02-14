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

int getFirstVertexLineNum(VECSTRING lines) {
  int i = 0;
  VECSTRING::iterator it = lines.begin();
  string line = *it;
  char * l = &line[0];
  char * firstToken = strtok(l, " ");
  while(strcmp(firstToken, "POINTS")) {
    it++;
    i++;
    line = *it;
    l = &line[0];
    firstToken = strtok(l, " ");
  }
  return i;
}

int getLastVertexLineNum(VECSTRING lines) {
  int i = -1;
  VECSTRING::iterator it = lines.begin();
  string line = *it;
  char * l = &line[0];
  char * firstToken = strtok(l, " ");
  while(strcmp(firstToken, "POLYGONS")) {
    it++;
    i++;
    line = *it;
    l = &line[0];
    firstToken = strtok(l, " ");
  }
  return i;
}

VECVERTEX getVertices(VECSTRING lines) {
  int start = getFirstVertexLineNum(lines);
  int end = getLastVertexLineNum(lines);
  for(VECSTRING::iterator it = lines.begin(); it != lines.end(); ++it) {
    
  }
}

int main(void) {
  char * filename = "../data/face.vtk";
  VECSTRING lines = getLines(filename);
  int start = getFirstVertexLineNum(lines);
  cout << start << endl;
  int end = getLastVertexLineNum(lines);
  cout << end << endl;
  //printLines(lines);
  //VECVERTEX vertices = getVertices(lines);
}


/*vector<Vertex> getVertices(string filename) {
  vector<Vertex> vertices;
  char * line, floats = "";
  int numVertex = 0, counter;
  double f;
  Vertex vertex;
  ifstream file (filename);
  if(file.is_open()) {
    while(file.good() || floats != "POLYGON") {
      getline(file, line);
      int counter = 0; 
      while(counter < 3) {
        int count = 0;
        floats = strtok(line, " ");    
        while(count < 3) {
          vertex = Vertex();             
          f = stringToFloat(floats);
          vertex.setX(f);
          floats = strtok(NULL, " ");
          f = stringToFloat(floats);
          vertex.setY(f);
          floats = strtok(NULL, " ");
          f = stringToFloat(floats);
          vertex.setZ(f);
          floats = strtok(NULL, " ");
          count++;
        }
        vertices.push_back(vertex);
        counter++;
      }
    }
    file.close();
  }
  else {
    cout << "Cannot open surface model file.";
  }
  return vertices;
}

int stringToFloat(string s) {
  stringstream stream(s);
  float f;
  stream >> f;
  return f;
}

int main(void) {
  string line;
  ifstream file ("../data/face.vtk");
  if(file.is_open()) {
    while(file.good()) {
      getline(file, line);
      cout << line << endl;
    }
    file.close();
  }
  else {
    cout << "Cannot open surface model file.";
  }
  return 0;
}*/
