#ifndef _SURFACE_MODEL_PARSER_H
#define _SURFACE_MODEL_PARSER_H
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

class Vertex {
  private:
    float x;
    float y;
    float z;

  public: 

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  int getZ() {
    return z;
  }

  void setX(int newX) {
      x = newX;
  }

  void setY(int newY) {
      y = newY;
  }

  void setZ(int newZ) {
      z = newZ;
  }
};

int stringToFloat(string s);

#endif
