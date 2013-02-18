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
#include <cmath>

using namespace std;

struct Polygon;
struct Vertex;
struct TextureMapping;
struct Vector;

struct Vector {
  float x;
  float y;
  float z;
};

struct Polygon {
  Vertex * first;
  Vertex * second;
  Vertex * third;
  Vector normal;
};

struct Vertex {
  int index;
  float x;
  float y;
  float z;
  vector<Polygon *> polygonPointers;
  Vector normal;
};

struct TextureMapping {
  int index;
  float x;
  float y;
};

#endif
