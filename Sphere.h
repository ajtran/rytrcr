// Sphere.h
#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "Object.h"

class Sphere:Object
{
protected:
	Vector center;
	float radius;
	Vector ka;
	Vector kd;
	Vector ks;
	float p;
	Vector kr;
	Matrix M;

public:	
	Sphere(Vector center, float radius, Vector amb , Vector diff, Vector spec, float coeff, Vector ref, Matrix transf); //this is the constructor

	Vector getCenter();
	float getRadius();
	Vector getKa();
	Vector getKd();
	Vector getKs();
	float getP();
	Vector getKr();
	Matrix getM();

};

#endif