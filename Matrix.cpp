//Matrix.cpp

#include "Matrix.h"
#include <math.h>

Matrix::Matrix() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				arr[i][j] = 1.0;
			} else {
				arr[i][j] = 0.0;
			}
		}
	}
}

Matrix Matrix::matrixOnes() {
	Matrix out = Matrix();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out.arr[i][j] = 1.0;
		}
	}
	return out;
}

Vector Matrix::multiplyVector(Matrix A, Vector v, bool direction) {
	float dp0 = A.arr[0][0] * v.arr[0] + A.arr[0][1] * v.arr[1] + A.arr[0][2] * v.arr[2];
	float dp1 = A.arr[1][0] * v.arr[0] + A.arr[1][1] * v.arr[1] + A.arr[1][2] * v.arr[2];
	float dp2 = A.arr[2][0] * v.arr[0] + A.arr[2][1] * v.arr[1] + A.arr[2][2] * v.arr[2];
	if (direction) {
		return Vector(dp0, dp1, dp2);
	}
	dp0 += A.arr[0][3];
	dp1 += A.arr[1][3];
	dp2 += A.arr[2][3];
	return Vector(dp0, dp1, dp2);
}

// This is used for only multiplying matrices in 4 dimensions.
Matrix Matrix::multiplyMatrix(Matrix A, Matrix B) {
	Matrix out = Matrix();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out.arr[j][i] = A.arr[j][0] * B.arr[0][i] + A.arr[j][1] * B.arr[1][i] + A.arr[j][2] * B.arr[2][i] + A.arr[j][3] * B.arr[3][i];
		}
	}
	return out;
}

Matrix Matrix::inverse3(Matrix M) {
	//computing the determinant of a 3x3 matrix
	float det = (M.arr[0][0]) * ((M.arr[1][1]*M.arr[2][2] - M.arr[2][1]*M.arr[1][2])) 
	- (M.arr[0][1]) * (M.arr[1][0] * M.arr[2][2] - M.arr[1][2] * M.arr[2][0]) 
	+ (M.arr[0][2]) * (M.arr[1][0] * M.arr[2][1] - M.arr[1][1] * M.arr[2][0]);

	float divide = 1/det;
	Matrix inverse = Matrix();
	inverse.arr[0][0] = (M.arr[1][1] * M.arr[2][2] - M.arr[2][1] * M.arr[1][2]) * divide;
	inverse.arr[0][1] = (M.arr[0][2] * M.arr[2][1] - M.arr[0][1] * M.arr[2][2]) * divide;
	inverse.arr[0][2] = (M.arr[0][1] * M.arr[1][2] - M.arr[0][2] * M.arr[1][1]) * divide;
	inverse.arr[1][0] = (M.arr[1][2] * M.arr[2][0] - M.arr[1][0] * M.arr[2][2]) * divide;
	inverse.arr[1][1] = (M.arr[0][0] * M.arr[2][2] - M.arr[0][2] * M.arr[2][0]) * divide;
	inverse.arr[1][2] = (M.arr[1][0] * M.arr[0][2] - M.arr[0][0] * M.arr[1][2]) * divide;
	inverse.arr[2][0] = (M.arr[1][0] * M.arr[2][1] - M.arr[2][0] * M.arr[1][1]) * divide;
	inverse.arr[2][1] = (M.arr[2][0] * M.arr[0][1] - M.arr[0][0] * M.arr[2][1]) * divide;
	inverse.arr[2][2] = (M.arr[0][0] * M.arr[1][1] - M.arr[1][0] * M.arr[0][1]) * divide;
	return inverse;

}

