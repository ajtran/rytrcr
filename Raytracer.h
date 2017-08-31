// Raytracer.h
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Shader.h"
#include "Sphere.h"
#include "Triangle.h"

class Raytracer {
protected: 
	Shader shader;
	vector<Sphere> spheres;
	vector<Triangle> triangles;
	Vector eye;

public:
	Raytracer(Shader shdr, vector<Sphere> sphs, vector<Triangle> tris, Vector eyePos);
	float intersectSph(Vector direction, Vector source, Sphere sphere);
	float intersectTri(Vector direction, Vector source, Triangle triangle);

	Vector trace(Vector rayDirection, Vector source, int depth);
};

#endif