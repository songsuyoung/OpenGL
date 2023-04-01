/***********************************************************************/
/*                         HW#7 : �κ� ����		                       */
/*  �ۼ��� : �ۼ���                          ��¥ : 2021�� 11�� 22��   */
/*                                                                     */
/* ���� ���� : HW#4���� ������ �κ��� �̿��Ͽ� ������ �ְ� �޸��� ��� */
/* �� ������									                       */
/* ��� : init���� ������ enable �� ���հ��� �����ν� ������ �����ϰ�, */
/* ����, Ű�����ݹ鿡�� r�� R�� ������ Timer�ݹ��� �̿��Ͽ�, sin�� �̿�*/
/* �� ���� ������� �κ��� �޸� ���� ǥ�� �ߴ�.						   */
/***********************************************************************/

#include <Gl/glut.h>
#include <stdlib.h>
#include <math.h>

GLfloat pocusX = 0.0, pocusY = 0.0, pocusZ = 90.0; //z���� gluƯ���� �̸� ��������
static double time = 0; //�κ��� �ȴٸ��� �ڿ������� �����̱� ���� ������ time����
static GLint Right = 0,Left=0; //���� ���Ƹ��κа� ���� ���Ƹ� �κ��� ǥ���ϱ� ����.

static float init = 90, LeftLeg = 0, RightLeg = 0, Neck = 0, Head = 0, Leftshoulder = 0, Leftelbow = 0, Rightshoulder = 0, Rightelbow = 0;
//���� ����� �������� �ʱ� ����,���ʴٸ�,�����ʴٸ�,��,�Ӹ�,���ʾ��,������,�����ʾ��,���������� �� ������ �ǹ���
//�ʱ� ������ �ʿ��� ������ glu�� �𵨸��� ���, 90���� ������������ ������ ������ �ٶ󺸴� ���� ����̿��⶧���� �Ϻη�, 90���� ȸ�����Ѽ�
//�� �𵨵��� �𵨸�����.
GLUquadricObj* qobj = gluNewQuadric();
//���� primitive�� �� �κ��� �𵨸��ϱ� ���� ������� �ش�Ǵ� glu�� �̿��Ͽ���.

//��� �Ӹ��� �𵨸��ϴ� �Լ��̴�. ����� ���� �Ӹ��� �����̴� �������ƴ�, ���� �����̸鼭, �Ӹ��� �������� ���� �����̱� ������ ���� ����������
//��� �𵨸��ϰ� �Ǿ���.
void drawNeckAndHead() {

	//���� �𵨸�. �������� ������ pop�߱⶧����, �� ���� 90�� ������ �𵨸��� ������.
	glTranslatef(0.0, 0.8, -1.0);
	glRotatef((GLfloat)Neck + 90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.8, 0.0);
	glPushMatrix();	// ���� �׸��µ� �ʿ��� ��ȯ ���ÿ� ����
	glScalef(1.0, 1.0, 2.0);
	gluCylinder(qobj, 0.5, 0.5, 0.5, 20, 8); //���� �𵨸�
	glPopMatrix(); //���� ũ�⸦ Ű��͸� ���ϰ� �Ǹ�, �Ӹ��� �������� �𵨸��� ������.

	//�Ӹ�
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef((GLfloat)Head, 1.0, 0.0, 0.0); //�Ӹ��� ��� ��������, ���� �ణ �����̰� (�� 5�� �Ӹ� 10��) �Ӹ��� 15�� �������� �̵��� ���ڸ��� ���ư�
	glScalef(1.0, 1.0, 1.0); //ũ�⸦ 1Ű��
	gluSphere(qobj, 1.2, 50, 50);

	glPopMatrix();

}

