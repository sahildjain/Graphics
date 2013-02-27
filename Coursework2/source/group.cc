#include "raycast.h"

// Constructor for a group of n objects.
Group::Group(int n) {

  this->_object = new Object3D*[n];
  this->_count  = n;
  for(int i = 0; i < n; ++i) {
    this->_object[i] = NULL;
  }
}

// Destructor.
Group::~Group() {

  if (this->_object == NULL) {
    return;
  }

  for (int i = 0; i < this->_count; i++) {
    if (this->_object[i] != NULL) {
      delete this->_object[i];
    }
  }
  delete[] this->_object;
}

// Insert an object into the array.
void Group::addObject(int index, Object3D *obj) {
  Object3D ** newObjects = new Object3D*[getCount() + 1];
  Object3D ** objects = getObjects();
  if(index < getCount()) {
    int i;
    for(i = 0; i < index; ++i) {
      newObjects[i] = objects[i];
    }
    newObjects[index] = obj;
    for(i = index + 1; i < getCount() + 1; ++i) {
      newObjects[i] = objects[i - 1];
    }
  }
  else { // add to the end of the array
    for(int i = 0; i < getCount(); ++i) {
      newObjects[i] = objects[i];
    }
    newObjects[getCount()] = obj;
  }
  this->_count++;
}

// Loops over all primitives in the group calling each one's
// intersection method in turn.
bool Group::intersect(const Ray &r, Hit &h) {
  Object3D ** o = getObjects();
  for(int i = 0; i < this->_count; ++i) {
    Object3D * object = o[i];
    object->intersect(r, h);
  }
  return true;
}

int Group::getCount() {
  return this->_count;
}

Object3D** Group::getObjects() {
  return this->_object;
}
