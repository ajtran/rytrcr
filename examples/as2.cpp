#ifndef cimg_debug
#define cimg_debug 1
#endif

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

#include "CImg.h"
#include "Film.h"
#include "Film.cpp"
#include "Matrix.h"
#include "Matrix.cpp"
#include "Raytracer.h"
#include "Raytracer.cpp"
#include "Sampler.h"
#include "Sampler.cpp"
#include "Shader.h"
#include "Shader.cpp"
#include "Scene.h"
#include "Scene.cpp"
#include "Sphere.h"
#include "Sphere.cpp"
#include "Triangle.h"
#include "Triangle.cpp"
#include "Vector.h"
#include "Vector.cpp"

using namespace cimg_library;
using namespace std;

#undef min
#undef max


//****************************************************
// Global Variables
//****************************************************
Vector eye = Vector(0.0, 0.0, 0.0);
Vector ll = Vector(0.0, 0.0, 0.0);
Vector lr = Vector(0.0, 0.0, 0.0);
Vector ul = Vector(0.0, 0.0, 0.0);
Vector ur = Vector(0.0, 0.0, 0.0);

Vector center = Vector(0.0, 0.0, 0.0);
float radius = 0.0;

Vector vertexA = Vector(0.0, 0.0, 0.0);
Vector vertexB = Vector(0.0, 0.0, 0.0);
Vector vertexC = Vector(0.0, 0.0, 0.0);

vector<Vector> pls;
vector<Vector> dls;
vector<Vector> pIntensity;
vector<Vector> dIntensity;

Vector pointLight = Vector(0.0, 0.0, 0.0);
float falloff = 0;
Vector rgbPoint = Vector(0.0, 0.0, 0.0);
Vector directLight = Vector(0.0, 0.0, 0.0);
Vector rgbDirect = Vector(0.0, 0.0, 0.0);
Vector rgbAmbient = Vector(0.0, 0.0, 0.0);
Vector ka = Vector(0.0, 0.0, 0.0);
Vector ks = Vector(0.0, 0.0, 0.0);
float spectralCoeff = 0.0;
Vector kd = Vector(0.0, 0.0, 0.0);
Vector kr = Vector(0.0, 0.0, 0.0);

Matrix translate = Matrix();
Matrix rotation = Matrix();
Matrix rotateX = Matrix();
Matrix rotateY = Matrix();
Matrix rotateZ = Matrix();
Matrix scale = Matrix();

vector<Matrix> transformations;

Matrix M = Matrix();

string File = "";

vector<Sphere> spheres;
vector<Triangle> triangles;
vector<Vector> vertices;