//���� ���-���� �𵨸��ϴ� �Լ��̴�. ���� �ǵ��� ���� �㸮�� ������ �ִ� ���¿���, ����� ���������ʰ� �ȸ� ��� �ٽ� ���� �㸮�� ���� ���ִ� ���¸�
//����� �;���. �׷��� ����� ���� �𵨸��� ������ ������ �����̴� �Ʒ��ȸ� �ش��Ѵ�.
void drawLeftArm() {

	glTranslatef(-1.0, 0.0, 0.0);	 //����� �𵨸��ϱ� ���� �̵� 
	glRotatef((GLfloat)Leftshoulder + 90, 1.0, 0.0, -0.5); // 90�� ȸ���ϴµ�, z������ ȸ����Ų������ �缱�� ���� ����� ���ؼ�
	glPushMatrix();	// ������ �𵨸��� ���ؼ� ����� ���ÿ� ����
	glScalef(0.5, 0.5, 1.5);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8); //��� �𵨸�

	glPopMatrix(); //ũ�⸦ ���ÿ��� ���ϰ�, ��� �𵨸����� ���ƿ�

	glTranslatef(0.0, 0.0, 3.0);
	glRotatef((GLfloat)Leftelbow -60 , 1.0, 0.0,0.0); //���� ����� ��� 90���̱⶧���� Leftelbow�� 0�̴���, 90�� �̸� ȸ���Ȼ���, ���� �㸮�� ���ִ� ���·�
	//����� ���ؼ� -120���� ���ش�. (�ֳ��ϸ� ���� �𵨸��̱⶧���� -������ �Ǿ���Ѵ�.
	glScalef(0.5, 0.5, 1.0);
	gluCylinder(qobj, 1.0, 1.0, 1.0, 20, 8); //�� �𵨸�

	glTranslatef(0.0, 0.0, 1.5);
	glScalef(1.0, 0.5, 0.5);
	gluSphere(qobj, 1.0, 50, 50); // �� �𵨸�

	glPopMatrix();

}

//������ ���-���� �𵨸��ϴ� �Լ��̴�. ���� �ǵ��� ���������� ���� �㸮�� ¤�� �ִ� ���¿���, ��ٰ�, �ٽ� �㸮�� ¤���ִ� �ڼ��� ���ư��� �������� ��������
//�𵨸��ߴ�.
void drawRightArm() {

	glTranslatef(1.0, 0.0, 0.0);	 // ������ ����� �׷����� ������ �̵�
	glRotatef((GLfloat)Rightshoulder + 90, 1.0, 0.0,0.5); // gluƯ�������� 90�� �����µ�, ����� ���������ʰ� �ȸ� �㸮�� ���� �ִٰ� �ǰ�, �ٽ� ���ư��°�
	//ǥ���ϱ� ���ؼ� z�� ȸ��, �� ��� z���� +������.(���� ȸ��)
	glPushMatrix();	// ������ �𵨸��� ���ؼ� ���ÿ� ����
	glScalef(0.5, 0.5, 1.5);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8); //��� �׸���

	glPopMatrix(); //ũ�⸦ ������, ����� TR�� ���ư�.

	glTranslatef(0.0, 0.0, 3.0); //�̵���
	glRotatef((GLfloat)Rightelbow-90, 1.0, 0.0,0.0);
	glScalef(0.5, 0.5, 1.0); //ũ�� Ű���
	gluCylinder(qobj, 1.0, 1.0, 1.0, 20, 8); //�Ʒ� ���� �׸�/

	glTranslatef(0.0, 0.0, 1.5);
	glScalef(1.0, 0.5, 0.5);
	gluSphere(qobj, 1.0, 50, 50); //���� �𵨸�.
	glPopMatrix(); //���� �׸� �Ʒ����� ���ؼ�, �ؿ� �ʿ��� �������𵨸��� ������ �����ʵ�����.

}

