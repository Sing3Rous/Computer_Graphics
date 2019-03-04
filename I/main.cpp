#include <gl/freeglut.h>
#include <vector>
using namespace std;

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
	GLfloat angle = 0.f;
	GLfloat scale = 1.f;
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

	//scale and rotate
	//if (primitives.size() > 0 && primitives[currentPrimitive].points.size() > 0) {

	//	glPushMatrix();
	//	glTranslatef(Width / 2, Height / 2, 0);
	//	glScalef(primitives[currentPrimitive].scale, primitives[currentPrimitive].scale, 0);
	//	glTranslatef(-(Width / 2), -(Height / 2), 0);

	//	glTranslatef(primitives[currentPrimitive].points[0].x, primitives[currentPrimitive].points[0].y, 0);
	//	glRotatef(primitives[currentPrimitive].angle, 0, 0, 1);
	//	glTranslatef(-(primitives[currentPrimitive].points[0].x), -(primitives[currentPrimitive].points[0].y), 0);
	//}
	
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
		glColor3ub(primitives[currentPrimitive].color.r + 50, primitives[currentPrimitive].color.g + 50, primitives[currentPrimitive].color.b + 50);
		for (int i = 0; i < primitives[currentPrimitive].points.size(); ++i) {

			glVertex2i(primitives[currentPrimitive].points[i].x, primitives[currentPrimitive].points[i].y);
		}
		glEnd();

		if (primitives[currentPrimitive].currentPoint >= 0) {

			glPointSize(10);
			glEnable(GL_POINT_SMOOTH);
			glBegin(GL_POINTS);
			glColor3ub(primitives[currentPrimitive].color.r + 100, primitives[currentPrimitive].color.g + 100, primitives[currentPrimitive].color.b + 100);
			glVertex2i(primitives[currentPrimitive].points[primitives[currentPrimitive].currentPoint].x,
				primitives[currentPrimitive].points[primitives[currentPrimitive].currentPoint].y);
			glEnd();
		}
	}
	//glPopMatrix();
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

		primitives[currentPrimitive].scale -= 0.1;
	}
	//scale up
	if (key == ']' || key == '}') {

		primitives[currentPrimitive].scale += 0.1;
	}
	//angle down
	if (key == ',' || key == '<') {

		primitives[currentPrimitive].angle -= 5;
	}
	//angle up
	if (key == '.' || key == '>"') {

		primitives[currentPrimitive].angle += 5;
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
