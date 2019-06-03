#include "includes.h"

GLint Width = 800, Height = 600;

int i, k;
class Spline {

private:
	int num;
	struct point
	{
		double x;
		double y;
	} points[200];

	double *a, *b, *c;

public:
	Spline() { num = 0; }

	void add(double x, double y) {

		bool flag = true;
		for (int i = 0; i < num; i++) {

			if (fabs(points[i].x - x) < 0.01) {

				flag = false;
			}
		}

		if (num < 100 && flag) {

			points[num].x = x; points[num].y = y;
			num++;
		}
	}

	inline double f(double a, double b, double c, double x_x0) {
		return a + b * x_x0 + c * x_x0 * x_x0;
	}

	inline double f1(double b, double c, double x_x0) {
		return b + 2 * c * x_x0;
	}

	bool build() {
		if (num < 2) {

			return false;
		}
		this->sort();
		double *di, *didown, *diup, *F, *d;
		double A = 1;
		double B = 1;
		didown = new double[num - 1];
		diup = new double[num - 1];
		di = new double[num];
		F = new double[num];
		d = new double[num];

		for (int i = 0; i < num - 1; i++) {

			didown[i] = diup[i] = points[i + 1].x - points[i].x;
			di[i + 1] = 3 * (points[i + 2].x - points[i].x);
		}
		diup[0] = 0;
		di[0] = 2;
		didown[num - 2] = 0;
		di[num - 1] = 2;

		for (i = 1; i < num - 1; i++) {

			F[i] = 4 * ((points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x) - 
				(points[i].y - points[i - 1].y) / (points[i].x - points[i - 1].x));
		}
		F[0] = A;
		F[num - 1] = B;

		solveslau(di, didown, diup, F, d);
		delete[] didown;
		delete[] diup;
		for (i = 0; i < num - 1; i++) {

			di[i] = ((points[i + 1].x - points[i].x)*(d[i] - d[i + 1]) / 4) + 
				(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x);
		}
		di[num - 1] = di[num - 2] + B * (points[num - 1].x - points[num - 2].x) / 2;

		for (i = 0; i < num - 1; i++) {

			double h = points[i + 1].x - points[i].x;
			F[i] = 0.5*h*(di[i] - h * d[i] * 0.5) + points[i].y;
		}
		F[num - 1] = points[num - 1].y;
		a = F;
		b = di;
		c = d;
		return true;
	}

	void sort()
	{
		int i;
		bool flag;
		double x, y;

		do {

			flag = false;
			for (i = 0; i < num - 1; i++) {

				if (points[i].x > points[i + 1].x) {

					x = points[i].x;
					points[i].x = points[i + 1].x;
					points[i + 1].x = x;
					y = points[i].y;
					points[i].y = points[i + 1].y;
					points[i + 1].y = y;
					flag = true;
				}
			}
		} while (flag);
	}

	void solveslau(double *di, double *didown, double *diup, double *F, double *X) {

		double *D;
		D = new double[num];

		//factorization
		for (int k = 1; k < num; k++) {

			diup[k - 1] /= di[k - 1];
			di[k] -= didown[k - 1] * diup[k - 1];
		}

		//direct
		D[0] = F[0] / di[0];
		for (k = 1; k < num; k++) {

			D[k] = (F[k] - didown[k - 1] * D[k - 1]) / di[k];
		}


		//reverse
		X[num - 1] = D[num - 1];
		for (k = num - 2; k >= 0; k--) {

			X[k] = D[k] - diup[k] * X[k + 1];
		}

		delete D;
	}

	void draw() {

		int i;
		double h, x, x1;

		glPointSize(6);
		glBegin(GL_POINTS);

		glColor3d(1.0, 0.5, 0.3);
		for (i = 0; i < num; i++) {

			glVertex2d(points[i].x, points[i].y);
		}
		glEnd();

		glPointSize(5);
		glColor3d(0.2, 0.5, 1.0);
		glLineWidth(2);
		glBegin(GL_LINES);
		x = (points[1].x + points[0].x) / 2.0;
		x1 = points[0].x;

		do {

			h = 1e-3;
			glVertex2f(x1, f(a[0], b[0], c[0], x1 - x));
			x1 += h;
			glVertex2f(x1, f(a[0], b[0], c[0], x1 - x));
		} while (x1 < x);


		for (i = 1; i < num - 1; i++) {

			h = 1e-3;
			x1 = (points[i].x + points[i - 1].x) / 2;
			x = (points[i + 1].x + points[i].x) / 2;
			do {

				glVertex2f(x1, f(a[i], b[i], c[i], x1 - x));
				x1 += h;
				glVertex2f(x1, f(a[i], b[i], c[i], x1 - x));
			} while (x1 < x);
		}

		x = points[num - 1].x;
		x1 = (points[num - 1].x + points[num - 2].x) / 2;

		do {

			glVertex2f(x1, f(a[num - 1], b[num - 1], c[num - 1], x1 - x));
			x1 += h;
			glVertex2f(x1, f(a[num - 1], b[num - 1], c[num - 1], x1 - x));
		} while (x1 < x);

		glEnd();

		glLineWidth(1);
		glBegin(GL_LINES);
		glColor3d(0.3,0.8,0.7);
		x = (points[1].x + points[0].x) / 2.0;
		x1 = points[0].x;

		do {

			h = 1e-3;
			glVertex2f(x1, f1(b[0], c[0], x1 - x));
			x1 += h;
			glVertex2f(x1, f1(b[0], c[0], x1 - x));
		} while (x1 < x);


		for (i = 1; i < num - 1; i++) {

			h = 1e-3;
			x1 = (points[i].x + points[i - 1].x) / 2;
			x = (points[i + 1].x + points[i].x) / 2;
			do {

				glVertex2f(x1, f1(b[i], c[i], x1 - x));
				x1 += h;
				glVertex2f(x1, f1(b[i], c[i], x1 - x));
			} while (x1 < x);
		}

		x = points[num - 1].x;
		x1 = (points[num - 1].x + points[num - 2].x) / 2;

		do {

			glVertex2f(x1, f1(b[num - 1], c[num - 1], x1 - x));
			x1 += h;
			glVertex2f(x1, f1(b[num - 1], c[num - 1], x1 - x));
		} while (x1 < x);

		glEnd();
	}
};
