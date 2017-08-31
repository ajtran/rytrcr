// Sample.h
// Basically, calculates each ray going from the eye
// to the scene... and returns if it hits anything
// or the color of the pixel it hits
#ifndef SAMPLER_H
#define SAMPLER_H

#include "CImg.h"
#include "Scene.h"
class Sampler
{
protected:
	Scene scene;

public:
	Sampler(Scene scene);

	Vector sample(float x, float y, int i, int n);
};

#endif