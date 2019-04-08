#pragma once
#define _USE_MATH_DEFINES 
#include <math.h>
#include <windows.h>
#include "glut.h"
#include "glaux.h"
#include <vector>
#include <gl\gl.h>
#include <stdio.h>
#include "Camera.h"

#pragma comment(lib,"glaux.lib")

enum LIGHT_TYPE {

	DIRECTIONAL_LIGHT = 1,
	POINT_LIGHT,
	POINT_LIGHT_INTENSIVE,
	SPOTLIGHT,
	SPOTLIGHT_INTENSIVE,
	POINT_LIGHT2
};

const double cameraSpeed = 0.03f;

using namespace std;

double perspectiveAngle = 60;
double orthoFactor = 10;
GLint width, height;
Camera camera;
bool isMouseRotating = false;
bool isPerspective = true;
bool isWireframe = false;
bool showingNormals = false;
bool smoothingNormals = false;
bool showingGrid = false;
bool isLighting = true;
bool showingTextures = false;
LIGHT_TYPE lightType = DIRECTIONAL_LIGHT;

double shearMatrix[4][4];
double rotationMatrix[4][4];
double scaleMatrix[4][4];

vector <double> percents;
vector <Vector3d> normals;
vector <Vector3d> smoothedNormals;
vector <Vector3d> replicationPath;
vector <Vector3d> sectionScaling;

unsigned int textureNames[10];

void loadTexture() {

	AUX_RGBImageRec *image1 = auxDIBImageLoad(L"textures\\1.bmp");
	/*AUX_RGBImageRec *image2 = auxDIBImageLoad(L"textures\\2.bmp");
	AUX_RGBImageRec *image3 = auxDIBImageLoad(L"textures\\3.bmp");
	AUX_RGBImageRec *image4 = auxDIBImageLoad(L"textures\\4.bmp");
	AUX_RGBImageRec *image5 = auxDIBImageLoad(L"textures\\5.bmp");
	AUX_RGBImageRec *image6 = auxDIBImageLoad(L"textures\\6.bmp");*/
	AUX_RGBImageRec *image7 = auxDIBImageLoad(L"textures\\7.bmp");
	/*AUX_RGBImageRec *image8 = auxDIBImageLoad(L"textures\\8.bmp");*/
	glGenTextures(2, textureNames); //создание имен текстур

	glBindTexture(GL_TEXTURE_2D, textureNames[1]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image1->sizeX, image1->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
	//glBindTexture(GL_TEXTURE_2D, textureNames[1]);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image2->sizeX, image2->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image2->data);
	//glBindTexture(GL_TEXTURE_2D, textureNames[2]);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image3->sizeX, image3->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image3->data);
	//glBindTexture(GL_TEXTURE_2D, textureNames[3]);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image4->sizeX, image4->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image4->data);
	//glBindTexture(GL_TEXTURE_2D, textureNames[4]);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image5->sizeX, image5->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image5->data);
	//glBindTexture(GL_TEXTURE_2D, textureNames[5]);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image6->sizeX, image6->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image6->data);
	glBindTexture(GL_TEXTURE_2D, textureNames[0]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image7->sizeX, image7->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image7->data);
	//glBindTexture(GL_TEXTURE_2D, textureNames[7]);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image8->sizeX, image8->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image8->data);
}