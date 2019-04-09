#include "Triangle.h"

void reshape(GLint w, GLint h) {

	width = w, height = h;
	if (height == 0) {

		height = 1;
	}
	double ratio = 1. * width / height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);

	if (isPerspective) {

		gluPerspective(60, ratio, 0.1f, 100.0f);
	} else {

		if (width > height) {

			glOrtho(-orthoFactor * ratio, orthoFactor * ratio, -orthoFactor, orthoFactor, -100.0f, 100.0f);
		} else {

			glOrtho(-orthoFactor, orthoFactor, -orthoFactor / ratio, orthoFactor / ratio, -100.0f, 100.0f);
		}
	}
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {

	if (key == 'w' || key == 'W') {

		camera.move_depth(cameraSpeed);
	}
	if (key == 's' || key == 'S') {

		camera.move_depth(-cameraSpeed);
	}

	if (key == 'a' || key == 'A') {

		camera.move_horizontal(-cameraSpeed);
	}
	if (key == 'd' || key == 'D') {

		camera.move_horizontal(cameraSpeed);
	}
	if (key == 'q' || key == 'Q') {

		camera.rotation_by_point(camera.view, -cameraSpeed * 2.0f, 0.0f, 1.0f, 0.0f);
	}
	if (key == 'e' || key == 'E') {

		camera.rotation_by_point(camera.view, cameraSpeed * 2.0f, 0.0f, 1.0f, 0.0f);
	}
	if (key == 't' || key == 'T') {

		showingTextures = !showingTextures;
	}
	if (key == 'g' || key == 'G') {

		showingGrid = !showingGrid;
	}
	if (key == 'l' || key == 'L') {

		isLighting = !isLighting;
	}
	if (key == 'n' || key == 'N') {

		showingNormals = !showingNormals;
	}
	if (key == 'b' || key == 'B') {

		smoothingNormals = !smoothingNormals;
	}
	if (key == 'f' || key == 'F') {

		isWireframe = !isWireframe;
		if (isWireframe) {

			isLighting = false;
		}
		else {

			isLighting = true;
		}
	}
	if (key == 'p' || key == 'P') {

		isPerspective = !isPerspective;
		reshape(width, height);
	}
	if (key == 'm' || key == 'M') {

		isMouseRotating = !isMouseRotating;
	}
	if (key == '.' || key == '>') {

		if (orthoFactor > 0.1f && !isPerspective) {

			orthoFactor -= 0.05;
			reshape(width, height);
		}
		else {

			if (isPerspective) {

				camera.move_vertical(6 * cameraSpeed);
			}
		}
	}
	if (key == ',' || key == '<') {

		if (orthoFactor < 10 && !isPerspective) {

			orthoFactor += 0.05;
			reshape(width, height);
		}
		else {

			if (isPerspective) {

				camera.move_vertical(-6 * cameraSpeed);
			}
		}
	}
	if (key == '1') lightType = DIRECTIONAL_LIGHT;
	if (key == '2') lightType = POINT_LIGHT;
	if (key == '3') lightType = POINT_LIGHT_INTENSIVE;
	if (key == '4') lightType = SPOTLIGHT;
	if (key == '5') lightType = SPOTLIGHT_INTENSIVE;
	if (key == '6') lightType = POINT_LIGHT2;
}

void keyboard_special(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
		camera.move_vertical(cameraSpeed);
	}

	if (key == GLUT_KEY_DOWN) {
		camera.move_vertical(-cameraSpeed);
	}

	if (key == GLUT_KEY_LEFT) {
		camera.rotation_by_point(camera.view, -cameraSpeed * 2.0f, 0.0f, 1.0f, 0.0f);
	}

	if (key == GLUT_KEY_RIGHT) {
		camera.rotation_by_point(camera.view, cameraSpeed * 2.0f, 0.0f, 1.0f, 0.0f);
	}
	glutPostRedisplay();
}

void mouse(int x, int y) {

	if (isMouseRotating) {
		camera.set_view_by_mouse(width, height);
	}
}

