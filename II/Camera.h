#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
#include "glut.h" 
#include <vector>
#include <GL\GL.H>
#include "Normal.h"

class Camera {

public:
	Vector3d position;
	Vector3d view;
	Vector3d scene;

	Camera();
	void set_position(double posX, double posY, double posZ,
		double viewX, double viewY, double viewZ,
		double sceneX, double sceneY, double sceneZ);

	void set_view_by_mouse(GLint width, GLint height);
	void move_depth(double speed);
	void move_horizontal(double speed);
	void move_vertical(double speed);
	void rotation(double angle, double x, double y, double z);
	void rotation_by_point(Vector3d center, double angle, double x, double y, double z);
};