//����,�� �ٸ��� �𵨸��ϰ�, ������ �𵨸��ϴµ� ����ϴ� �Լ����� ȣ���� ���� �׸��� �׸��� �ݹ��Լ��̴�.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //�׵���ķ� �ʱ�ȭ
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, pocusX, pocusY, pocusZ, 0.0, 1.0, 0.0); //�׵���ķ� �ʱ�ȭ�� ��, gluLookAt�� ����
	//�̷��� �����ν� ī�޶� ��ġ�� ����. ������ �����ν�, �������� �����Ͽ� ������ ������� �̵��� �� �ְ���.
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glPushMatrix();
	//������ ���, �̵��� �����ʱ� ������ �������� �𵨸����� �����ؾ��ҰͰ��Ƽ� ���ÿ� ���������ʾҴ�. 

	glColor3f(0.2, 0.3, 0.5);

	glTranslatef(0.0, 0.0, 0.0);	 // Pivot ���� �� ��ü �̵�

	glRotatef((GLfloat)init, 1.0, 0.0, 0.0); // glu�� ��� 90�� ������ ȸ����������� ���� ���� �𵨸��� ����� �����ִ�.
	glTranslatef(0.0, 0.0, 0.0);	 // Pivot ���� �� ��ü �̵�
	gluQuadricDrawStyle(qobj, GLU_FILL);
	glScalef(3.0, 3.0, 3.0);
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8);
	glPopMatrix(); //���ÿ� ���Ե����� �ʾ�����, TRS�� �ڵ������� ���̱⶧���� �ڵ������� ���� �κ��� pop���ش�

	glPushMatrix(); //���ÿ� �ٽ� �׵������ �������ش�. �� ���ĺ��ʹ� �������� �𵨸��� ����ϱ� ������ �� ������ �ߴ�.
	//���� �ٸ��ϼ�

	glTranslatef(0.0, 0.0, 0.0);	 // �ٸ��� ��ġ�� ���� �̵����ϰ�
	glRotatef((GLfloat)LeftLeg + 90, 1.0, 0.0, 0.0); //������ ������ ���ÿ� �����ʾұ⶧���� glu�� Ư���� 90���� ������ä ����ؾ��ؼ� 90�� �������.
	glTranslatef(-0.7, 0.0, 4.0);	// ��ġ�� �̵�����
	glScalef(1.0, 1.0, 1.5); //ũ�⸦ Ű���
	//glRotatef((GLfloat)Left, 1.0, 0.0, 0.0); //������ ������ ���ÿ� �����ʾұ⶧���� glu�� Ư���� 90���� ������ä ����ؾ��ؼ� 90�� �������.
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //���� �������� �𵨸��Ѵ�.
	
	//���� �� �ٸ� �𵨸� 
	glTranslatef(0.0, 0.0, 1.0);
	glRotatef((GLfloat)Left, 1.0, 0.0, 0.0); //������ ������ ���ÿ� �����ʾұ⶧���� glu�� Ư���� 90���� ������ä ����ؾ��ؼ� 90�� �������.
	glScalef(1.0, 1.0, 1.0); //ũ�⸦ Ű���
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //�������� �𵨸� ��

	glTranslatef(0.0, 0.0, 1.5); //������ �� �������µ� , z���� �ø��� ������ glRotate���� y��� z���� ������ �ٲ���⶧���̴�.
	gluCylinder(qobj, 0.3, 0.5, 0.5, 20, 8);  //���� �𵨸����ش�.
	glPopMatrix(); //���� ���������� �𵨸��� �ٸ��� ���������ν� �ؿ� ������ �����ʵ��� �Ѵ�.


	//�����ʴٸ�
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);	 // ������ �ٸ��� ���������� ���ʴٸ��� ����ѵ�, ���ʴٸ��� +0.3�Ѹ�ŭ �̵����� �ָ� ���� ���̰����� �������ϴ�.
	glRotatef((GLfloat)RightLeg + 90, 1.0, 0.0, 0.0); // ���� ���������� gluƯ���� 90�� ���ߴ�.
	glTranslatef(0.7, 0.0, 4.0);
	glScalef(1.0, 1.0, 1.5); //ũ�⸦ Ű���
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //�������� �𵨸� ��
	
	glTranslatef(0.0, 0.0, 1.0);
	glRotatef((GLfloat)Right, 1.0, 0.0, 0.0); //������ ������ ���ÿ� �����ʾұ⶧���� glu�� Ư���� 90���� ������ä ����ؾ��ؼ� 90�� �������.
	glScalef(1.0, 1.0, 1.0); //ũ�⸦ Ű���
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //�������� �𵨸� ��

	glTranslatef(0.0, 0.0, 1.5); // ������ ������
	gluCylinder(qobj, 0.3, 0.5, 0.5, 20, 8); //�������� �𵨸�.
	glPopMatrix(); //�����ٸ��� ���������� �𵨸��� ������ ��.


	//�� �Ӹ�
	glPushMatrix();
	drawNeckAndHead();

	gluQuadricDrawStyle(qobj, GLU_FILL);

	glPushMatrix();
	//������ �׸���
	gluQuadricDrawStyle(qobj, GLU_FILL);

	drawLeftArm();
	//������ �׸���
	glPushMatrix();
	drawRightArm();

	glutSwapBuffers();
}

