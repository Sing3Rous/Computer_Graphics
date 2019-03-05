#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <gl/freeglut.h>
#include <vector>

using namespace std;
using namespace glm;

//-------------------------------------------------------------------------------------------

struct type_color {
	GLint r, g, b;
	type_color() { r = 0; g = 0; b = 0; }
	type_color(GLint _r, GLint _g, GLint _b) { r = _r, g = _g, b = _b; }
};

struct type_point {
	GLint x, y;
	type_point() { x = 0; y = 0; }
	type_point(GLint _x, GLint _y) { x = _x; y = _y; }
};

struct type_primitive {
	vector <type_point> points;
	type_color color;
	bool isFill = true;
	int currentPoint = -1;
};

//-------------------------------------------------------------------------------------------

GLint Width = 512, Height = 512;

vector <type_primitive> primitives(1);

int currentPrimitive = 0;

type_point menuPoint;

//-------------------------------------------------------------------------------------------

void Display(void) {

	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//drawing all primitives
	for (int i = 0; i < primitives.size(); ++i) {

		glColor3ub(primitives[i].color.r, primitives[i].color.g, primitives[i].color.b);
		if (primitives[i].isFill) {

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		} else {

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < primitives[i].points.size(); ++j) {

			glVertex2i(primitives[i].points[j].x, primitives[i].points[j].y);
		}
		glEnd();
	}

	//drawing contour of primitives
	if (primitives.size() > 0) {

		glPointSize(6);
		glEnable(GL_POINT_SMOOTH);
		glBegin(GL_POINTS);
		glColor3ub(primitives[currentPrimitive].color.r + 50, primitives[currentPrimitive].color.g + 50,
			primitives[currentPrimitive].color.b + 50);
		for (int i = 0; i < primitives[currentPrimitive].points.size(); ++i) {

			glVertex2i(primitives[currentPrimitive].points[i].x, primitives[currentPrimitive].points[i].y);
		}
		glEnd();

		if (primitives[currentPrimitive].currentPoint >= 0) {

			glPointSize(10);
			glEnable(GL_POINT_SMOOTH);
			glBegin(GL_POINTS);
			glColor3ub(primitives[currentPrimitive].color.r + 100,
				primitives[currentPrimitive].color.g + 100,
				primitives[currentPrimitive].color.b + 100);
			glVertex2i(primitives[currentPrimitive].points[primitives[currentPrimitive].currentPoint].x,
				primitives[currentPrimitive].points[primitives[currentPrimitive].currentPoint].y);
			glEnd();
		}
	}
	glutSwapBuffers();
}

//-------------------------------------------------------------------------------------------