Matrix Matrix::inverse4(Matrix M) {
	Matrix inv = Matrix();

    inv.arr[0][0] = M.arr[1][1]  * M.arr[2][2] * M.arr[3][3] - 
             M.arr[1][1]  * M.arr[2][3] * M.arr[3][2] - 
             M.arr[2][1]  * M.arr[1][2]  * M.arr[3][3] + 
             M.arr[2][1]  * M.arr[1][3]  * M.arr[3][2] +
             M.arr[3][1] * M.arr[1][2]  * M.arr[2][3] - 
             M.arr[3][1] * M.arr[1][3]  * M.arr[2][2];

    inv.arr[1][0] = -M.arr[1][0]  * M.arr[2][2] * M.arr[3][3] + 
              M.arr[1][0]  * M.arr[2][3] * M.arr[3][2] + 
              M.arr[2][0]  * M.arr[1][2]  * M.arr[3][3] - 
              M.arr[2][0]  * M.arr[1][3]  * M.arr[3][2] - 
              M.arr[3][0] * M.arr[1][2]  * M.arr[2][3] + 
              M.arr[3][0] * M.arr[1][3]  * M.arr[2][2];

    inv.arr[2][0] = M.arr[1][0]  * M.arr[2][1] * M.arr[3][3] - 
             M.arr[1][0]  * M.arr[2][3] * M.arr[3][1] - 
             M.arr[2][0]  * M.arr[1][1] * M.arr[3][3] + 
             M.arr[2][0]  * M.arr[1][3] * M.arr[3][1] + 
             M.arr[3][0] * M.arr[1][1] * M.arr[2][3] - 
             M.arr[3][0] * M.arr[1][3] * M.arr[2][1];

    inv.arr[3][0] = -M.arr[1][0]  * M.arr[2][1] * M.arr[3][2] + 
               M.arr[1][0]  * M.arr[2][2] * M.arr[3][1] +
               M.arr[2][0]  * M.arr[1][1] * M.arr[3][2] - 
               M.arr[2][0]  * M.arr[1][2] * M.arr[3][1] - 
               M.arr[3][0] * M.arr[1][1] * M.arr[2][2] + 
               M.arr[3][0] * M.arr[1][2] * M.arr[2][1];

    inv.arr[0][1] = -M.arr[0][1]  * M.arr[2][2] * M.arr[3][3] + 
              M.arr[0][1]  * M.arr[2][3] * M.arr[3][2] + 
              M.arr[2][1]  * M.arr[0][2] * M.arr[3][3] - 
              M.arr[2][1]  * M.arr[0][3] * M.arr[3][2] - 
              M.arr[3][1] * M.arr[0][2] * M.arr[2][3] + 
              M.arr[3][1] * M.arr[0][3] * M.arr[2][2];

    inv.arr[1][1] = M.arr[0][0]  * M.arr[2][2] * M.arr[3][3] - 
             M.arr[0][0]  * M.arr[2][3] * M.arr[3][2] - 
             M.arr[2][0]  * M.arr[0][2] * M.arr[3][3] + 
             M.arr[2][0]  * M.arr[0][3] * M.arr[3][2] + 
             M.arr[3][0] * M.arr[0][2] * M.arr[2][3] - 
             M.arr[3][0] * M.arr[0][3] * M.arr[2][2];

    inv.arr[2][1] = -M.arr[0][0]  * M.arr[2][1] * M.arr[3][3] + 
              M.arr[0][0]  * M.arr[2][3] * M.arr[3][1] + 
              M.arr[2][0]  * M.arr[0][1] * M.arr[3][3] - 
              M.arr[2][0]  * M.arr[0][3] * M.arr[3][1] - 
              M.arr[3][0] * M.arr[0][1] * M.arr[2][3] + 
              M.arr[3][0] * M.arr[0][3] * M.arr[2][1];

    inv.arr[3][1] = M.arr[0][0]  * M.arr[2][1] * M.arr[3][2] - 
              M.arr[0][0]  * M.arr[2][2] * M.arr[3][1] - 
              M.arr[2][0]  * M.arr[0][1] * M.arr[3][2] + 
              M.arr[2][0]  * M.arr[0][2] * M.arr[3][1] + 
              M.arr[3][0] * M.arr[0][1] * M.arr[2][2] - 
              M.arr[3][0] * M.arr[0][2] * M.arr[2][1];

    inv.arr[0][2] = M.arr[0][1]  * M.arr[1][2] * M.arr[3][3] - 
             M.arr[0][1]  * M.arr[1][3] * M.arr[3][2] - 
             M.arr[1][1]  * M.arr[0][2] * M.arr[3][3] + 
             M.arr[1][1]  * M.arr[0][3] * M.arr[3][2] + 
             M.arr[3][1] * M.arr[0][2] * M.arr[1][3] - 
             M.arr[3][1] * M.arr[0][3] * M.arr[1][2];

    inv.arr[1][2] = -M.arr[0][0]  * M.arr[1][2] * M.arr[3][3] + 
              M.arr[0][0]  * M.arr[1][3] * M.arr[3][2] + 
              M.arr[1][0]  * M.arr[0][2] * M.arr[3][3] - 
              M.arr[1][0]  * M.arr[0][3] * M.arr[3][2] - 
              M.arr[3][0] * M.arr[0][2] * M.arr[1][3] + 
              M.arr[3][0] * M.arr[0][3] * M.arr[1][2];

    inv.arr[2][2] = M.arr[0][0]  * M.arr[1][1] * M.arr[3][3] - 
              M.arr[0][0]  * M.arr[1][3] * M.arr[3][1] - 
              M.arr[1][0]  * M.arr[0][1] * M.arr[3][3] + 
              M.arr[1][0]  * M.arr[0][3] * M.arr[3][1] + 
              M.arr[3][0] * M.arr[0][1] * M.arr[1][3] - 
              M.arr[3][0] * M.arr[0][3] * M.arr[1][1];

    inv.arr[3][2] = -M.arr[0][0]  * M.arr[1][1] * M.arr[3][2] + 
               M.arr[0][0]  * M.arr[1][2] * M.arr[3][1] + 
               M.arr[1][0]  * M.arr[0][1] * M.arr[3][2] - 
               M.arr[1][0]  * M.arr[0][2] * M.arr[3][1] - 
               M.arr[3][0] * M.arr[0][1] * M.arr[1][2] + 
               M.arr[3][0] * M.arr[0][2] * M.arr[1][1];

    inv.arr[0][3] = -M.arr[0][1] * M.arr[1][2] * M.arr[2][3] + 
              M.arr[0][1] * M.arr[1][3] * M.arr[2][2] + 
              M.arr[1][1] * M.arr[0][2] * M.arr[2][3] - 
              M.arr[1][1] * M.arr[0][3] * M.arr[2][2] - 
              M.arr[2][1] * M.arr[0][2] * M.arr[1][3] + 
              M.arr[2][1] * M.arr[0][3] * M.arr[1][2];

    inv.arr[1][3] = M.arr[0][0] * M.arr[1][2] * M.arr[2][3] - 
             M.arr[0][0] * M.arr[1][3] * M.arr[2][2] - 
             M.arr[1][0] * M.arr[0][2] * M.arr[2][3] + 
             M.arr[1][0] * M.arr[0][3] * M.arr[2][2] + 
             M.arr[2][0] * M.arr[0][2] * M.arr[1][3] - 
             M.arr[2][0] * M.arr[0][3] * M.arr[1][2];

    inv.arr[2][3] = -M.arr[0][0] * M.arr[1][1] * M.arr[2][3] + 
               M.arr[0][0] * M.arr[1][3] * M.arr[2][1] + 
               M.arr[1][0] * M.arr[0][1] * M.arr[2][3] - 
               M.arr[1][0] * M.arr[0][3] * M.arr[2][1] - 
               M.arr[2][0] * M.arr[0][1] * M.arr[1][3] + 
               M.arr[2][0] * M.arr[0][3] * M.arr[1][1];

    inv.arr[3][3] = M.arr[0][0] * M.arr[1][1] * M.arr[2][2] - 
              M.arr[0][0] * M.arr[1][2] * M.arr[2][1] - 
              M.arr[1][0] * M.arr[0][1] * M.arr[2][2] + 
              M.arr[1][0] * M.arr[0][2] * M.arr[2][1] + 
              M.arr[2][0] * M.arr[0][1] * M.arr[1][2] - 
              M.arr[2][0] * M.arr[0][2] * M.arr[1][1];

    float det = M.arr[0][0] * inv.arr[0][0] + M.arr[0][1] * inv.arr[1][0] + M.arr[0][2] * inv.arr[2][0] + M.arr[0][3] * inv.arr[3][0];

    if (det == 0)
    	return M;

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
        inv.arr[i/4][i%4] = inv.arr[i/4][i%4] * det;

    return inv;
}