//���� �ڵ������� �޸��⸦ ǥ���� �ݹ��Լ�
void MyTimer(int element) {
	time = time + 0.1047;//�ð� ��������.
	
	Leftshoulder = sin(time) * 40;//������ 40�� ������.
	Rightshoulder = -Leftshoulder;//�������� ���� �ݴ�� 20�� ����.

	LeftLeg = -sin(time) * 20;//�޴ٸ��� �����Ȱ� ���� ������. (sin���� �ð� ���� ���� �����ν� �̵��ϴ� ����� ǥ��
	RightLeg = -LeftLeg;//�����ٸ��� ���Ȱ� ���� ������.

	Left = fabs(LeftLeg / 0.5f); //�޹����� �ٸ� ������ 0.5f�� ���� ���밢����, �ٸ��� ������ �޸��⸦ ǥ��
	Right = fabs(RightLeg / 0.5f);//���������� �ٸ� ������ 0.5f�� ���� ���밢����, �ٸ��� ������ �޸��⸦ ǥ��

	glutPostRedisplay();
	glutTimerFunc(30, MyTimer, 1); //timer�� �ѹ��� ȣ���ϱ� ������, �ڿ������� �������� ǥ���ϱ� ���ؼ� �ݺ��� ȣ���� ����
}

//�� �Ȱ� ��ٸ��� �޸��� �������� ǥ���ϱ� ���� ���Ǵ� Ű�����ݹ�
void MyKeyboard(unsigned char key, int x, int y) {

	if (key == 'r'|| key=='R') {//sŰ�� ������� stop�� true�� �Ǹ鼭 �������� ����
		glutTimerFunc(30, MyTimer, 1); //timer�� �ѹ��� ȣ���ϱ� ������, �ڿ������� �������� ǥ���ϱ� ���ؼ� �ݺ��� ȣ���� ����
	}
	glutPostRedisplay();
}

//init�Լ� ���ο��� ������ �ʱ�ȭ�����ν� ���� ǥ����.
void MyInit(void) {
	glEnable(GL_DEPTH_TEST); //���̸� enable��Ŵ
	glEnable(GL_NORMALIZE); //�������͸� ��������
	glEnable(GL_LIGHTING); //������

	//���� ���� ������ ����
	GLfloat ambientLight[] = { 0.3f,0.3f,0.3f,1.0f };
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat position[] = { 400.0f,300.0f,700.0f,1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //�ֺ����� ��Ÿ���� ��������,
	//��ü���� �����⸦ ����� ���� ���� ������ �յ��ϰ� ���� ������ ����.
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	//�߻걤���� Ư�� ����� ��ġ��
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular); 
	//�ݻ籤����, ������Ʈ�� ǥ���� �� �൵��
	glLightfv(GL_LIGHT0, GL_POSITION, position); //������ ��ġ ����
	glEnable(GL_LIGHT0); //���� 0���� enable��Ų��.

	glEnable(GL_COLOR_MATERIAL); //���� ���� enable
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//�ո鿡 ���� ����
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//�ݻ籤 ����
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	//���� ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}

//������ â�� ����Ǿ �Ȱ��� �׸��� �����ϱ� ���ؼ� ���.
void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("7�� Robot ����");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}