void draw_figure() {

	int num = 0;

	if (!isWireframe) {

		glColor3ub(0, 0, 255);
		if (!smoothingNormals) {

			glColor3ub(0, 0, 255);
			if (!showingTextures) {

				glColor3ub(0, 0, 255);

				//setting normals to every plane
				glBegin(GL_TRIANGLES);
				glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;
				glColor3ub(0, 0, 255);
				glVertex3f(figure[0].first.x, figure[0].first.y, figure[0].first.z);
				glVertex3f(figure[0].second.x, figure[0].second.y, figure[0].second.z);
				glVertex3f(figure[0].third.x, figure[0].third.y, figure[0].third.z);
				glEnd();

				for (int i = 0; i < figure.size() - 1; ++i) {

					glBegin(GL_POLYGON);
					glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;

					glColor3ub(0, 0, 255);
					glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);
					glVertex3f(figure[i + 1].first.x, figure[i + 1].first.y, figure[i + 1].first.z);
					glVertex3f(figure[i + 1].second.x, figure[i + 1].second.y, figure[i + 1].second.z);
					glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);
					glEnd();

					glBegin(GL_POLYGON);
					glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;

					glColor3ub(0, 0, 255);
					glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);
					glVertex3f(figure[i + 1].third.x, figure[i + 1].third.y, figure[i + 1].third.z);
					glVertex3f(figure[i + 1].first.x, figure[i + 1].first.y, figure[i + 1].first.z);
					glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);
					glEnd();

					glBegin(GL_POLYGON);
					glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;

					glColor3ub(0, 0, 255);
					glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);
					glVertex3f(figure[i + 1].second.x, figure[i + 1].second.y, figure[i + 1].second.z);
					glVertex3f(figure[i + 1].third.x, figure[i + 1].third.y, figure[i + 1].third.z);
					glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);
					glEnd();
				}

				int last = figure.size() - 1;
				glBegin(GL_TRIANGLES);
				glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;

				glColor3ub(0, 0, 255);
				glVertex3f(figure[last].first.x, figure[last].first.y, figure[last].first.z);
				glVertex3f(figure[last].second.x, figure[last].second.y, figure[last].second.z);
				glVertex3f(figure[last].third.x, figure[last].third.y, figure[last].third.z);
				glEnd();
			}

			//textures
			else {

				//glColor3ub(0, 0, 255);
				glEnable(GL_TEXTURE_2D);			
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glBindTexture(GL_TEXTURE_2D, textureNames[1]);

				glBegin(GL_TRIANGLES);
				glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;
				glTexCoord2f(0, 0);
				glVertex3f(figure[0].first.x, figure[0].first.y, figure[0].first.z);
				glTexCoord2f(0.5, 1);
				glVertex3f(figure[0].second.x, figure[0].second.y, figure[0].second.z);
				glTexCoord2f(1, 0);
				glVertex3f(figure[0].third.x, figure[0].third.y, figure[0].third.z);
				glEnd();

				glBindTexture(GL_TEXTURE_2D, textureNames[0]);	//выбрать текстуру

				glBegin(GL_POLYGON);
				glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;

				glTexCoord2f(1, 0);
				glVertex3f(figure[0].first.x, figure[0].first.y, figure[0].first.z);
				glTexCoord2f(1, 1. / 3.);
				glVertex3f(figure[0].third.x, figure[0].third.y, figure[0].third.z);
				glTexCoord2f(0.5, 1. / 3.);
				glVertex3f(figure[1].third.x, figure[1].third.y, figure[1].third.z);
				glTexCoord2f(0.5, 0);
				glVertex3f(figure[1].first.x, figure[1].first.y, figure[1].first.z);
				glEnd();

				glBegin(GL_POLYGON);
				glTexCoord2f(0.5, 0);
				glVertex3f(figure[1].first.x, figure[1].first.y, figure[1].first.z);
				glTexCoord2f(0.5, 1. / 3.);
				glVertex3f(figure[1].third.x, figure[1].third.y, figure[1].third.z);
				glTexCoord2f(0, 1. / 3.);
				glVertex3f(figure[2].third.x, figure[2].third.y, figure[2].third.z);
				glTexCoord2f(0, 0);
				glVertex3f(figure[2].first.x, figure[2].first.y, figure[2].first.z);

				glEnd();

				glBegin(GL_POLYGON);
				glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;

				glTexCoord2f(1, 1. / 3.);
				glVertex3f(figure[0].third.x, figure[0].third.y, figure[0].third.z);
				glTexCoord2f(1, 2. / 3.);
				glVertex3f(figure[0].second.x, figure[0].second.y, figure[0].second.z);
				glTexCoord2f(0.5, 2. / 3.);
				glVertex3f(figure[1].second.x, figure[1].second.y, figure[1].second.z);
				glTexCoord2f(0.5, 1. / 3.);
				glVertex3f(figure[1].third.x, figure[1].third.y, figure[1].third.z);
				glEnd();

				glBegin(GL_POLYGON);
				glTexCoord2f(0.5, 1. / 3.);
				glVertex3f(figure[1].third.x, figure[1].third.y, figure[1].third.z);
				glTexCoord2f(0.5, 2. / 3.);
				glVertex3f(figure[1].second.x, figure[1].second.y, figure[1].second.z);
				glTexCoord2f(0, 2. / 3.);
				glVertex3f(figure[2].second.x, figure[2].second.y, figure[2].second.z);
				glTexCoord2f(0, 1. / 3.);
				glVertex3f(figure[2].third.x, figure[2].third.y, figure[2].third.z);

				glEnd();

				glBegin(GL_POLYGON);
				glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;

				glTexCoord2f(1, 2. / 3.);
				glVertex3f(figure[0].second.x, figure[0].second.y, figure[0].second.z);
				glTexCoord2f(1, 1);
				glVertex3f(figure[0].first.x, figure[0].first.y, figure[0].first.z);
				glTexCoord2f(0.5, 1);
				glVertex3f(figure[1].first.x, figure[1].first.y, figure[1].first.z);
				glTexCoord2f(0.5, 2. / 3.);
				glVertex3f(figure[1].second.x, figure[1].second.y, figure[1].second.z);
				glEnd();

				glBegin(GL_POLYGON);
				glTexCoord2f(0.5, 2. / 3.);
				glVertex3f(figure[1].second.x, figure[1].second.y, figure[1].second.z);
				glTexCoord2f(0.5, 1);
				glVertex3f(figure[1].first.x, figure[1].first.y, figure[1].first.z);
				glTexCoord2f(0, 1);
				glVertex3f(figure[2].first.x, figure[2].first.y, figure[2].first.z);
				glTexCoord2f(0, 2. / 3.);
				glVertex3f(figure[2].second.x, figure[2].second.y, figure[2].second.z);

				glEnd();

				glBindTexture(GL_TEXTURE_2D, textureNames[1]);
				int j = figure.size() - 1;
				glBegin(GL_TRIANGLES);
				glNormal3f(normals[num].x, normals[num].y, normals[num].z); num++;

				glTexCoord2f(0, 0);
				glVertex3f(figure[j].first.x, figure[j].first.y, figure[j].first.z);
				glTexCoord2f(0.5, 1);
				glVertex3f(figure[j].second.x, figure[j].second.y, figure[j].second.z);
				glTexCoord2f(1, 0);
				glVertex3f(figure[j].third.x, figure[j].third.y, figure[j].third.z);
				glEnd();

				glDisable(GL_TEXTURE_2D);
			}

		}

		//smooth normals
		else {

			glColor3ub(0, 0, 255);
			if (!showingTextures) {

				//setting normal to every vertex
				glBegin(GL_TRIANGLES);

				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glVertex3f(figure[0].first.x, figure[0].first.y, figure[0].first.z);

				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glVertex3f(figure[0].second.x, figure[0].second.y, figure[0].second.z);

				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glVertex3f(figure[0].third.x, figure[0].third.y, figure[0].third.z);
				glEnd();

				num = 0;
				for (int i = 0; i < figure.size() - 1; ++i) {

					glBegin(GL_POLYGON);

					glNormal3f(smoothedNormals[num].x, smoothedNormals[num].y, smoothedNormals[num].z);
					glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);

					glNormal3f(smoothedNormals[num + 3].x, smoothedNormals[num + 3].y, smoothedNormals[num + 3].z);
					glVertex3f(figure[i + 1].first.x, figure[i + 1].first.y, figure[i + 1].first.z);

					glNormal3f(smoothedNormals[num + 4].x, smoothedNormals[num + 4].y, smoothedNormals[num + 4].z);
					glVertex3f(figure[i + 1].second.x, figure[i + 1].second.y, figure[i + 1].second.z);

					glNormal3f(smoothedNormals[num + 1].x, smoothedNormals[num + 1].y, smoothedNormals[num + 1].z);
					glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);
					glEnd();

					glBegin(GL_POLYGON);

					glNormal3f(smoothedNormals[num + 2].x, smoothedNormals[num + 2].y, smoothedNormals[num + 2].z);
					glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);

					glNormal3f(smoothedNormals[num + 5].x, smoothedNormals[num + 5].y, smoothedNormals[num + 5].z);
					glVertex3f(figure[i + 1].third.x, figure[i + 1].third.y, figure[i + 1].third.z);

					glNormal3f(smoothedNormals[num + 3].x, smoothedNormals[num + 3].y, smoothedNormals[num + 3].z);
					glVertex3f(figure[i + 1].first.x, figure[i + 1].first.y, figure[i + 1].first.z);

					glNormal3f(smoothedNormals[num].x, smoothedNormals[num].y, smoothedNormals[num].z);
					glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);
					glEnd();

					glBegin(GL_POLYGON);

					glNormal3f(smoothedNormals[num + 1].x, smoothedNormals[num + 1].y, smoothedNormals[num + 1].z);
					glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);

					glNormal3f(smoothedNormals[num + 4].x, smoothedNormals[num + 4].y, smoothedNormals[num + 4].z);
					glVertex3f(figure[i + 1].second.x, figure[i + 1].second.y, figure[i + 1].second.z);

					glNormal3f(smoothedNormals[num + 5].x, smoothedNormals[num + 5].y, smoothedNormals[num + 5].z);
					glVertex3f(figure[i + 1].third.x, figure[i + 1].third.y, figure[i + 1].third.z);

					glNormal3f(smoothedNormals[num + 2].x, smoothedNormals[num + 2].y, smoothedNormals[num + 2].z);
					glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);
					glEnd();

					num += 3;
				}

				int j = figure.size() - 1;
				glBegin(GL_TRIANGLES);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[num].x, smoothedNormals[num].y, smoothedNormals[num].z);
				glVertex3f(figure[j].first.x, figure[j].first.y, figure[j].first.z);

				glNormal3f(smoothedNormals[num + 1].x, smoothedNormals[num + 1].y, smoothedNormals[num + 1].z);
				glVertex3f(figure[j].second.x, figure[j].second.y, figure[j].second.z);

				glNormal3f(smoothedNormals[num + 2].x, smoothedNormals[num + 2].y, smoothedNormals[num + 2].z);
				glVertex3f(figure[j].third.x, figure[j].third.y, figure[j].third.z);
				glEnd();
			}

			//textures
			else {

				glColor3ub(0, 0, 255);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, textureNames[0]);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

				//setting normal to every vertex and texture coordinates
				glBegin(GL_TRIANGLES);

				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glTexCoord2f(0, 0); glVertex3f(figure[0].first.x, figure[0].first.y, figure[0].first.z);

				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glTexCoord2f(0.5, 1); glVertex3f(figure[0].second.x, figure[0].second.y, figure[0].second.z);

				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glTexCoord2f(1, 0); glVertex3f(figure[0].third.x, figure[0].third.y, figure[0].third.z);
				glEnd();

				num = 0;
				for (int i = 0; i < figure.size() - 1; ++i) {

					glBegin(GL_POLYGON);
					glNormal3f(smoothedNormals[num].x, smoothedNormals[num].y, smoothedNormals[num].z);
					glTexCoord2f(0, 1);
					glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);

					glNormal3f(smoothedNormals[num + 3].x, smoothedNormals[num + 3].y, smoothedNormals[num + 3].z);
					glTexCoord2f(1, 1);
					glVertex3f(figure[i + 1].first.x, figure[i + 1].first.y, figure[i + 1].first.z);

					glNormal3f(smoothedNormals[num + 4].x, smoothedNormals[num + 4].y, smoothedNormals[num + 4].z);
					glTexCoord2f(1, 0);
					glVertex3f(figure[i + 1].second.x, figure[i + 1].second.y, figure[i + 1].second.z);

					glNormal3f(smoothedNormals[num + 1].x, smoothedNormals[num + 1].y, smoothedNormals[num + 1].z);
					glTexCoord2f(0, 0);
					glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);
					glEnd();

					glBegin(GL_POLYGON);

					glNormal3f(smoothedNormals[num + 2].x, smoothedNormals[num + 2].y, smoothedNormals[num + 2].z);
					glTexCoord2f(0, 1);
					glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);

					glNormal3f(smoothedNormals[num + 5].x, smoothedNormals[num + 5].y, smoothedNormals[num + 5].z);
					glTexCoord2f(1, 1);
					glVertex3f(figure[i + 1].third.x, figure[i + 1].third.y, figure[i + 1].third.z);

					glNormal3f(smoothedNormals[num + 3].x, smoothedNormals[num + 3].y, smoothedNormals[num + 3].z);
					glTexCoord2f(1, 0);
					glVertex3f(figure[i + 1].first.x, figure[i + 1].first.y, figure[i + 1].first.z);

					glNormal3f(smoothedNormals[num].x, smoothedNormals[num].y, smoothedNormals[num].z);
					glTexCoord2f(0, 0);
					glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);
					glEnd();

					glBegin(GL_POLYGON);

					glNormal3f(smoothedNormals[num + 1].x, smoothedNormals[num + 1].y, smoothedNormals[num + 1].z);
					glTexCoord2f(0, 1);
					glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);

					glNormal3f(smoothedNormals[num + 4].x, smoothedNormals[num + 4].y, smoothedNormals[num + 4].z);
					glTexCoord2f(1, 1);
					glVertex3f(figure[i + 1].second.x, figure[i + 1].second.y, figure[i + 1].second.z);

					glNormal3f(smoothedNormals[num + 5].x, smoothedNormals[num + 5].y, smoothedNormals[num + 5].z);
					glTexCoord2f(1, 0);
					glVertex3f(figure[i + 1].third.x, figure[i + 1].third.y, figure[i + 1].third.z);

					glNormal3f(smoothedNormals[num + 2].x, smoothedNormals[num + 2].y, smoothedNormals[num + 2].z);
					glTexCoord2f(0, 0);
					glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);
					glEnd();
				}

				int j = figure.size() - 1;
				glBegin(GL_TRIANGLES);

				glNormal3f(smoothedNormals[num].x, smoothedNormals[num].y, smoothedNormals[num].z);
				glTexCoord2f(0, 0);
				glVertex3f(figure[j].first.x, figure[j].first.y, figure[j].first.z);

				glNormal3f(smoothedNormals[num + 1].x, smoothedNormals[num + 1].y, smoothedNormals[num + 1].z);
				glTexCoord2f(0.5, 1);
				glVertex3f(figure[j].second.x, figure[j].second.y, figure[j].second.z);

				glNormal3f(smoothedNormals[num + 2].x, smoothedNormals[num + 2].y, smoothedNormals[num + 2].z);
				glTexCoord2f(1, 0);
				glVertex3f(figure[j].third.x, figure[j].third.y, figure[j].third.z);
				glEnd();

				glDisable(GL_TEXTURE_2D);
			}
		}
	}

	//wireframe
	else {

		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 0, 0);
		for (int i = 0; i < figure.size(); ++i) {

			glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3ub(0, 255, 0);
		for (int i = 0; i < figure.size(); ++i) {

			glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3ub(0, 0, 255);
		for (int i = 0; i < figure.size(); ++i) {

			glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 255, 255);
		for (int i = 0; i < replicationPath.size(); ++i) {

			glVertex3f(replicationPath[i].x, replicationPath[i].y, replicationPath[i].z);
		}
		glEnd();

		for (int i = 0; i < figure.size(); ++i) {

			glBegin(GL_LINE_LOOP);
			glColor3ub(150, 150, 150);
			glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);
			glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);
			glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);
			glEnd();
		}
	}

	if (showingNormals) {

		if (!smoothingNormals) {

			glBegin(GL_LINE_STRIP);
			glVertex3f(figure[0].first.x, figure[0].first.y, figure[0].first.z);
			glVertex3f(figure[0].first.x + normals[0].x, figure[0].first.y + normals[0].y, figure[0].first.z + normals[0].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glVertex3f(figure[0].second.x, figure[0].second.y, figure[0].second.z);
			glVertex3f(figure[0].second.x + normals[0].x, figure[0].second.y + normals[0].y, figure[0].second.z + normals[0].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glVertex3f(figure[0].third.x, figure[0].third.y, figure[0].third.z);
			glVertex3f(figure[0].third.x + normals[0].x, figure[0].third.y + normals[0].y, figure[0].third.z + normals[0].z);
			glEnd();

			num = 1;
			for (int i = 0; i < figure.size() - 1; ++i) {

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);
				glVertex3f(figure[i].first.x + normals[num].x, figure[i].first.y + normals[num].y, figure[i].first.z + normals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i + 1].first.x, figure[i + 1].first.y, figure[i + 1].first.z);
				glVertex3f(figure[i + 1].first.x + normals[num].x, figure[i + 1].first.y + normals[num].y, figure[i + 1].first.z + normals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i + 1].second.x, figure[i + 1].second.y, figure[i + 1].second.z);
				glVertex3f(figure[i + 1].second.x + normals[num].x, figure[i + 1].second.y + normals[num].y, figure[i + 1].second.z + normals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);
				glVertex3f(figure[i].second.x + normals[num].x, figure[i].second.y + normals[num].y, figure[i].second.z + normals[num].z);
				glEnd();

				num++;

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);
				glVertex3f(figure[i].third.x + normals[num].x, figure[i].third.y + normals[num].y, figure[i].third.z + normals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i + 1].third.x, figure[i + 1].third.y, figure[i + 1].third.z);
				glVertex3f(figure[i + 1].third.x + normals[num].x, figure[i + 1].third.y + normals[num].y, figure[i + 1].third.z + normals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i + 1].first.x, figure[i + 1].first.y, figure[i + 1].first.z);
				glVertex3f(figure[i + 1].first.x + normals[num].x, figure[i + 1].first.y + normals[num].y, figure[i + 1].first.z + normals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);
				glVertex3f(figure[i].first.x + normals[num].x, figure[i].first.y + normals[num].y, figure[i].first.z + normals[num].z);
				glEnd();

				num++;

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);
				glVertex3f(figure[i].second.x + normals[num].x, figure[i].second.y + normals[num].y, figure[i].second.z + normals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i + 1].second.x, figure[i + 1].second.y, figure[i + 1].second.z);
				glVertex3f(figure[i + 1].second.x + normals[num].x, figure[i + 1].second.y + normals[num].y, figure[i + 1].second.z + normals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i + 1].third.x, figure[i + 1].third.y, figure[i + 1].third.z);
				glVertex3f(figure[i + 1].third.x + normals[num].x, figure[i + 1].third.y + normals[num].y, figure[i + 1].third.z + normals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);
				glVertex3f(figure[i].third.x + normals[num].x, figure[i].third.y + normals[num].y, figure[i].third.z + normals[num].z);
				glEnd();

				num++;
			}

			int j = figure.size() - 1;
			glBegin(GL_LINE_STRIP);
			glVertex3f(figure[j].first.x, figure[j].first.y, figure[j].first.z);
			glVertex3f(figure[j].first.x + normals[num].x, figure[j].first.y + normals[num].y, figure[j].first.z + normals[num].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glVertex3f(figure[j].second.x, figure[j].second.y, figure[j].second.z);
			glVertex3f(figure[j].second.x + normals[num].x, figure[j].second.y + normals[num].y, figure[j].second.z + normals[num].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glVertex3f(figure[j].third.x, figure[j].third.y, figure[j].third.z);
			glVertex3f(figure[j].third.x + normals[num].x, figure[j].third.y + normals[num].y, figure[j].third.z + normals[num].z);
			glEnd();

		}

		//smooth normals
		else
		{
			num = 0;
			for (int i = 0; i < figure.size(); ++i) {

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i].first.x, figure[i].first.y, figure[i].first.z);
				glVertex3f(figure[i].first.x + smoothedNormals[num].x, figure[i].first.y + smoothedNormals[num].y, figure[i].first.z + smoothedNormals[num].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i].second.x, figure[i].second.y, figure[i].second.z);
				glVertex3f(figure[i].second.x + smoothedNormals[num + 1].x, figure[i].second.y + smoothedNormals[num + 1].y, figure[i].second.z + smoothedNormals[num + 1].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glVertex3f(figure[i].third.x, figure[i].third.y, figure[i].third.z);
				glVertex3f(figure[i].third.x + smoothedNormals[num + 2].x, figure[i].third.y + smoothedNormals[num + 2].y, figure[i].third.z + smoothedNormals[num + 2].z);
				glEnd();
				num += 3;
			}
		}
	}
}

