#include "Normal.h"

Vector3d::Vector3d() {};

Vector3d::Vector3d(double _x, double _y, double _z) {

	x = _x;
	y = _y;
	z = _z;
}

Vector3d Vector3d::operator + (Vector3d vector) {

	return Vector3d(vector.x + x, vector.y + y, vector.z + z);
}

Vector3d Vector3d::operator - (Vector3d vector) {

	return Vector3d(x - vector.x, y - vector.y, z - vector.z);
}

Vector3d Vector3d::operator * (double number) {

	return Vector3d(x * number, y * number, z * number);
}

Vector3d Vector3d::operator / (double number) {

	return Vector3d(x / number, y / number, z / number);
}

Vector3d vector_normal(Vector3d vec1, Vector3d vec2) {

	Vector3d normal;

	normal.x = ((vec1.y * vec2.z) - (vec1.z * vec2.y));
	normal.y = ((vec1.z * vec2.x) - (vec1.x * vec2.z));
	normal.z = ((vec1.x * vec2.y) - (vec1.y * vec2.x));

	return normal;
}

double norm(Vector3d vec) {

	return (double)sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

Vector3d normalization(Vector3d vec) {

	return vec / norm(vec);
}

double scalar_product(Vector3d vec1, Vector3d vec2) {

	return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

Vector3d euclidian_vector(Vector3d point1, Vector3d point2) {

	Vector3d vector;

	vector.x = point1.x - point2.x;
	vector.y = point1.y - point2.y;
	vector.z = point1.z - point2.z;

	return vector;
}

Vector3d vertex_normal(Vector3d point1, Vector3d point2, Vector3d point3) {

	Vector3d vec1 = euclidian_vector(point3, point2);
	Vector3d vec2 = euclidian_vector(point2, point1);
	Vector3d normal = vector_normal(vec1, vec2);
	
	return normalization(normal);
}