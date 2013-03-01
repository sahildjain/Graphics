#include "raycast.h"

// Add any code you need here and in the corresponding header
// file.


// Constructor with parameters.
OrthographicCamera::OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size) {
  this->centre = centre;
  this->direction = direction;
  this->up = up;
  this->size = size;
}

/*
 * point represents the screen coordinates
 * The ray object returned contains the origin and direction
 * of the ray in the world coordinates
 */
Ray OrthographicCamera::generateRay(Vec2f point) {
  
  // normalise the input projection direction
  Vec3f projectionDirection = getDirection();
  projectionDirection.Normalize();
  this->direction = projectionDirection;
  
  Vec3f up = getUp();
  up.Normalize();
  // horizontal vector is the cross product of up and direction
  Vec3f horizontal;
  Vec3f::Cross3(horizontal, projectionDirection, up);
  horizontal.Normalize();
  
  // check if up and direction are orthogonal. if they are not,
  // use the horizontal vector to find a perpendicular vector
  // to horizontal and direction, which will be orthonormal
  if(up.Dot3(projectionDirection) != 0) {
    Vec3f::Cross3(up, projectionDirection, horizontal); 
  }
  up.Normalize();
  this->up = up;
  
  //calculating the origin using the input point
  Vec3f origin = getCentre();

  if(point.x() != 0.5) {
    if (point.x() < 0.5) {
      origin += horizontal * ((0.5 - point.x()) * getSize());
    }
    else {
      origin -= horizontal * ((point.x() - 0.5) * getSize());
    }
  }
  
  if(point.y() != 0.5) {
    if (point.y() < 0.5) {
      origin += up * ((0.5 - point.y()) * getSize());
    }
    else {
      origin -= up * ((point.y() - 0.5) * getSize());
    }
  }
  
  // As the camera is orthogonal, the direction is always the projection direction
  Ray *ray = new Ray(projectionDirection, origin);
  return *ray;
}

Vec3f OrthographicCamera::getCentre() {
  return this->centre;
}

Vec3f OrthographicCamera::getDirection() {
  return this->direction;
}

Vec3f OrthographicCamera::getUp() {
  return this->up;
}

int OrthographicCamera::getSize() {
  return this->size;
}