void Reshape(GLint w, GLint h) {

	Width = w; Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//-------------------------------------------------------------------------------------------

void Keyboard(unsigned char key, int x, int y) {

	menuPoint.x = x;
	menuPoint.y = y;

	//RGB settings
	if (key == 'r' || key == 'R')
		primitives[currentPrimitive].color.r += 20;
	if (key == 'g' || key == 'G')
		primitives[currentPrimitive].color.g += 20;
	if (key == 'b' || key == 'B')
		primitives[currentPrimitive].color.b += 20;

	//fill mode
	if (key == 'm' || key == 'M')
		primitives[currentPrimitive].isFill = !primitives[currentPrimitive].isFill;

	//primitive coordinates settings
	if (key == 'w' || key == 'W')
		for (int i = 0; i < primitives[currentPrimitive].points.size(); i++)
			primitives[currentPrimitive].points[i].y += 20;
	if (key == 's' || key == 'S')
		for (int i = 0; i < primitives[currentPrimitive].points.size(); i++)
			primitives[currentPrimitive].points[i].y -= 20;
	if (key == 'd' || key == 'D')
		for (int i = 0; i < primitives[currentPrimitive].points.size(); i++)
			primitives[currentPrimitive].points[i].x += 20;
	if (key == 'a' || key == 'A')
		for (int i = 0; i < primitives[currentPrimitive].points.size(); i++)
			primitives[currentPrimitive].points[i].x -= 20;

	//point coordinates settings
	if (key == 'i' || key == 'I')
		primitives[currentPrimitive].points[primitives[currentPrimitive].currentPoint].y += 20;
	if (key == 'k' || key == 'K')
		primitives[currentPrimitive].points[primitives[currentPrimitive].currentPoint].y -= 20;
	if (key == 'l' || key == 'L:')
		primitives[currentPrimitive].points[primitives[currentPrimitive].currentPoint].x += 20;
	if (key == 'j' || key == 'J')
		primitives[currentPrimitive].points[primitives[currentPrimitive].currentPoint].x -= 20;

	//scale down
	if (key == '[' || key == '{') {

		auto c = primitives[currentPrimitive].points[0];

		for (int i = 0; i < primitives[currentPrimitive].points.size(); ++i) {

			primitives[currentPrimitive].points[i].x -= c.x;
			primitives[currentPrimitive].points[i].y -= c.y;
			primitives[currentPrimitive].points[i].x /= 1.2;
			primitives[currentPrimitive].points[i].y /= 1.2;
			primitives[currentPrimitive].points[i].x += c.x;
			primitives[currentPrimitive].points[i].y += c.y;
		}
	}

	//scale up
	if (key == ']' || key == '}') {

		auto c = primitives[currentPrimitive].points[0];

		for (int i = 0; i < primitives[currentPrimitive].points.size(); ++i) {

			primitives[currentPrimitive].points[i].x -= c.x;
			primitives[currentPrimitive].points[i].y -= c.y;
			primitives[currentPrimitive].points[i].x *= 1.2;
			primitives[currentPrimitive].points[i].y *= 1.2;
			primitives[currentPrimitive].points[i].x += c.x;
			primitives[currentPrimitive].points[i].y += c.y;
		}

	}

	//angle down
	if (key == ',' || key == '<') {

		int x0 = primitives[currentPrimitive].points[0].x;
		int y0 = primitives[currentPrimitive].points[0].y;

		mat3 rotate1 = translate(rotate(translate(mat3(1.0f), { x0, y0 }), radians(3.0f)), { -x0, -y0 });

		for (int i = 0; i < primitives[currentPrimitive].points.size(); ++i) {

			auto res = rotate1 * vec3(primitives[currentPrimitive].points[i].x,
				primitives[currentPrimitive].points[i].y, 1);
			primitives[currentPrimitive].points[i].x = res.x;
			primitives[currentPrimitive].points[i].y = res.y;
		}
	}

	//angle up
	if (key == '.' || key == '>"') {

		int x0 = primitives[currentPrimitive].points[0].x;
		int y0 = primitives[currentPrimitive].points[0].y;

		mat3 rotate1 = translate(rotate(translate(mat3(1.0f), { x0, y0 }), radians(-3.0f)), { -x0, -y0 });

		for (int i = 0; i < primitives[currentPrimitive].points.size(); ++i) {

			auto res = rotate1 * vec3(primitives[currentPrimitive].points[i].x,
				primitives[currentPrimitive].points[i].y, 1);
			primitives[currentPrimitive].points[i].x = res.x;
			primitives[currentPrimitive].points[i].y = res.y;
		}
	}

	//deleting current primitive
	if (key == 'z' || key == 'Z') {

		if (primitives.size() > 0) {

			primitives.erase(primitives.begin() + currentPrimitive);
		}

		if (currentPrimitive != 0)
			currentPrimitive--;
	}

	//deleting last point
	if (key == 'x' || key == 'X') {

		if (!primitives[currentPrimitive].points.empty()) {

			primitives[currentPrimitive].points.pop_back();
			primitives[currentPrimitive].currentPoint--;
		}
	}

	//previous point
	if (key == 'u' || key == 'U') {

		if (primitives[currentPrimitive].currentPoint != 0)
			primitives[currentPrimitive].currentPoint--;
	}

	//next point
	if (key == 'o' || key == 'O') {

		if (primitives[currentPrimitive].currentPoint != primitives[currentPrimitive].points.size() - 1)
			primitives[currentPrimitive].currentPoint++;
	}

	//previous primitive
	if (key == 'q' || key == 'Q') {

		if (currentPrimitive != 0)
			currentPrimitive--;
	}

	//next primitive
	if (key == 'e' || key == 'E') {

		if (currentPrimitive != primitives.size() - 1)
			currentPrimitive++;
	}

	//anchor current set of primitives
	if (key == ' ') {

		primitives.resize(primitives.size() + 1);
		currentPrimitive++;
	}

	glutPostRedisplay();
}

//-------------------------------------------------------------------------------------------

void Mouse(int button, int state, int x, int y) {

	menuPoint.x = x;
	menuPoint.y = y;

	if (state != GLUT_DOWN) return;

	//adding point
	if (button == GLUT_LEFT_BUTTON) {

		if (primitives.size() == 0)
			primitives.resize(1);

		type_point p(x, Height - y);
		primitives[currentPrimitive].points.push_back(p);
		primitives[currentPrimitive].currentPoint++;
	}
}

//-------------------------------------------------------------------------------------------

void menu(int num) {

	switch (num) {


	case 3: Keyboard('r', menuPoint.x, menuPoint.y); break;
	case 4: Keyboard('g', menuPoint.x, menuPoint.y); break;
	case 5: Keyboard('b', menuPoint.x, menuPoint.y); break;
	case 6: Keyboard('w', menuPoint.x, menuPoint.y); break;
	case 7: Keyboard('s', menuPoint.x, menuPoint.y); break;
	case 8: Keyboard('a', menuPoint.x, menuPoint.y); break;
	case 9: Keyboard('d', menuPoint.x, menuPoint.y); break;
	
	case 11: Keyboard('i', menuPoint.x, menuPoint.y); break;
	case 12: Keyboard('k', menuPoint.x, menuPoint.y); break;
	case 13: Keyboard('j', menuPoint.x, menuPoint.y); break;
	case 14: Keyboard('l', menuPoint.x, menuPoint.y); break;
	case 15: Keyboard('o', menuPoint.x, menuPoint.y); break;
	case 16: Keyboard('u', menuPoint.x, menuPoint.y); break;
	case 17: Keyboard('e', menuPoint.x, menuPoint.y); break;
	case 18: Keyboard('q', menuPoint.x, menuPoint.y); break;
	case 19: Keyboard(' ', menuPoint.x, menuPoint.y); break;
	case 20: Keyboard('z', menuPoint.x, menuPoint.y); break;
	case 21: Mouse(GLUT_LEFT_BUTTON, GLUT_DOWN, menuPoint.x, menuPoint.y); break;
	case 22: Keyboard('x', menuPoint.x, menuPoint.y); break;
	case 23: Keyboard(',', menuPoint.x, menuPoint.y); break;
	case 24: Keyboard('.', menuPoint.x, menuPoint.y); break;
	case 25: Keyboard('[', menuPoint.x, menuPoint.y); break;
	case 26: Keyboard(']', menuPoint.x, menuPoint.y); break;
	case 27: Keyboard('m', menuPoint.x, menuPoint.y); break;
	default: break;
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------------------------------------

void createMenu() {
	//submenu "General menu"
	int generalMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Next primitive", 17);
	glutAddMenuEntry("Previous primitive", 18);

	//submenu "Functional menu"
	int functionalMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Anchor primitive", 19);
	glutAddMenuEntry("Delete primitive", 20);

	glutAddMenuEntry("Rotate primitive for 3 degree left", 23);
	glutAddMenuEntry("Rotate primitive for 3 degree right", 24);

	glutAddMenuEntry("Scale primitive for 1.2x down", 25);
	glutAddMenuEntry("Scale primitive for 1.2x up", 26);

	glutAddMenuEntry("R value +20", 3);
	glutAddMenuEntry("G value +20", 4);
	glutAddMenuEntry("B value +20", 5);

	glutAddMenuEntry("Move current primitive up for 20 px", 6);
	glutAddMenuEntry("Move current primitive down for 20 px", 7);
	glutAddMenuEntry("Move current primitive left for 20 px", 8);
	glutAddMenuEntry("Move current primitive right for 20 px", 9);

	glutAddMenuEntry("Fill on unfill primitvie", 27);

	//submenu "Point menu"
	int pointMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Anchor point", 21);
	glutAddMenuEntry("Delete point", 22);

	glutAddMenuEntry("Next point", 15);
	glutAddMenuEntry("Previous point", 16);

	glutAddMenuEntry("Move current point up for 20px", 11);
	glutAddMenuEntry("Move current point down for 20px", 12);
	glutAddMenuEntry("Move current point left for 20px", 13);
	glutAddMenuEntry("Move current point right for 20px", 14);

	//menu
	int mainMenu = glutCreateMenu(menu);
	glutAddSubMenu("Functional menu", functionalMenu);
	glutAddSubMenu("General menu", generalMenu);
	glutAddSubMenu("Point menu", pointMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//-------------------------------------------------------------------------------------------

void main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Computer Graphics I");
	createMenu();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();
}
