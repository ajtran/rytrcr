#include "Shader.h"
#include <iostream>

Shader::Shader() {
	// don't do anything?
}

Shader::Shader(vector<Vector> pls, vector<Vector> pis, vector<Vector> dls, vector<Vector> dis) {
	pointLights = pls;
	pointRGBs = pis;
	directLights = dls;
	directRGBs = dis;
}

// float Shader::anisotropic(float pu, float pv, Vector l, Vector n, bool point, Vector normv) {
// 	n = Vector::normalize(n);
// 	if (point) {
// 		l = Vector::add(Vector::scale(-1.0, l), n);
// 	}
// 	Vector h = Vector::normalize(Vector::half(Vector::normalize(l), normv));
// 	Vector u = Vector(0.0, 0.0, 0.0);
// 	Vector v = Vector(0.0, 0.0, 0.0);
// 	Vector y = Vector(0.0, n.arr[1], 0.0);
// 	Vector subtract = Vector::add(y, Vector::scale(-1, n));
// 	float dp = Vector::dotProduct(y, n);
// 	v = Vector::normalize(Vector::add(Vector::scale(dp, Vector::scale(-1, n)), y));

// 	// v =Vector::normalize(scale(dp, subtract));
// 	u = Vector::normalize(Vector::cross(v, n));
// 		return ((pu * pow(Vector::dotProduct(h, u), 2) + (pv * pow(Vector::dotProduct(h, v), 2)))) / (1 - pow(Vector::dotProduct(h, n), 2));
// }

Vector Shader::phong(Vector ka, Vector kd, Vector ks, Vector l, Vector n, Vector i, float p, Vector normv) {
	// Vector normn = Vector::normalize(n);
	Vector normn = n;

	// if (point) {
	// 	l = Vector::add(Vector::scale(-1.0, l), Vector::scale(1.0, normn));
	// 	// l.print();
	// }
	Vector norml = Vector::normalize(l);
	Vector normr = Vector::normalize(Vector::rFunc(Vector::scale(-1.0, norml), normn));
	Vector ambient = Vector::multiply(ka, i);
	// most recent change: 1.0 -> -1.0
	Vector diffuse = Vector::scale(fmax(Vector::dotProduct(Vector::scale(1.0, norml), normn), 0.0),Vector::multiply(kd, i));
	// cout << "diffuse term";
	// kd.print();
	// cout << fmax(Vector::dotProduct(Vector::scale(1.0, norml), normn), 0.0);
	// cout << endl;
	Vector specular = Vector::scale(pow(fmax(Vector::dotProduct(normr, normv), 0.0), p), Vector::multiply(ks, i));
	return Vector::add(Vector::add(ambient, diffuse), specular);
}

vector<Vector> Shader::getPls() {
	return pointLights;
}

vector<Vector> Shader::getPis() {
	return pointRGBs;
}

vector<Vector> Shader::getDls() {
	return directLights;
}

vector<Vector> Shader::getDis() {
	return directRGBs;
}

// Vector Shader::shading(Vector point, Vector normv) {	
// 	Vector n = point;
// 	vector<Vector> dls = directLights;
// 	vector<Vector> dis = directRGBs;
// 	vector<Vector> pls = pointLights;
// 	vector<Vector> pis = pointRGBs;

// 	// Vector normv = Vector::normalize(Vector::add(eyePos, Vector::scale(-1.0, point)));
// 	// normv.print();
// 	// normv.print();
// 	// normv = Vector(0.0,0.0,-1.0);

// 	bool iso = true;
// 	float pu = 1.0;
// 	float pv = 1.0;
	
// 	Vector value = Vector(0.0, 0.0, 0.0);

// 	for (int d = 0; d < dls.size(); d++) {
// 		// but this iso, aniso stuff doesnt really matter....
// 		// if (not iso) {
// 		// 	p = Shader::anisotropic(pu, pv, dls[d], n, false, normv);
// 		// }
// 		// value = Vector::add(value, Shader::phong(ka, kd, ks, dls[d], n, dis[d], p, false, normv));
// 	}
// 	for (int c = 0; c < pls.size(); c++) {
// 		// if (not iso) {
// 		// 	p = Shader::anisotropic(pu, pv, pls[c], n, true, normv);
// 		// }
// 		// value = Vector::add(value, Shader::phong(ka, kd, ks, pls[c], n, pis[c], p, true, normv));
// 		// value.print();/
// 	}
// 	return value;
// }