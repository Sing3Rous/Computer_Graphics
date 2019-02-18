#include <gl/freeglut.h>
#include <vector>
using namespace std;

//-------------------------------------------------------------------------------------------

struct type_color {
	GLint r, g, b;
	type_color() { r = 255; g = 255; b = 255; }
	type_color(GLint _r, GLint _g, GLint _b) { r = _r, g = _g, b = _b; }
};

struct type_point {
	GLint x, y;
	type_point() { x = 0; y = 0; }
	type_point(GLint _x, GLint _y) { x = _x; y = _y; }
};

//-------------------------------------------------------------------------------------------

GLint Width = 512, Height = 512;

type_point menuPoint;

vector <vector <type_point>> primitives;
vector <type_color>  primitivesColors;

vector <type_point> currentPrimitives;
type_color currentPrimitivesColor;

//-------------------------------------------------------------------------------------------

void Display(void) {
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//drawing all primitives' sets without current
	for (int i = 0; i < primitives.size(); ++i) {

		glColor3ub(primitivesColors[i].r, primitivesColors[i].g, primitivesColors[i].b);
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < primitives[i].size(); ++j) {

			glVertex2i(primitives[i][j].x, primitives[i][j].y);
		}
		glEnd();
	}

	//drawing current primitives' set
	glColor3ub(currentPrimitivesColor.r, currentPrimitivesColor.g, currentPrimitivesColor.b);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < currentPrimitives.size(); ++i) {

		glVertex2i(currentPrimitives[i].x, currentPrimitives[i].y);
	}
	glEnd();

	//drawing points of current primitives' set
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	for (int i = 0; i < currentPrimitives.size(); ++i) {

		glVertex2i(currentPrimitives[i].x, currentPrimitives[i].y);
	}
	glEnd();

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

	int n = currentPrimitives.size();
	menuPoint.x = x;
	menuPoint.y = y;

	//RGB settings
	if (key == 'r' || key == 'R') currentPrimitivesColor.r += 20;
	if (key == 'g' || key == 'G') currentPrimitivesColor.g += 20;
	if (key == 'b' || key == 'B') currentPrimitivesColor.b += 20;

	//coordinates settings
	if (key == 'w' || key == 'W') for (int i = 0; i < n; i++) currentPrimitives[i].y += 20;
	if (key == 's' || key == 'S') for (int i = 0; i < n; i++) currentPrimitives[i].y -= 20;
	if (key == 'a' || key == 'A') for (int i = 0; i < n; i++) currentPrimitives[i].x -= 20;
	if (key == 'd' || key == 'D') for (int i = 0; i < n; i++) currentPrimitives[i].x += 20;

	//deleting all primitives' set
	if (key == 'z' || key == 'Z') {

		if (!currentPrimitives.empty()) {

			currentPrimitives.clear();
			currentPrimitivesColor.r = 255;
			currentPrimitivesColor.g = 255;
			currentPrimitivesColor.b = 255;

		} else if (!primitives.empty()) {

			for (int i = 0; i < primitives[primitives.size() - 1].size(); ++i) {

				currentPrimitives.push_back(primitives[primitives.size() - 1][i]);
				currentPrimitivesColor.r = primitivesColors[primitives.size() - 1].r;
				currentPrimitivesColor.g = primitivesColors[primitives.size() - 1].g;
				currentPrimitivesColor.b = primitivesColors[primitives.size() - 1].b;
			}
			primitives.pop_back();
			primitivesColors.pop_back();
		}
	}

	//deleting last point
	if (key == 'x' || key == 'X') {

		if (!currentPrimitives.empty())
			currentPrimitives.pop_back();
	}

	//anchor current primitives' set
	if (key == ' ') {

		primitives.push_back(currentPrimitives);
		primitivesColors.push_back(currentPrimitivesColor);
		currentPrimitivesColor.r = 255;
		currentPrimitivesColor.g = 255;
		currentPrimitivesColor.b = 255;
		currentPrimitives.clear();
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

		type_point p(x, Height - y);
		currentPrimitives.push_back(p);
	}
}

//-------------------------------------------------------------------------------------------

void menu(int num) {

	switch (num) {

	case 1: Mouse(GLUT_LEFT_BUTTON, GLUT_DOWN, menuPoint.x, menuPoint.y); break;
	case 2: Keyboard('x', menuPoint.x, menuPoint.y); break;
	case 3: Keyboard('r', menuPoint.x, menuPoint.y); break;
	case 4: Keyboard('g', menuPoint.x, menuPoint.y); break;
	case 5: Keyboard('b', menuPoint.x, menuPoint.y); break;
	case 6: Keyboard('w', menuPoint.x, menuPoint.y); break;
	case 7: Keyboard('s', menuPoint.x, menuPoint.y); break;
	case 8: Keyboard('a', menuPoint.x, menuPoint.y); break;
	case 9: Keyboard('d', menuPoint.x, menuPoint.y); break;
	case 10: Keyboard('z', menuPoint.x, menuPoint.y); break;
	default: break;
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------------------------------------

void createMenu() {

	//submenu "Functional menu"
	int functionalMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Add point", 1);
	glutAddMenuEntry("Delete last point", 2);

	glutAddMenuEntry("R value +20", 3);
	glutAddMenuEntry("G value +20", 4);
	glutAddMenuEntry("B value +20", 5);

	glutAddMenuEntry("Move current set of primitives up for 20 px", 6);
	glutAddMenuEntry("Move current set of primitives down for 20 px", 7);
	glutAddMenuEntry("Move current set of primitives left for 20 px", 8);
	glutAddMenuEntry("Move current set of primitives right for 20 px", 9);

	//menu
	int mainMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Delete current set of primitives", 10);
	glutAddSubMenu("Functional menu", functionalMenu);

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