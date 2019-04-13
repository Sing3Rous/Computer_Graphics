#include "Constants.h"

Vector3d multCoordinate(double matrix[4][4], Vector3d coordinate) {

	double coord[4] = { coordinate.x, coordinate.y, coordinate.z, 1.0f };
	double result[4];

	for (int i = 0; i < 4; ++i) {

		double sum = 0;
		for (int j = 0; j < 4; ++j) {

			sum += matrix[i][j] * coord[j];
		}
		result[i] = sum;
	}
	return Vector3d(result[0], result[1], result[2]);
}

void initializeShearMatrix(double x, double y, double z) {

	shearMatrix[0][0] = 1; shearMatrix[0][1] = 0;
	shearMatrix[0][2] = 0; shearMatrix[0][3] = x;
	shearMatrix[1][0] = 0; shearMatrix[1][1] = 1;
	shearMatrix[1][2] = 0; shearMatrix[1][3] = y;
	shearMatrix[2][0] = 0; shearMatrix[2][1] = 0;
	shearMatrix[2][2] = 1; shearMatrix[2][3] = z;
	shearMatrix[3][0] = 0; shearMatrix[3][1] = 0;
	shearMatrix[3][2] = 0; shearMatrix[3][3] = 1;
}

void initializeRotationMatrix(double angle, Vector3d axis) {

	double cosA = (double)cos(angle * M_PI / 180.0);
	double sinA = (double)sin(angle * M_PI / 180.0);
	Vector3d normalizedAxis = normalization(axis);

	rotationMatrix[0][0] = cosA + (1 - cosA) * normalizedAxis.x * normalizedAxis.x;
	rotationMatrix[0][1] = (1 - cosA) * normalizedAxis.x * normalizedAxis.y - sinA * normalizedAxis.z;
	rotationMatrix[0][2] = (1 - cosA) * normalizedAxis.x * normalizedAxis.z + sinA * normalizedAxis.y;
	rotationMatrix[0][3] = 0;
	rotationMatrix[1][0] = (1 - cosA) * normalizedAxis.x * normalizedAxis.y + sinA * normalizedAxis.z;
	rotationMatrix[1][1] = cosA + (1 - cosA) * normalizedAxis.y * normalizedAxis.y;
	rotationMatrix[1][2] = (1 - cosA) * normalizedAxis.z * normalizedAxis.y - sinA * normalizedAxis.x;
	rotationMatrix[1][3] = 0;
	rotationMatrix[2][0] = (1 - cosA) * normalizedAxis.x * normalizedAxis.z - sinA * normalizedAxis.y;
	rotationMatrix[2][1] = (1 - cosA) * normalizedAxis.z * normalizedAxis.y + sinA * normalizedAxis.x;
	rotationMatrix[2][2] = cosA + (1 - cosA) * normalizedAxis.z * normalizedAxis.z;
	rotationMatrix[2][3] = 0;
	rotationMatrix[3][0] = 0;
	rotationMatrix[3][1] = 0;
	rotationMatrix[3][2] = 0;
	rotationMatrix[3][3] = 1;
}

void initializeScaleMatrix(double x, double y, double z) {

	scaleMatrix[0][0] = x; scaleMatrix[0][1] = 0;
	scaleMatrix[0][2] = 0; scaleMatrix[0][3] = 0;
	scaleMatrix[1][0] = 0; scaleMatrix[1][1] = y;
	scaleMatrix[1][2] = 0; scaleMatrix[1][3] = 0;
	scaleMatrix[2][0] = 0; scaleMatrix[2][1] = 0;
	scaleMatrix[2][2] = z; scaleMatrix[2][3] = 0;
	scaleMatrix[3][0] = 0; scaleMatrix[3][1] = 0;
	scaleMatrix[3][2] = 0; scaleMatrix[3][3] = 1;
}