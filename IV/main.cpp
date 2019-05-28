#include "Spline.h"
#include <string>

using namespace std;

int n = 0;
double scale = 1.0;
Spline spline;
void display();
int dx = 0, dy = 0;

void reshape(int width, int height) {

	Width = width;
	Height = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, 2, 12);
	gluLookAt(0, 0, 5, dx, dy, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1, 1, 1, 0);
}
void  Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		spline.add((10 * double(x) / Width - 5) / scale, (5 - 10 * double(y) / Height) / scale);
	}

	display();
}
void CoordSystem() {

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex2f(-9, 0);
	glVertex2f(9, 0);
	glVertex2f(0, -9);
	glVertex2f(0, 9);
	glEnd();
	glRasterPos2d(-0.1,9.8);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15,'y');
	glRasterPos2d(9.8,-0.15);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15,'x');
	glRasterPos2d(0.1, 0.1);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	double num = 0.8;
	for (int i = 0; i < 9; ++i) {

		glRasterPos2d(0.1, num);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, to_string(i + 1)[0]);
		num = num + 1;
	}

	double y = -0.8;
	for (int i = 0; i < 9; ++i) {

		glRasterPos2d(0.1, y);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
		y = y - 1;
	}

	num = -0.8;
	for (int i = 0; i < 9; ++i) {

		glRasterPos2d(0.2, num);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, to_string(i + 1)[0]);
		num = num - 1;
	}

	num = 0.8;
	for (int i = 0; i < 9; ++i) {

		glRasterPos2d(num, 0.1);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, to_string(i + 1)[0]);
		num = num + 1;
	}


	y = -0.8;
	for (i = 0; i < 9; i++) {

		glRasterPos2d(y, 0.1);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
		y = y - 1;
	}

	num = -0.7;
	for (int i = 0; i < 9; ++i) {

		glRasterPos2d(num, 0.1);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, to_string(i + 1)[0]);
		num = num - 1;
	}
}

void Key(unsigned char key, int x, int y) {

	if (key == '+') {

		glScalef(1.1, 1.1, 0);
		n++;
		scale *= 1.1;
	}
	if (key == '-') {

		glScalef(0.9, 0.9, 0);
		n--;
		scale *= 0.9;
	}
	display();
}

void display() {

	CoordSystem();
	if (spline.build()) {

		spline.draw();
	}
	glutSwapBuffers();
}
 
void Init(void) {

	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Width, 0.0, Height, -1.0, 1.0);
	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Computer Graphics IV"); //кусочно-квадратичный интерполяционный сплайн
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Key);
	Init();
	glutMainLoop();
	return 0;
}

