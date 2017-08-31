// Vector Class
#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
	float arr[3];

	Vector();
	Vector(float x, float y, float z);

	void print();

	Vector clip();

	static Vector scale(float c, Vector v);
	static Vector add(Vector u, Vector v);
	static float sum(Vector v);
	static Vector square(Vector v);
	static float dotProduct(Vector u, Vector v);
	static Vector multiply(Vector u, Vector v);
	static Vector normalize(Vector u);
	static Vector cross(Vector u, Vector v);
	static Vector half(Vector u, Vector v);
	static Vector rFunc(Vector l, Vector n);
	static Vector minDistance(Vector coordP, Vector coordM, Vector eyePos);
	static float distance(Vector u, Vector v);
	static Vector reflectedRay(Vector Ri, Vector normal);
};

#endif