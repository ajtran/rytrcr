#include "Film.h"

using namespace std;

Film::Film(int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			dictRGB[make_pair(i, j)] = Vector();
			dictCount[make_pair(i, j)] = 0;
		}
	}
}

void Film::add(int x, int y, Vector rgb) {
	dictRGB[make_pair(x, y)] = Vector::add(dictRGB[make_pair(x,y)], rgb);
	dictCount[make_pair(x, y)] += 1.0;
}

Vector Film::mean(int x, int y) {
	Vector rgb = dictRGB[make_pair(x, y)];
	int count = dictCount[make_pair(x, y)];
	return Vector::scale(1.0 / count, rgb);
}