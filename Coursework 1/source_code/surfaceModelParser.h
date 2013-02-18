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

using namespace std;

struct Polygon;
struct Vertex;
struct TextureMapping;
struct Normal;

struct Polygon {
  Vertex * first;
  Vertex * second;
  Vertex * third;
};

struct Vertex {
  int index;
  float x;
  float y;
  float z;
  vector<Polygon *> polygonPointers;
};

struct TextureMapping {
  int index;
  float x;
  float y;
};

struct Normal {
  float x;
  float y;
  float z;
};

#endif
