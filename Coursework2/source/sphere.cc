#include "raycast.h"

// Add any code you need here and in the corresponding header
// file.


Sphere::Sphere()
{

}



Sphere::Sphere(Vec3f centre, float radius, Vec3f color) {
	this->centre = centre;
	this->radius = radius;
	this->color = color;
}

/*
	l = direction of ray
	o = origin of ray
	r = radius of sphere
	c = centre of sphere
	if (sqrt((l . (o - c)) ^ 2 - (o - c) ^ 2 + r ^ 2) >= 0) return true, else return false
*/
bool Sphere::intersect(const Ray &r, Hit &h)
{
	Vec3f rayOrigin = r.getOrigin();
	Vec3f rayDirection = r.getDirection();

	// a =  (o - c) ^ 2
	Vec3f oMinusC = rayOrigin - this->centre;
	float a = oMinusC.Length() * oMinusC.Length();
	
	// dot product of l and (o - c)
	float dotProduct = rayDirection.Dot3(oMinusC);
	float b = dotProduct * dotProduct;

	// radius ^ 2
	float c = this->radius * this->radius;

	float d = b - a + c;

	if(d >= 0) { // there is an intersection
		float hitDistance = h.getT();
		float sqrtD = sqrt(d);
		float distance1 = 0 - dotProduct + sqrtD;
		float distance2 = 0 - dotProduct - sqrtD;
		float newDistance;
		if(distance2 < distance1) {
			newDistance = distance2;
		}
		else {
			newDistance = distance1;
		}
		if(hitDistance > newDistance) {
			// update the hit object
			h.set(newDistance, this->color);
		}
		return true; // return true as there is an intersection
	}
	
	// return false because there is no intersection
	return false;
}
