#include "Vector.h"

#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

// initialize vector.
Vector::Vector(){
	arr[0] = 0.0;
	arr[1] = 0.0;
	arr[2] = 0.0;
}

// initialize entires in vector to x, y, z.
Vector::Vector(float x, float y, float z) {
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
}

// scaling the vector by a scalar c and return a Vector.
Vector Vector::scale(float c, Vector v) {
	Vector scaleVec = Vector(v.arr[0] * c, v.arr[1] * c, v.arr[2] * c);
    return scaleVec;
}

// add two vectors u and v and return a Vector.
Vector Vector::add(Vector u, Vector v) { 
	Vector addVec = Vector(u.arr[0] + v.arr[0], u.arr[1] + v.arr[1], u.arr[2] + v.arr[2]);
	return addVec;
}

// sum the entries in the vector v and return a float.
float Vector::sum(Vector v) {
	float sum = v.arr[0] + v.arr[1] + v.arr[2];
	return sum;
}

// square the entries in the vector v and return a Vector.
Vector Vector::square(Vector v) {
	Vector squareVec = Vector(v.arr[0] * v.arr[0], v.arr[1] * v.arr[1], v.arr[2] * v.arr[2]);
	return squareVec;
}

// multiply two vectors u and v and return a Vector.
Vector Vector::multiply(Vector u, Vector v) {
	return Vector(u.arr[0] * v.arr[0], u.arr[1] * v.arr[1], u.arr[2] * v.arr[2]);
}

// take the dot product between two vectors u and v and return a float.
float Vector::dotProduct(Vector u, Vector v) {
	return Vector::sum(Vector::multiply(u, v));
}

// normalize the vector u and return a Vector.
Vector Vector::normalize(Vector u) {
	float factor = pow(Vector::sum(Vector::square(u)), 0.5);
	return Vector::scale(1/factor, u);
}

// take the cross product of two vectors u and v and return a Vector.
Vector Vector::cross(Vector u, Vector v) {
	Vector cproduct = Vector(u.arr[1]*v.arr[2] - u.arr[2]*v.arr[1], u.arr[2]*v.arr[0] - u.arr[0]*v.arr[2], u.arr[0]*v.arr[1] - u.arr[1]*v.arr[0]);
	return cproduct;
}

// computes the half vector.
Vector Vector::half(Vector u, Vector v) {
	return Vector::normalize(Vector::add(u, v));
}


Vector Vector::rFunc(Vector l, Vector n) {
	Vector negL = Vector::scale(-1.0, l);
	float dot = Vector::dotProduct(l, n);
	return Vector::add(negL, Vector::scale(2.0 * dot, n));
}

Vector Vector::minDistance(Vector coordP, Vector coordM, Vector eyePos) {

	float distP = pow(Vector::sum(Vector::square(Vector::add(Vector::scale(-1, eyePos), coordP))), 0.5);
	float distM = pow(Vector::sum(Vector::square(Vector::add(Vector::scale(-1, eyePos), coordM))), 0.5);
	if (distP < distM) {
		return coordP;

	} else {
		return coordM;
	}
}

float Vector::distance(Vector u, Vector v) {
	return pow(Vector::sum(Vector::square(Vector::add(u, Vector::scale(-1.0, v)))), 0.5);
}

Vector Vector::clip() {
	Vector v = Vector(arr[0], arr[1], arr[2]);
	if (arr[0] > 1.0) {
		v.arr[0] = 1.0;
	}
	if (arr[1] > 1.0) {
		v.arr[1] = 1.0;
	}
	if (arr[2] > 1.0) {
		v.arr[2] = 1.0;
	}
	return v;
}


// computes the reflected ray which is 
// Rr = Ri - 2N(Ri . N)
Vector Vector::reflectedRay(Vector Ri, Vector normal) {
	float dot = Vector::dotProduct(Ri, normal);
 	Vector Rr = Vector::add(Ri, Vector::scale(-2.0 * dot, normal));
	return Rr;
}

// a function that prints a vector. 
void Vector::print(){
	cout << "[" << arr[0] << " " << arr[1] << " " << arr[2] << "]" << endl;
}