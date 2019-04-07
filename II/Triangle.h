#pragma once
#include "Constants.h"
#include "Matrix.h"

struct Triangle {

	Vector3d first;
	Vector3d second;
	Vector3d third;
};

vector <Triangle> figure;
Triangle triangle;

Triangle transofrm(int section, double angle, Vector3d axis, Vector3d shift) {

	Triangle trngl;
	trngl.first = triangle.first;
	trngl.second = triangle.second;
	trngl.third = triangle.third;

	if (angle != 0.0f) {

		initializeRotationMatrix(angle, axis);
		trngl.first = multCoordinate(rotationMatrix, trngl.first);
		trngl.second = multCoordinate(rotationMatrix, trngl.second);
		trngl.third = multCoordinate(rotationMatrix, trngl.third);
	}

	initializeScaleMatrix(sectionScaling[section].x, sectionScaling[section].y, sectionScaling[section].z);
	trngl.first = multCoordinate(scaleMatrix, trngl.first);
	trngl.second = multCoordinate(scaleMatrix, trngl.second);
	trngl.third = multCoordinate(scaleMatrix, trngl.third);

	initializeShearMatrix(shift.x, shift.y, shift.z);
	trngl.first = multCoordinate(shearMatrix, trngl.first);
	trngl.second = multCoordinate(shearMatrix, trngl.second);
	trngl.third = multCoordinate(shearMatrix, trngl.third);
}

void replication() {

	FILE *triangleFile;
	FILE *trajectoryFile;
	FILE *percentsFile;

	fopen_s(&triangleFile, "triangle.txt", "r");
	fopen_s(&trajectoryFile, "trajectory.txt", "r");
	fopen_s(&percentsFile, "percents.txt", "r");

	fscanf_s(triangleFile, "%f%f%f", &triangle.first.x, &triangle.first.y, &triangle.first.z);
	fscanf_s(triangleFile, "%f%f%f", &triangle.second.x, &triangle.second.y, &triangle.second.z);
	fscanf_s(triangleFile, "%f%f%f", &triangle.third.x, &triangle.third.y, &triangle.third.z);
	fclose(triangleFile);

	Vector3d coord;
	double angle;
	while (!feof(trajectoryFile)) {

		fscanf_s(trajectoryFile, "%f%f%f", &coord.x, &coord.y, &coord.z);
		replicationPath.push_back(coord);
	}
	fclose(trajectoryFile);

	Vector3d scale;
	double percent;
	while (!feof(percentsFile)) {

		fscanf_s(percentsFile, "%f", &percent);
		fscanf_s(percentsFile, "%f%f%f", &scale.x, &scale.y, &scale.z);
		percents.push_back(percent);
		sectionScaling.push_back(scale);
	}
	fclose(percentsFile);
	
	Vector3d axis;
	Vector3d previousPath = vertex_normal(triangle.first, triangle.second, triangle.third);
	Vector3d currentPath;
	Triangle trngl;

	double pathLength = 0;

	for (int i = 0; i < replicationPath.size(); ++i) {

		currentPath = replicationPath[i + 1] - replicationPath[i];
		pathLength += norm(currentPath);
	}

	for (int i = 0; i < percents.size(); ++i) {

		double pointDistance = (pathLength * percents[i]) / 100.0f;

		Vector3d currentPathDirection;
		double currentLength;
		double previousLength;
		bool isFound = false;

		int pathStart;

		if (i == percents.size() - 1) {

			pathStart = replicationPath.size() - 2;
		} else {

			for (int j = 0; i < replicationPath.size() - 1, !isFound; ++j) {

				currentPathDirection = replicationPath[j + 1] - replicationPath[j];
				currentLength += norm(currentPathDirection);

				if (pointDistance >= previousLength && pointDistance <= currentLength) {

					isFound = true;
				} else {

					previousLength = currentLength;
				}

				pathStart = j - 1;
			}
			currentPath = replicationPath[pathStart + 1] - replicationPath[pathStart];

			double localLength = pointDistance - previousLength;
			if (i == percents.size() - 1) {

				localLength = norm(currentPath);
			}
			double currentPathNorm = norm(currentPath);

			Vector3d shift = Vector3d(replicationPath[pathStart].x + (localLength * currentPath.x) / currentPathNorm,
				replicationPath[pathStart].y + (localLength * currentPath.y) / currentPathNorm,
				replicationPath[pathStart].z + (localLength * currentPath.z) / currentPathNorm);

			axis = vector_normal(currentPath, previousPath);

			angle = acos(scalar_product(currentPath, previousPath) / (norm(currentPath) * norm(previousPath)))
				* 180.0 / M_PI;

			if (scalar_product(currentPath, previousPath) < 0) {
				
				angle = 180 - angle;
			} else {

				angle = -(180 + angle);
			}

			if (angle == 180) {

				angle = 0;
			}

			trngl = transofrm(i, angle, axis, shift);
			figure.push_back(trngl);
		}
	}
}

void calcNormals() {

	Vector3d normal = vertex_normal(figure[0].first, figure[0].second, figure[0].third);
	normals.push_back(normal);

	for (int i = 0; i < figure.size() - 1; ++i) {

		normal = vertex_normal(figure[i].second, figure[i].first, figure[i + 1].first);
		normals.push_back(normal);

		normal = vertex_normal(figure[i].first, figure[i].third, figure[i + 1].third);
		normals.push_back(normal);

		normal = vertex_normal(figure[i].third, figure[i].second, figure[i + 1].second);
		normals.push_back(normal);
	}

	normal = vertex_normal(figure[figure.size() - 1].first, figure[figure.size() - 1].third,
		figure[figure.size()].second);
	normals.push_back(normal);
}

void calcSmoothedNormals() {

	Vector3d smoothedNormal = (normals[0] + normals[1] + normals[2]) / 3.0;
	smoothedNormals.push_back(smoothedNormal);
	
	smoothedNormal = (normals[0] + normals[1] + normals[3]) / 3.0;
	smoothedNormals.push_back(smoothedNormal);

	smoothedNormal = (normals[0] + normals[2] + normals[3]) / 3.0;
	smoothedNormals.push_back(smoothedNormal);

	for (int i = 0, int num = 1; i < figure.size() - 1; ++i, num += 3) {

		smoothedNormal = (normals[num] + normals[num + 1] + normals[num + 3] + normals[num + 4]) / 4.0;
		smoothedNormals.push_back(smoothedNormal);

		smoothedNormal = (normals[num] + normals[num + 2] + normals[num + 3] + normals[num + 5]) / 4.0;
		smoothedNormals.push_back(smoothedNormal);

		smoothedNormal = (normals[num + 1] + normals[num + 2] + normals[num + 4] + normals[num + 5]) / 4.0;
		smoothedNormals.push_back(smoothedNormal);
	}

	int last = normals.size() - 1;
	smoothedNormal = (normals[last] + normals[last - 2] + normals[last - 3]) / 3.0;
	smoothedNormals.push_back(smoothedNormal);

	smoothedNormal = (normals[last] + normals[last - 1] + normals[last - 3]) / 3.0;
	smoothedNormals.push_back(smoothedNormal);

	smoothedNormal = (normals[last] + normals[last - 1] + normals[last - 2]) / 3.0;
	smoothedNormals.push_back(smoothedNormal);
}