void draw_grid() {

	glColor3ub(255, 0, 213);
	for (int i = -50; i <= 50; ++i) {

		glBegin(GL_LINES);

		glVertex3f(-50, 0, i);
		glVertex3f(50, 0, i);

		glVertex3f(i, 0, -50);
		glVertex3f(i, 0, 50);
		glEnd();
	}
}

void set_lighting() {

	GLfloat ambience[4] = { 1, 1, 1, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambience);
	GLfloat materialsDiffuse[4] = { 1, 1, 1, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialsDiffuse);

	if (lightType == DIRECTIONAL_LIGHT) {

		GLfloat lightDiffuse[3] = { 2, 1.5, 1.8 };
		GLfloat lightPosition[4] = { 10, -10, 10, 0 };
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	}

	if (lightType == POINT_LIGHT) {

		GLfloat lightDiffuse[3] = { 0.4, 0.4, 0.4 };
		GLfloat lightPosition[4] = { 0, 4.0, 0, 1.0 };
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	}

	if (lightType == POINT_LIGHT_INTENSIVE) {

		GLfloat lightDiffuse[3] = { 0.4, 0.4, 0.4 };
		GLfloat lightPosition[4] = { 0, 4.0, 0, 1.0 };
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT2, GL_POSITION, lightPosition);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.04);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.04);
	}

	if (lightType == SPOTLIGHT) {

		GLfloat lightDiffuse[3] = { 2, 2, 2 };
		GLfloat lightPosition[4] = { 0, 0, 0, 1.0 };
		GLfloat lightSportDirection[3] = { 0, 1, 0 };
		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT3, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT3, GL_POSITION, lightPosition);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 50);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lightSportDirection);
	}

	if (lightType == SPOTLIGHT_INTENSIVE) {

		GLfloat lightDiffuse[3] = { 2, 2, 2 };
		GLfloat lightPosition[4] = { 0, 0, 0, 1.0 };
		GLfloat lightSportDirection[3] = { 0, 1, 0 };
		glEnable(GL_LIGHT4);
		glLightfv(GL_LIGHT4, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT4, GL_POSITION, lightPosition);
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 50);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lightSportDirection);
		glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0);
	}

	if (lightType == POINT_LIGHT2) {

		GLfloat lightDiffuse[3] = { 0.4, 0.4, 0.4 };
		GLfloat lightPosition[4] = { 0, 4.0, 10000, 1.0 };
		glEnable(GL_LIGHT1);
		//glLightfv(GL_LIGHT1, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	}
}

void initialize() {

	set_lighting();
	camera.set_position(-15.0f, 8.5f, 0.0f, -5.0f, 8.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	replication();
	calcNormals();
	calcSmoothedNormals();
	loadTexture();
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (isLighting) {

		glEnable(GL_LIGHTING);
	}
	else {

		glDisable(GL_LIGHTING);
	}

	glLoadIdentity();
	gluLookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.view.x, camera.view.y, camera.view.z,
		camera.scene.x, camera.scene.y, camera.scene.z);
	set_lighting();
	if (showingGrid) {

		draw_grid();
	}
	draw_figure();
	glTranslatef(camera.view.x, 0, camera.view.z);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glutSwapBuffers();
}

void main(int argc, char *argv[]) {

	width = 1880;
	height = 990;
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("CG II");
	initialize();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_special);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutPassiveMotionFunc(mouse);
	glutMainLoop();
	
}