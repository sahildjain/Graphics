#include "surfaceModelParser.h"

vector getVertices(void) {
  vector<vertex> vertices;
  char * line;
  char * floats;
  ifstream file ("../data/face.vtk");
  if(file.is_open()) {
    while(file.good()) {
      getline(file, line);
      floats = strtok(line, " ");
      while(floats != NULL) {
        
      }
    }
    file.close();
  }
  else {
    cout << "Cannot open surface model file.";
  }
  return vertices;
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
}
