#include "Sampler.h"
#include "Vector.h"

#include <iostream>

#include <stdlib.h>
#include <time.h> 

Sampler::Sampler(Scene s){
	scene = s;
}

// do we want to do this for every pixel? or just one at a time
Vector Sampler::sample(float x, float y, int i, int n) {
	// INITIALIZE RANDOM SEED
	// srand (time(NULL));

	float squared = pow(n, 0.5);

	float XLO = (i % (int)squared) / squared;
	float XHI = ((i + 1) % (int)squared) / squared;
	float YLO = (i / (int)squared) / squared;
	float YHI = ((i + 1) % (int)squared) / squared;


	// GENERATES RANDOM NUMBER BETWEEN 1 AND 10
	float offsetx = XLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(XHI-XLO)));
	float offsety = YLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(YHI-YLO)));

	// this is the simple sampler
	x = x + offsetx;
	y = y + offsety;
	// x = x + .5;
	// y = y + .5;
	Vector pixelPos = scene.getPixelPos(x, y);

	return pixelPos;

}