#pragma once
#include <math.h>

class Vector3d
{
public:
	Vector3d();
	Vector3d(double _x, double _y, double _z);

	Vector3d operator + (Vector3d vector);
	Vector3d operator - (Vector3d vector);
	Vector3d operator * (double number);
	Vector3d operator / (double number);

	double x, y, z;
};

Vector3d vector_normal(Vector3d vec1, Vector3d vec2);
double norm(Vector3d vec);
Vector3d normalization(Vector3d vec);
double scalar_product(Vector3d vec1, Vector3d vec2);
Vector3d euclidian_vector(Vector3d point1, Vector3d point2);
Vector3d vertex_normal(Vector3d point1, Vector3d point2, Vector3d point3);
