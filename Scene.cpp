// Scene.cpp
#include "Scene.h"
#include "Vector.h"

#include <iostream>

using namespace cimg_library;
using namespace std;

// default constructor
Scene::Scene(){
	//do nothing?
}

// maybe we don't need the image in the scene, to be determined later
Scene::Scene(Vector pos, Vector ul, Vector ll, Vector ur, Vector lr, int w, int l, CImg<> image){
	eye_pos = pos;
	UL = ul;
	LL = ll;
	UR = ur;
	LR = lr;
	width = w;
	length = l;

	img = image;
}

cimg_library::CImg<> Scene::getImg() {
	return img;
}

// also we need to offset it by .5 to get the middle of the pixel?
Vector Scene::getPixelPos(float x, float y) {
	float u = 1 - x/width;
	float v = 1 - y/length;
	Vector lowL = Vector::scale(v, LL);
	Vector uppL = Vector::scale((1 - v), UL);
	Vector left = Vector::scale(u, Vector::add(lowL, uppL));
	Vector lowR = Vector::scale(v, LR);
	Vector uppR = Vector::scale((1 - v), UR);
	Vector right = Vector::scale((1 - u), Vector::add(lowR, uppR));
	Vector out = Vector::add(left, right);
	return out;
}

Vector Scene::getEyePos() {
	return eye_pos;
}

Vector Scene::getUL() {
	return UL;
}

Vector Scene::getLL() {
	return LL;
}

Vector Scene::getUR() {
	return UR;
}

Vector Scene::getLR() {
	return LR;
}

int Scene::getWidth() {
	return width;
}

int Scene::getLength() {
	return length;
}