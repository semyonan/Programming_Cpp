#include <time.h>
#include <stdlib.h>
#include <vector>
#include "rubics_cube.cpp"

using namespace std;
rube_cube cube;
unsigned int c[9] = {0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 	0xCD853F};
GLfloat lightPos[] = {0, 100, 200, 0}; 
int xRot = 110, yRot = 207, zRot = 0;
double translateZ = -35.0;
 
void display() {
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glTranslatef(0, 0, translateZ);
	glRotatef(xRot, 1, 0, 1);
	glRotatef(yRot, 0, 1, 0);
	glTranslatef(-6, -6, -6);
	cube.draw_cube();
	glPopMatrix();
	glutSwapBuffers();
}
 
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect = (GLfloat)w/(GLfloat)h;
    gluPerspective(60, fAspect, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void rotate(int key, int, int) {
	if(key == '1') {
		cube.front_face_rotate(true);
		glutPostRedisplay();
	} 
	if(key == '2') {
		cube.front_face_rotate(false);
		glutPostRedisplay();
	} 
	if(key == '3') {
		cube.back_face_rotate(true);
		glutPostRedisplay();
	} 
	if(key == '4') {
		cube.back_face_rotate(false);
		glutPostRedisplay();
	} 
	if(key == '5') {
		cube.left_face_rotate(true);
		glutPostRedisplay();
	} 
	if(key == '6') {
		cube.left_face_rotate(false);
		glutPostRedisplay();
	} 
	if(key == '7') {
		cube.right_face_rotate(true);
		glutPostRedisplay();
	} 
	if(key == '8') {
		cube.right_face_rotate(false);
		glutPostRedisplay();
	} 
	if(key == '9') {
		cube.up_face_rotate(true);
		glutPostRedisplay();
	} 
	if(key == '0') {
		cube.up_face_rotate(false);
	} 
	if(key == 'R') {
		cube.down_face_rotate(true);
		glutPostRedisplay();
	} 
	if(key == 'L') {
		cube.down_face_rotate(false);
		glutPostRedisplay();
	}  
	if (key == GLUT_KEY_DOWN) {
		xRot += 3;
		if (xRot >= 360)
			xRot -= 360;
		glutPostRedisplay();
	}
 
	if (key == GLUT_KEY_UP) {
		xRot -= 3;
		if (xRot < 0)
			xRot += 360;
		glutPostRedisplay();
	}
 
	if (key == GLUT_KEY_RIGHT) {
		yRot += 3;
		if (yRot >= 360)
			yRot -= 360;
		glutPostRedisplay();
	}
 
	if (key == GLUT_KEY_LEFT) {
		yRot -= 3;
		if (yRot < 0)
			yRot += 360;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_F1) {
		cube.find_solution();
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_F2) {
		cout << "Введите последовательность поворотов: \n";
		string rotations;
		cin >> rotations;
		cube.make_rotations(rotations, false);
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_F3) {
		cube.print_cube(false);
	}
	if (key == GLUT_KEY_F4) {
		cube.print_cube(true);
	}
	if (key == GLUT_KEY_F5) {
		cout << "Введите название файла, из которого вы хотите прочитать состояние кубика: \n";
		string filename;
		cin >> filename;
		ifstream fin(filename);
		cube.read_cube(fin);
		glutPostRedisplay();
		fin.close();
	}
	if (key == GLUT_KEY_F6) {
		cube.random_rotate();
		glutPostRedisplay();
	}
}
 
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	srand(time(0));

	float mat_specular[] = {0.3, 0.3, 0.3, 0};
	float diffuseLight[] = {0.2, 0.2, 0.2, 1};
	float ambientLight[] = {0.9, 0.9, 0.9, 1.0};
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	cube.fill_rube_cube();
}
 
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 700);
	glutInitWindowPosition(1, 1);
	
	glutCreateWindow("Cube");
	init();
	glutDisplayFunc(display);
	
	glutReshapeFunc(reshape);
	glutSpecialFunc(rotate);
	glutMainLoop();
	return 0;
}