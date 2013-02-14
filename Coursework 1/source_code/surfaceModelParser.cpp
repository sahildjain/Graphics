#include "surfaceModelParser.h"
#include <vector>

using namespace std;

vector<string> getLines(string filename) {
  vector<string> lines;
  char * line;
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

void printLines(vector<string> lines) {

}

int main(void) {
  string filename = "../data/face.vtk";
  vector<string> lines = getLines(filename);
  printLines(lines);
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
