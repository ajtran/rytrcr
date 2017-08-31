#ifndef FILM_H
#define FILM_H

#include <map>
#include <list>
#include "Vector.h"

class Film {
protected:
	std::map<std::pair<int, int>, Vector > dictRGB;
	std::map<std::pair<int, int>, float > dictCount;



public:
	Film(int x, int y);

	void add(int x, int y, Vector rgb);
	Vector mean(int x, int y);
};

#endif