//****************************************************
// Main Procedure
//****************************************************
int main(int argc,char **argv) {
  // Parsing Command Line Arguments
  for (int i = 1; i < argc; i++) {
  	cout << argv[i] << endl;
  	if (strcmp(argv[i], "cam") == 0) {
  		eye = Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
  		ll = Vector(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
  		lr = Vector(atof(argv[i + 7]), atof(argv[i + 8]), atof(argv[i + 9]));
  		ul = Vector(atof(argv[i + 10]), atof(argv[i + 11]), atof(argv[i + 12]));
  		ur = Vector(atof(argv[i + 13]), atof(argv[i + 14]), atof(argv[i + 15]));
  		i += 15;
  	} else if (strcmp(argv[i], "sph") == 0) {
  		center = Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
  		radius = atof(argv[i + 4]);
      for (int t = 0; t < transformations.size(); t++) {
        M = Matrix::multiplyMatrix(transformations[transformations.size()-1-t], M);
      }
      M = Matrix::multiplyMatrix(Matrix::scale(Matrix(), Vector(radius, radius, radius)), M);
      M = Matrix::multiplyMatrix(Matrix::translate(Matrix(), center), M);

      M.print();
  		Sphere sphere = Sphere(center, radius, ka, kd, ks, spectralCoeff, kr, M);
  		spheres.push_back(sphere);
      M = Matrix();
  		i += 4;
  	} else if (strcmp(argv[i], "tri") == 0) {
  		vertexA = Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
  		vertexB = Vector(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
  		vertexC = Vector(atof(argv[i + 7]), atof(argv[i + 8]), atof(argv[i + 9]));

      for (int t = 0; t < transformations.size(); t++) {
        M = Matrix::multiplyMatrix(transformations[transformations.size()-1-t], M);
      }
      M.print();

      Triangle triangle = Triangle(vertexA, vertexB, vertexC, ka, kd, ks, spectralCoeff, kr, M);
      triangles.push_back(triangle);
  		i += 9;
  	} else if (strcmp(argv[i], "obj") == 0) {
  		File = argv[i + 1];
      ifstream file(File.c_str());
      string line;
      string type;
      while (std::getline(file, line)) {

        if ((line == "") || (line[0] == '#')) {
          continue;
        }
        istringstream iss(line);
        iss >> type;
        if (type == "v") {
          Vector temp = Vector();
          sscanf(line.c_str(), "%*s %f %f %f", &temp.arr[0], &temp.arr[1], &temp.arr[2]);
          vertices.push_back(temp);
        }
        if (type == "f") {
          int v1;
          int v2;
          int v3;
          sscanf(line.c_str(), "%*s %i %i %i", &v1, &v2, &v3);
          Triangle temp = Triangle(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1], ka, kd, ks, spectralCoeff, kr, Matrix());
          triangles.push_back(temp);
        }
      }
  		i += 1;
  	} else if (strcmp(argv[i], "ltp") == 0) {
  		pointLight = Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
  		rgbPoint = Vector(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
  		falloff = atof(argv[i + 7]);
  		pls.push_back(pointLight);
  		pIntensity.push_back(rgbPoint);
  		i += 7;
  	} else if (strcmp(argv[i], "ltd") == 0) {
  		directLight = Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
  		rgbDirect = Vector(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
  		dls.push_back(directLight);
  		dIntensity.push_back(rgbDirect);
  		i += 6;
  	} else if (strcmp(argv[i], "lta") == 0) {
  		rgbAmbient = Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
  		i += 3;
  	} else if (strcmp(argv[i], "mat") == 0) {
  		ka = Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
  		kd = Vector(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
  		ks = Vector(atof(argv[i + 7]), atof(argv[i + 8]), atof(argv[i + 9]));
  		spectralCoeff = atof(argv[i + 10]);
  		kr = Vector(atof(argv[i + 11]), atof(argv[i + 12]), atof(argv[i + 13]));
  		i += 13;
  	} else if (strcmp(argv[i], "xft") == 0) {
  		translate = Matrix::translate(translate, Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3])));
      transformations.push_back(translate);
  		i += 3;
  	} else if (strcmp(argv[i], "xfr") == 0) {
      rotation = Matrix::rotate(rotation, Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3])));
      transformations.push_back(rotation);
  		i += 3;
  	} else if (strcmp(argv[i], "xfs") == 0) {
  		scale = Matrix::scale(scale, Vector(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3])));
      transformations.push_back(scale);
  		i += 3;
    } else if (strcmp(argv[i], "xfz") == 0) {
      translate = Matrix();
      rotation = Matrix();
      scale = Matrix();
      M = Matrix();
      transformations = vector<Matrix>();
  	} else {
  		fprintf(stderr, "Warning: Too many parameters or too little parameters or unsupported feature. Program has stopped running.\n");
  		return 0;
  	}
  }

  int x = 700;
  int y = 700;
  CImg<> img(x, y, 1, 3, 0);

  Scene scene = Scene(eye, ll, ul, lr, ur, x, y, img);

  Film film = Film(x, y);

  Sampler sampler = Sampler(scene);

  Shader shader = Shader(pls, pIntensity, dls, dIntensity);

  Raytracer raytracer = Raytracer(shader, spheres, triangles, eye);

  Vector rgb = Vector(0.0, 0.0, 0.0);
  for (int i = 0; i < x; i++) {
  	for (int j = 0; j < y; j++) {
  		Vector pixelPos;
      int n = 4;
  		for (int k = 0; k < 16; k++) {
        pixelPos = sampler.sample(i, j, k, n);
        Vector direction = Vector::add(pixelPos, Vector::scale(-1.0, eye));
			  Vector color = raytracer.trace(direction, eye, 5);
			  film.add(i, j, color);
		  }

      rgb = film.mean(i, j).clip();
      if (falloff > 0) {
        rgb = Vector::scale(1 / pow(falloff, 2), rgb);
      }
		  img(i, j, 0) = rgb.arr[0];
		  img(i, j, 1) = rgb.arr[1];
		  img(i, j, 2) = rgb.arr[2];
  	}
  }

  img.display();

  // to save to png file
  img.normalize(0, 255);
  img.save("image-06.png");

  return 0;
}