#include "Camera.h"

Camera::Camera() {};

void Camera::set_position(double posX, double posY, double posZ,
	double viewX, double viewY, double viewZ,
	double sceneX, double sceneY, double sceneZ) {

	position = Vector3d(posX, posY, posZ);
	view = Vector3d(viewX, viewY, viewZ);
	scene = Vector3d(sceneX, sceneY, sceneZ);
}

void Camera::set_view_by_mouse(GLint width, GLint height) {

	POINT mousePos;

	int centerX = width / 2.0f;
	int centerY = height / 2.0f;

	double angleY = 0.0f;
	double angleZ = 0.0f;
	double currentAngleX = 0.0f;

	GetCursorPos(&mousePos);
	if (mousePos.x == centerX && mousePos.y == centerY) return;

	SetCursorPos(centerX, centerY);

	angleY = (double)((centerX - mousePos.x)) / 1000.0f;
	angleZ = (double)((centerY - mousePos.y)) / 1000.0f;

	double lastAngleX = currentAngleX;

	if (currentAngleX > 1.0f) {

		currentAngleX = 1.0f;
		if (lastAngleX != 1.0f) {

			auto axis = vector_normal(view - position, scene);
			axis = normalization(axis);
			rotation(1.0f - lastAngleX, axis.x, axis.y, axis.z);
		}
	} else if (currentAngleX < -1.0f) {

		currentAngleX = -1.0f;
		if (lastAngleX != -1.0f) {

			auto axis = vector_normal(view - position, scene);
			axis = normalization(axis);
			rotation(-1.0f - lastAngleX, axis.x, axis.y, axis.z);
		}
	} else {

		auto axis = vector_normal(view - position, scene);
		axis = normalization(axis);
		rotation(angleZ, axis.x, axis.y, axis.z);
	}

	rotation(angleY, 0, 1, 0);
}

void Camera::move_depth(double speed) {

	auto direction = view - position;
	auto x = direction.x;
	auto z = direction.z;

	position.x += x * speed;
	position.z += z * speed;

	view.x += x * speed;
	view.z += z * speed;
}

void Camera::move_horizontal(double speed) {

	auto direction = view - position;
	auto x = direction.x;
	auto y = direction.y;
	auto z = direction.z;

	x = x * cos(M_PI / 2.) - y * sin(M_PI / 2.);
	z = y * cos(M_PI / 2.) + x * sin(M_PI / 2.);

	position.x += x * speed;
	position.z += z * speed;

	view.x += x * speed;
	view.z += z * speed;
}

void Camera::move_vertical(double speed) {

	position.y += speed;
	view.y += speed;
}

void Camera::rotation(double angle, double x, double y, double z) {

	auto currentDirection = view - position;

	double cosA = (double)cos(angle);
	double sinA = (double)sin(angle);

	Vector3d direction;

	direction.x = (cosA + (1 - cosA) * x * x) * currentDirection.x;
	direction.x += (((1 - cosA) * x * y) - (z * sinA)) * currentDirection.y;
	direction.x += (((1 - cosA) * x * z) + (y * sinA)) * currentDirection.z;

	direction.y = (((1 - cosA) * x * y) + (z * sinA)) * currentDirection.x;
	direction.y += (cosA + (1 - cosA) * y * y) * currentDirection.y;
	direction.y += (((1 - cosA) * y * z) + (x * sinA)) * currentDirection.z;

	direction.z = (((1 - cosA) * x * z) - (y * sinA)) * currentDirection.x;
	direction.z += (((1 - cosA) * y * z) + (x * sinA)) * currentDirection.y;
	direction.z += (cosA + (1 - cosA) * z * z) * currentDirection.z;

	view = position + direction;
}

void Camera::rotation_by_point(Vector3d center, double angle, double x, double y, double z) {

	auto axis = position - center;

	double cosA = (double)cos(angle);
	double sinA = (double)sin(angle);

	Vector3d direction;

	direction.x = (cosA + (1 - cosA) * x * x) * axis.x;
	direction.x += (((1 - cosA) * x * y) - (z * sinA)) * axis.y;
	direction.x += (((1 - cosA) * x * z) + (y * sinA)) * axis.z;

	direction.y = (((1 - cosA) * x * y) + (z * sinA)) * axis.x;
	direction.y += (cosA + (1 - cosA) * y * y) * axis.y;
	direction.y += (((1 - cosA) * y * z) + (x * sinA)) * axis.z;

	direction.z = (((1 - cosA) * x * z) - (y * sinA)) * axis.x;
	direction.z += (((1 - cosA) * y * z) + (x * sinA)) * axis.y;
	direction.z += (cosA + (1 - cosA) * z * z) * axis.z;

	view = position + direction;
}