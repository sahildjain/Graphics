#ifndef _SURFACE_MODEL_PARSER_H
#define _SURFACE_MODEL_PARSER_H
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <string>

struct Vertex {
  float x;
  float y;
  float z;
  int index;
};

struct Polygon {
  int first;
  int second;
  int third;
};

#endif
