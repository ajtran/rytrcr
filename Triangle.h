// Triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"
#include "Object.h"

class Triangle:Object
{
protected:
	Vector v1;
	Vector v2;
	Vector v3;
	Vector ka;
	Vector kd;
	Vector ks;
	float p;
	Vector kr;
	Matrix M;

public:	
	//this is the constructor
	static Vector getCentroid(Vector vertexA, Vector vertexB, Vector vertexC);
	Triangle(Vector vertex1, Vector vertex2, Vector vertex3, Vector amb , Vector diff, Vector spec, float coeff, Vector ref, Matrix trans);
	Vector getV1();
	Vector getV2();
	Vector getV3();
	Vector getKa();
	Vector getKd();
	Vector getKs();
	float getP();
	Vector getKr();
	Matrix getM();


	Vector getNormal();
};

#endif