Matrix Matrix::add(Matrix A, Matrix B) {
	Matrix out = Matrix();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			out.arr[i][j] = A.arr[i][j] + B.arr[i][j];
		}
	}
	return out;
}

Matrix Matrix::scale(Matrix M, Vector s) {
	M.arr[0][0] = s.arr[0];
	M.arr[1][1] = s.arr[1];
	M.arr[2][2] = s.arr[2];
	return M;
}

//mainly for multiplying a matrix by a scalar 
Matrix Matrix::scalar(float c, Matrix M) {
	Matrix out = Matrix();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			out.arr[i][j] = c * M.arr[i][j];
		}
	}
	return out;
}

Matrix Matrix::rotate(Matrix M, Vector r) {
	Matrix rCross = Matrix();
	Matrix rotationMatrix = Matrix();
	Matrix rrt = Matrix();
	Vector normr = Vector::normalize(r);

	rCross.arr[0][0] = 0.0;
	rCross.arr[0][1] = -normr.arr[2];
	rCross.arr[0][2] = normr.arr[1];
	rCross.arr[1][0] = normr.arr[2];
	rCross.arr[1][1] = 0.0;
	rCross.arr[1][2] = -normr.arr[0];
	rCross.arr[2][0] = -normr.arr[1];
	rCross.arr[2][1] = normr.arr[0];
	rCross.arr[2][2] = 0.0;

	float theta = pow(Vector::sum(Vector::square(r)), 0.5);
	//rhat * rhat^T
	rrt.arr[0][0] = normr.arr[0] * normr.arr[0];
	rrt.arr[0][1] = normr.arr[0] * normr.arr[1];
	rrt.arr[0][2] = normr.arr[0] * normr.arr[2];
	rrt.arr[1][0] = normr.arr[1] * normr.arr[0];
	rrt.arr[1][1] = normr.arr[1] * normr.arr[1];
	rrt.arr[1][2] = normr.arr[1] * normr.arr[2];
	rrt.arr[2][0] = normr.arr[2] * normr.arr[0]; 
	rrt.arr[2][1] = normr.arr[2] * normr.arr[1];
	rrt.arr[2][2] = normr.arr[2] * normr.arr[2];


	rotationMatrix = Matrix::add(Matrix::add(rrt, Matrix::scalar(sin(theta), rCross)), Matrix::scalar(-cos(theta), Matrix::multiplyMatrix(rCross, rCross)));
	return rotationMatrix;
}

Matrix Matrix::transpose(Matrix M) {
	Matrix T = Matrix();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			T.arr[i][j] = M.arr[j][i];
		}
	}
	return T;
}

Matrix Matrix::translate(Matrix M, Vector t) {
	M.arr[0][3] = t.arr[0];
	M.arr[1][3] = t.arr[1];
	M.arr[2][3] = t.arr[2];
	return M;
}

void Matrix::print() {
	for (int i = 0; i < 4; i++) {
		cout << "[ ";
		for (int j = 0; j < 4; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "]" << endl;
	}
}