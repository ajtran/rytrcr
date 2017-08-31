#include "Triangle.h"


Triangle::Triangle(Vector vertex1, Vector vertex2, Vector vertex3, Vector amb , Vector diff, Vector spec, float coeff, Vector ref, Matrix trans){
	v1 = vertex1;
	v2 = vertex2;
	v3 = vertex3;
	ka = amb;
	kd = diff;
	ks = spec;
	p = coeff;
	kr = ref;
	M = trans;

}

Vector Triangle::getCentroid(Vector vertexA, Vector vertexB, Vector vertexC){
	// Vector vertexA = triangle.getV1();
	// Vector vertexB = triangle.getV2();
	// Vector vertexC = triangle.getV3();
	float c1 = (vertexA.arr[0] + vertexB.arr[0] + vertexC.arr[0]) / 3;
	float c2 = (vertexA.arr[1] + vertexB.arr[1] + vertexC.arr[1]) / 3;
	float c3 = (vertexA.arr[2] + vertexB.arr[2] + vertexC.arr[2]) / 3;
	Vector centroid = Vector();
	centroid.arr[0] = c1;
	centroid.arr[1] = c2;
	centroid.arr[2] = c3;
	return centroid;
}

Matrix Triangle::getM(){
	return M;
}

Vector Triangle::getV1(){
	return v1;
}

Vector Triangle::getV2(){
	return v2;
}

Vector Triangle::getV3(){
	return v3;
}

Vector Triangle::getKa(){
	return ka;
}

Vector Triangle::getKd(){
	return kd;
}

Vector Triangle::getKs(){
	return ks;
}

float Triangle::getP(){
	return p;
}

Vector Triangle::getKr(){
	return kr;
}

Vector Triangle::getNormal(){
      Vector v1v2 = Vector::add(v2, Vector::scale(-1.0, v1));
      Vector v1v3 = Vector::add(v3, Vector::scale(-1.0, v1));
      Vector normal = Vector::normalize(Vector::cross(v1v2, v1v3));
      return normal;
}