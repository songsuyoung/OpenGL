#include <GL/glut.h>
void MyDisplay() {
	glClearColor(0.259, 0.259, 0.453, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES); // GL_POINTS, GL_POLYGON µî
	glVertex2f(-1.0, 0.0);
	glVertex2f(0.0, 0.0);
	glEnd();
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("My First OpenGL Code");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}