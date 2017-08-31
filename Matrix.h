//Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include "Object.h"

class Matrix
{
protected:
	//what should the matrix take in?
	float arr[4][4];

public:
	//this is the constructor
	Matrix();
	void print();

	static Matrix matrixOnes();
	static Matrix scale(Matrix M, Vector s);
	static Matrix rotate(Matrix M, Vector r);
	static Matrix rotateX(Matrix M, Vector r);
	static Matrix rotateY(Matrix M, Vector r);
	static Matrix rotateZ(Matrix M, Vector r);
	static Matrix translate(Matrix M, Vector t);
	static Vector multiplyVector(Matrix A, Vector v, bool direction);
	static Matrix multiplyMatrix(Matrix A, Matrix B);
	static Matrix inverse3(Matrix M);
	static Matrix inverse4(Matrix M);
	static Matrix add(Matrix A, Matrix B);
	static Matrix scalar(float c, Matrix M);
	static Matrix transpose(Matrix M);
};

#endif