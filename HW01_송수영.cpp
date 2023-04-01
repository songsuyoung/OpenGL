/***********************************************************************/
/*                 HW#1 : 3D Sierpinski Gasket	                       */
/*  �ۼ��� : �ۼ���                              ��¥ : 2021�� 9�� 17��*/
/*                                                                     */
/* ���� ���� : 2d�� ���ǵ� sierpinski gasket �ڵ带 3d �ڵ�� ��ȯ�ϴ� */
/* ������ ���ٿ� Reshape callback �Լ��� ����ؼ� �ְ� ���� �ذ�	   */
/* ��� : main���� ������ �ݹ��Լ��� �̿��ؼ� ȭ���� ��ǥ�� ���ϰ� �ְ�*/
/* ������ �ذ��Ѵ�. MyDisplay�� 3d �ﰢ���� ����� ���� ��ǥ 4���� ���*/
/*������ ���� �ϳ� �����Ͽ� ������ ���Ѵ�.�� �� 50000�� ��ǥ�� ���ϰ� ��*/
/*������ ����Ѵ�. MyReshape�� ��� ���ο� ������ ũ�⸦ ���� ������ ũ��*/
/*���� ������ �����, �׿� �°� ����Ʈ�� ������ �ش�.�׷����ν� �ְ*/
/*���� �ذ��Ѵ�. MyInit�� ��� ���� �ʱ� ������ȯ�� �ǽ��Ѵ�.           */
/***********************************************************************/

#include <gl/glut.h>
#include <stdlib.h> //random�� �������ϱ�.

//callback�Լ� �̸� ����, main�ۼ� �� �ڵ� �ۼ��� ����
void MyDisplay();
void MyReshape(int NewWidth,int NewHeight);
void MyInit();

void main(int argc, char** argv) {

	glutInit(&argc, argv); //argc ,argv�� ���ڰ����� �Ѱܼ� glut �ʱ�ȭ�� ������.
	glutInitDisplayMode(GLUT_RGB); //window â�� RGB��� �⺻������ �����ϱ�
	glutInitWindowSize(500, 500); //������ â ũ��� 500,500����, ��ġ�� 0,0 ���� ������.
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2D->3D Sierpinski gasket");
	glutDisplayFunc(MyDisplay); //�׸� �׸��� �ݹ��Լ�
	// ������â�� �׷��� sierpinski gasket �ڵ带 ���� �Լ��� �ݹ��Լ��� ���.
	glutReshapeFunc(MyReshape); //�ְ�� �ذ� �ݹ��Լ�
	// ������â�� ũ�Ⱑ ����ɽ� ����� ũ�⸦ �����찡 �����Ͽ� ���ڰ����� ����
	// �� ���ڰ��� �̿��ؼ� �ְ��� �߻����� �ʰ� ������ȯ�� �ٲ��� �ڵ带 �ݹ��Լ��� ���
	MyInit();
	glutMainLoop(); //������ â�� ����Ǳ� ������ ����
	
}

void MyDisplay() {
	float vertices[4][3] = { {0.0,130.0,-1.0},{230,500.0,0.3},{500.0,130.0,-1.0},{200.0,0.0,1.0} };
	//3d�� ����� ���� z���� �����ϰ�, 3���� �ﰢ���� ����� ���� 4���� �������� �������ش�.
	float p[3] = { 250.0,100.0,0.5 }; //���� ����Ʈ 3d���̱� ������ x,y,z��������������
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT); //���� �����ϴ� BUFFER�� ���

	for (j = 0; j < 50000; j++) {
		i = rand() % 4; //3d�� ����� ���ؼ� ������ 4���� ���� �� �ϳ��� �������� ����.
		p[0] = (p[0] + vertices[i][0]) / 2.0;  
		p[1] = (p[1] + vertices[i][1]) / 2.0;
		p[2] = (p[2] + vertices[i][2]) / 2.0;
		//�������� ����� ���� x,y,z ��ǥ�� ������ ���� �� 
		glBegin(GL_POINTS);
			glVertex3fv(p);
			//3���� �Ǽ� ���� �Է¹޴� glvertex�� �̿��Ѵ�. �ڿ� v�� �ٿ����ֱ⶧���� �迭��...
		glEnd();
	}
	glFlush(); //�ѹ��� ���
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight); //��ġ, ���� ������� ������ ũ�⿡ ���� ����Ʈ ����
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)500.0;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)500.0;
	//������ ���ؼ� ������ȯ�� �����ϱ� ���� ����

	glMatrixMode(GL_PROJECTION); //������ȯ �Լ�
	glLoadIdentity(); //�׵��Լ��� ����
	glOrtho(0.0 * WidthFactor, 500.0 * WidthFactor, 0.0 * HeightFactor, 500.0 * HeightFactor, 1, -1);
	//���ο� ũ�⿡ ���� glOrtho ��ȭ
}

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //�������� �ʱ�ȭ
	glColor3f(1.0,0.0,0.0); //���������� ����

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //�׵����
	glOrtho(0.0, 500.0, 0.0, 500.0, 1, -1); //�ʱ� ������ȯ

}
