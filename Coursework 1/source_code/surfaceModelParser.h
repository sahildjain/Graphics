#ifndef _SURFACE_MODEL_PARSER_H
#define _SURFACE_MODEL_PARSER_H
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

struct Vertex {
  float x;
  float y;
  float z;
}

vector<string> getLines(string filename);
void printLines(vector<string> lines) 

#endif
