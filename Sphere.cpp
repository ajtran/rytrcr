#include "Sphere.h"


Sphere::Sphere(Vector c, float r, Vector amb , Vector diff, Vector spec, float coeff, Vector ref, Matrix transf){
	center = c;
	radius = r;
	ka = amb;
	kd = diff;
	ks = spec;
	p = coeff;
	kr = ref;
	M = transf;
}

Vector Sphere::getCenter(){
	return center;
}

float Sphere::getRadius(){
	return radius;
}

Vector Sphere::getKa(){
	return ka;
}

Vector Sphere::getKd(){
	return kd;
}

Vector Sphere::getKs(){
	return ks;
}

float Sphere::getP(){
	return p;
}

Vector Sphere::getKr(){
	return kr;
}

Matrix Sphere::getM(){
	return M;
}