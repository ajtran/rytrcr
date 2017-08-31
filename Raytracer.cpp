#include "Raytracer.h"

Raytracer::Raytracer(Shader shdr, vector<Sphere> sphs, vector<Triangle> tris, Vector eyePos){
	shader = shdr;
	spheres = sphs;
	triangles = tris;
	eye = eyePos;

}

float Raytracer::intersectSph(Vector direction, Vector source, Sphere sphere){
	float radiusSquared = pow(sphere.getRadius(), 2);
	float a = Vector::sum(Vector::square(direction));
	float b = 2 * Vector::sum(Vector::multiply(Vector::add(source, Vector::scale(-1, sphere.getCenter())), direction));
	float c = Vector::sum(Vector::square(Vector::add(source, Vector::scale(-1, sphere.getCenter())))) - radiusSquared;
	float discriminant = pow(b, 2) - (4 * a * c);

	if (discriminant < 0) {
		return 0.0;
	}

	float tPlus = (-b + pow(pow(b, 2) - 4 * a * c, 0.5))/(2*a);
	float tMinus = (-b - pow(pow(b, 2) - 4 * a * c, 0.5))/(2*a);

	if ((tPlus <= 0) && (tMinus <= 0)) {
		return 0.0;
	}

	return fmin(tPlus, tMinus);
}

float Raytracer::intersectTri(Vector direction, Vector source, Triangle triangle) {
	Vector v1 = triangle.getV1();
	Vector v2 = triangle.getV2();
	Vector v3 = triangle.getV3();
	Vector intersection = Vector(0.0, 0.0, 0.0);
	float beta = 0.0;
	float gamma = 0.0;
	float t = 0.0;
	float dot = 0.0;
	float area = 0.0;

	Vector v1v2 = Vector::add(v2, Vector::scale(-1.0, v1));
	Vector v1v3 = Vector::add(v3, Vector::scale(-1.0, v1));
	Vector v2v3 = Vector::add(v3, Vector::scale(-1.0, v2));

	// find the normal of the plane
	Vector normal = Vector::cross(v1v2, v1v3);

	area = pow(Vector::sum(Vector::square(normal)), 0.5);

	float dotProduct = Vector::dotProduct(normal, direction);
	if ((dotProduct < 0.00001) && (dotProduct > 0.00001)) {
		return 0.0;
	}

	dot = Vector::dotProduct(normal, v1);
	t = (Vector::dotProduct(normal, source) + dot) / (Vector::dotProduct(normal, direction));
	if (t < 0) {
		return 0.0;
	}

	intersection = Vector::add(source, Vector::scale(t, direction)); //P

	Vector intersectv1 = Vector::add(intersection, Vector::scale(-1.0, v1));
	Vector cross = Vector::cross(v1v2, intersectv1);
	// beta = pow(Vector::sum(Vector::square(cross)), 0.5);

	if (Vector::dotProduct(normal, cross) < 0) {
		return 0.0;
	}

	Vector intersectv2 = Vector::add(intersection, Vector::scale(-1.0, v2));
	cross = Vector::cross(v2v3, intersectv2);
	beta = pow(Vector::sum(Vector::square(cross)), 0.5);


	if (Vector::dotProduct(normal, cross) < 0) {
		return 0.0;
	}

	Vector intersectv3 = Vector::add(intersection, Vector::scale(-1.0, v3));
	cross = Vector::cross(Vector::scale(-1.0, v1v3), intersectv3);
	gamma = pow(Vector::sum(Vector::square(cross)), 0.5);

	if (Vector::dotProduct(normal, cross) < 0) {
		return 0.0;
	}

	return t;
}


