// Shader Class
#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include "Vector.h"

class Shader
{
public:
	Shader();
	Shader(vector<Vector> pls, vector<Vector> rgbPoints, vector<Vector> dls, vector<Vector> rgbDirects);
	Vector shading(Vector point, Vector normv);
	Vector phong(Vector ka, Vector kd, Vector ks, Vector l, Vector n, Vector i, float p, Vector normv);

	vector<Vector> getPls();
	vector<Vector> getPis();
	vector<Vector> getDls();
	vector<Vector> getDis();



protected:
	vector<Vector> pointLights;
	vector<Vector> directLights;
	vector<Vector> pointRGBs;
	vector<Vector> directRGBs;
};

#endif