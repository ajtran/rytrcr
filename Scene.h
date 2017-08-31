// Scene.h
#ifndef SCENE_H
#define SCENE_H

#include "Vector.h"
#include "CImg.h"


class Scene
{
protected:
	Vector eye_pos;
	Vector UL;
	Vector LL;
	Vector UR;
	Vector LR;
	int width;
	int length;
	cimg_library::CImg<> img;

public:
	Scene();

	Scene(Vector eye_pos, Vector UL, Vector LL, Vector UR, Vector LR, int width, int length, cimg_library::CImg<> img);

	cimg_library::CImg<> getImg();
	Vector getPixelPos(float x, float y);
	Vector getEyePos();
	Vector getUL();
	Vector getLL();
	Vector getUR();
	Vector getLR();
	int getWidth();
	int getLength();

};

#endif