Vector Raytracer::trace(Vector rayDirection, Vector source, int depth) {
  Vector value = Vector(0.0, 0.0, 0.0);

  // FIND CLOSEST INTERSECTING OBJECT
  float t;
	float minT = INT_MAX;
        
  bool sphere = false;        
  int closestSphereIndex = -1;

  rayDirection = Vector::normalize(rayDirection);
  Sphere unitSph = Sphere(Vector(0, 0, 0), 1, Vector(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0), 0, Vector(0, 0, 0), Matrix());

  Matrix transform;
	for (int s = 0; s < spheres.size(); s++) {
    transform = Matrix::inverse4(spheres[s].getM());
    t = intersectSph(Matrix::multiplyVector(transform, rayDirection, true), Matrix::multiplyVector(transform, source, false), unitSph);

		if (t > 0.0) {
      if (t < minT) {
        minT = t;
        sphere = true;
        closestSphereIndex = s;
      }
    }
  }
    
  bool triangle = false;
  int trindex = -1;

  Matrix toOrigin;
  for (int tr = 0; tr < triangles.size(); tr++) {
    Triangle currTri = triangles[tr];
    transform = Matrix::inverse4(currTri.getM());
    t = intersectTri(Matrix::multiplyVector(transform, rayDirection, true), Matrix::multiplyVector(transform, source, false), currTri);

    if (t > 0.0) {
      if (t < minT) {
        minT = t;
        triangle = true;
        sphere = false;
        trindex = tr;
      }
    }
  }

  if (minT == INT_MAX) {
    return value;
  }

  Matrix rightTransform;
  Vector pointOnSurface;
  if (sphere) {
    rightTransform = Matrix::inverse4(spheres[closestSphereIndex].getM());
  } else if (triangle) {
    rightTransform = Matrix::inverse4(triangles[trindex].getM());
  }
  pointOnSurface = Vector::add(Matrix::multiplyVector(rightTransform, source, false), Vector::scale(minT, Matrix::multiplyVector(rightTransform, rayDirection, true)));

  // DO NORMALS
  Vector normal;
  Vector traced;
  Vector bounceDirection;
  if (triangle) {
    normal = Vector::normalize(Matrix::multiplyVector(Matrix::transpose(rightTransform), triangles[trindex].getNormal(), true));
  } else if (sphere) {
    normal = Vector::normalize(Matrix::multiplyVector(Matrix::transpose(rightTransform), pointOnSurface, true));
  }

  // DO NORMAL PHONG SHADING FOR DIRECTIONAL LIGHTS
  vector<Vector> dls = shader.getDls();
  vector<Vector> dis = shader.getDis();

	for (int d = 0; d < dls.size(); d++) {
    Vector lightDirection = Vector::scale(-1.0, dls[d]);
		bool blocked = false;
		for (int s = 0; s < spheres.size(); s++) {
			if (s != closestSphereIndex) {
        Matrix trans = Matrix::inverse4(spheres[s].getM());
        if (sphere) {
          t = intersectSph(Matrix::multiplyVector(trans, lightDirection, true), Matrix::multiplyVector(trans, Matrix::multiplyVector(spheres[closestSphereIndex].getM(), pointOnSurface, false), false), unitSph);
        } else if (triangle) {
          t = intersectSph(Matrix::multiplyVector(trans, lightDirection, true), Matrix::multiplyVector(trans, Matrix::multiplyVector(triangles[trindex].getM(), pointOnSurface, false), false), unitSph);
        }
				if (t > 0.0) {
					blocked = true;
					break;
				}
			}
	  }
    for (int tr = 0; tr < triangles.size(); tr++) {
      if (tr != trindex) {
        Matrix trans = Matrix::inverse4(triangles[tr].getM());
        if (sphere) {
          t = intersectSph(Matrix::multiplyVector(trans, lightDirection, true), Matrix::multiplyVector(trans, Matrix::multiplyVector(spheres[closestSphereIndex].getM(), pointOnSurface, false), false), unitSph);
        } else if (triangle) {
          t = intersectSph(Matrix::multiplyVector(trans, lightDirection, true), Matrix::multiplyVector(trans, Matrix::multiplyVector(triangles[trindex].getM(), pointOnSurface, false), false), unitSph);
        }
        if (t > 0.0) {
          blocked = true;
          break;
        }
      }
    }

    Vector phong;
    if (triangle) {
      if (blocked) {
        phong = shader.phong(triangles[trindex].getKa(), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), lightDirection, normal,
                        dis[d], triangles[trindex].getP(), rayDirection);
      } else {
        phong = shader.phong(triangles[trindex].getKa(), triangles[trindex].getKd(), triangles[trindex].getKs(), lightDirection, normal,
                        dis[d], triangles[trindex].getP(), rayDirection);
      }
    } else if (sphere) {
		  if (blocked) {
        phong = shader.phong(spheres[closestSphereIndex].getKa(), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), lightDirection, normal,
                      dis[d], spheres[closestSphereIndex].getP(), rayDirection);
			}	else {
				phong = shader.phong(spheres[closestSphereIndex].getKa(), spheres[closestSphereIndex].getKd(), spheres[closestSphereIndex].getKs(), lightDirection, normal,
								     	dis[d], spheres[closestSphereIndex].getP(), rayDirection);
			}
    }
    value = Vector::add(value, phong);
	}

  // DO NORMAL PHONG SHADING FOR POINT LIGHTS
  vector<Vector> pls = shader.getPls();
  vector<Vector> pis = shader.getPis();
	for (int p = 0; p < pls.size(); p++) {
    Vector lightDirection = Vector::add(pointOnSurface, Vector::scale(-1.0, pls[p]));
    bool blocked = false;
    for (int s = 0; s < spheres.size(); s++) {
      if (s != closestSphereIndex) {
        Matrix trans = Matrix::inverse4(spheres[s].getM());
        if (sphere) {
          t = intersectSph(Matrix::multiplyVector(trans, lightDirection, true), Matrix::multiplyVector(trans, Matrix::multiplyVector(spheres[closestSphereIndex].getM(), pointOnSurface, false), false), unitSph);
        } else if (triangle) {
          t = intersectSph(Matrix::multiplyVector(trans, lightDirection, true), Matrix::multiplyVector(trans, Matrix::multiplyVector(triangles[trindex].getM(), pointOnSurface, false), false), unitSph);
        }
        if (t > 0.0) {
          blocked = true;
          break;
        }
      }
    }
    for (int tr = 0; tr < triangles.size(); tr++) {
      if (tr != trindex) {
        Matrix trans = Matrix::inverse4(triangles[tr].getM());
        if (sphere) {
          t = intersectSph(Matrix::multiplyVector(trans, lightDirection, true), Matrix::multiplyVector(trans, Matrix::multiplyVector(spheres[closestSphereIndex].getM(), pointOnSurface, false), false), unitSph);
        } else if (triangle) {
          t = intersectSph(Matrix::multiplyVector(trans, lightDirection, true), Matrix::multiplyVector(trans, Matrix::multiplyVector(triangles[trindex].getM(), pointOnSurface, false), false), unitSph);
        }
        if (t > 0.0) {
          blocked = true;
          break;
        }
      }
    }

    Vector phong;
    if (triangle) {
      if (blocked) {
        phong = shader.phong(triangles[trindex].getKa(), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), Vector::add(pls[p], Vector::scale(-1.0, pointOnSurface)), normal,
                        pis[p], triangles[trindex].getP(), rayDirection);
      } else {
        phong = shader.phong(triangles[trindex].getKa(), triangles[trindex].getKd(), triangles[trindex].getKs(), Vector::add(pls[p], Vector::scale(-1.0, pointOnSurface)), normal,
                        pis[p], triangles[trindex].getP(), rayDirection);
      }
    } else if (sphere) {
      if (blocked) {
        phong = shader.phong(spheres[closestSphereIndex].getKa(), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), Vector::add(pls[p], Vector::scale(-1.0, pointOnSurface)), Vector::normalize(Vector::add(pointOnSurface, Vector::scale(-1.0, spheres[closestSphereIndex].getCenter()))),
                        pis[p], spheres[closestSphereIndex].getP(), rayDirection);
      } else {
        phong = shader.phong(spheres[closestSphereIndex].getKa(), spheres[closestSphereIndex].getKd(), spheres[closestSphereIndex].getKs(), Vector::add(pls[p], Vector::scale(-1.0, pointOnSurface)), Vector::normalize(Vector::add(pointOnSurface, Vector::scale(-1.0, spheres[closestSphereIndex].getCenter()))),
                        pis[p], spheres[closestSphereIndex].getP(), rayDirection);
      }
    }
    value = Vector::add(value, phong);

  }

  // DO REFLECTIONS
  if (triangle) {
    if ((Vector::sum(triangles[trindex].getKr())) && (depth > 0)) {
      Vector bounceDirection = Vector::reflectedRay(rayDirection, triangles[trindex].getNormal());
      traced = trace(bounceDirection, Matrix::multiplyVector(triangles[trindex].getM(), pointOnSurface, false), depth - 1);
      if (Vector::sum(traced) > 0) {
        value = Vector::add(value, Vector::add(triangles[trindex].getKa(), Vector::multiply(triangles[trindex].getKr(), traced)));
      }
    } 
  } else if (sphere) {
    if (Vector::sum(spheres[closestSphereIndex].getKr()) && (depth > 0)) {
      bounceDirection = Vector::normalize(Vector::reflectedRay(Vector::normalize(rayDirection), normal));
      traced = trace(bounceDirection, Matrix::multiplyVector(spheres[closestSphereIndex].getM(), pointOnSurface, false), depth - 1);
      if (Vector::sum(traced) > 0) {
        value = Vector::add(value, Vector::add(spheres[closestSphereIndex].getKa(), Vector::multiply(spheres[closestSphereIndex].getKr(), traced)));
      }
    }
  }
  return value;
}
