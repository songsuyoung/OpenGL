/****************************************************************/
/*                      HW#5-2 : RobotVCS                       */
/*  �ۼ��� : �ۼ���                      ��¥ : 2021�� 11�� 02��*/
/*                                                              */
/* ���� ���� : HW#4���� ������ �κ��� ����Ͽ� ������ �ٲ𶧸���*/
/* � ���¸� �����ϴ��� Ȯ���� ����.			                */
/* ��� : HW#4 ��ɿ��ٰ� special callback�Լ��� ���ο� timer ca*/
/* ll�Լ��� �����ν� ����� �߰��Ͽ���.						    */
/* 'end'�� ���� �� ���� �������� ��ȯ, '��'�� ������ (������)����*/
/* �� ������ȯ, '��'�� ������ (����)������ ������ȯ, '��'�� ����*/
/* �� ���� ������ȯ, '��'�� ������ �Ʒ��� ������ȯ              */
/****************************************************************/

#include <Gl/glut.h>

//ī�޶��� ������ �����ϱ� ����
GLfloat pocusX = 0.0, pocusY = 0.0, pocusZ = 90.0; //z���� gluƯ���� �̸� ��������
bool LeftControl = false,RightControl=false,UpControl=false,DownControl=false,InitControl=true;
static int init = 90, LeftLeg = 0, RightLeg = 0, Neck = 0, Head = 0, Leftshoulder = 0, Leftelbow = 0, Rightshoulder = 0, Rightelbow = 0;
//���� ����� �������� �ʱ� ����,���ʴٸ�,�����ʴٸ�,��,�Ӹ�,���ʾ��,������,�����ʾ��,���������� �� ������ �ǹ���
//�ʱ� ������ �ʿ��� ������ glu�� �𵨸��� ���, 90���� ������������ ������ ������ �ٶ󺸴� ���� ����̿��⶧���� �Ϻη�, 90���� ȸ�����Ѽ�
//�� �𵨵��� �𵨸�����.
static bool LeftLeg_Control = false, RightLeg_Control = false, Head_Control = false, RightArm_Control = false, LeftArm_Control = false;
//�� ������ �����ϱ����� bool������, true���Ǿ����� �̵��ϵ��� ��.
bool stop = false;
//stop�� true�� �ɰ��, ��� �������� stop�Ǿ���Ѵ�.
int op = -1;
//�ɼ��� ��� ���õǴ� ������,������ ���õǴ��� ��Ȯ�� ������ ���ؼ� ����� ��������. �ο� ���������δ� ���� �����ϼ��� �ֱ⶧���� ��Ȯ�� ��������
//�����ؼ� ����ߴ�.
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
	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.0, 1.0, 2.0);
	gluCylinder(qobj, 0.5, 0.5, 0.5, 20, 8); //���� �𵨸�
	glPopMatrix(); //���� ũ�⸦ Ű��͸� ���ϰ� �Ǹ�, �Ӹ��� �������� �𵨸��� ������.

	//�Ӹ�
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef((GLfloat)Head, 1.0, 0.0, 0.0); //�Ӹ��� ��� ��������, ���� �ణ �����̰� (�� 5�� �Ӹ� 10��) �Ӹ��� 15�� �������� �̵��� ���ڸ��� ���ư�
	glScalef(1.0, 1.0, 1.0); //ũ�⸦ 1Ű��
	gluSphere(qobj, 1.2, 50, 50);

	//���� ����
	gluQuadricDrawStyle(qobj, GLU_FILL); //������ ���鿹���̶� fill�� �ٲ�
	glTranslatef(-0.5, 0.0, 0.0);
	gluSphere(qobj, 0.3, 50, 50);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(qobj, 0.1, 50, 50);
	glColor3f(1.0, 1.0, 1.0); //������ ��� �������� �ٲٱ� ���ؼ� �� ����

	//������ ����
	gluQuadricDrawStyle(qobj, GLU_FILL); //������ ���鿹���̶� fill�� �ٲ�
	glTranslatef(1.0, 0.0, 0.0);
	gluSphere(qobj, 0.3, 50, 50);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(qobj, 0.1, 50, 50);
	glColor3f(1.0, 1.0, 1.0); //������ ��� �������� �ٲٱ� ���ؼ� �� ����
	gluQuadricDrawStyle(qobj, GLU_LINE); //���� �ܿ� �������� �������� �׸��⶧���� ����

	glPopMatrix();

}

//���� ���-���� �𵨸��ϴ� �Լ��̴�. ���� �ǵ��� ���� �㸮�� ������ �ִ� ���¿���, ����� ���������ʰ� �ȸ� ��� �ٽ� ���� �㸮�� ���� ���ִ� ���¸�
//����� �;���. �׷��� ����� ���� �𵨸��� ������ ������ �����̴� �Ʒ��ȸ� �ش��Ѵ�.
void drawLeftArm() {

	glTranslatef(-1.0, 0.0, 0.0);	 //����� �𵨸��ϱ� ���� �̵� 
	glRotatef((GLfloat)Leftshoulder + 90, 1.0, -1.0, 0.0); // 90�� ȸ���ϴµ�, z������ ȸ����Ų������ �缱�� ���� ����� ���ؼ�
	glPushMatrix();	// ������ �𵨸��� ���ؼ� ����� ���ÿ� ����
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.5, 0.5, 1.5);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8); //��� �𵨸�

	glPopMatrix(); //ũ�⸦ ���ÿ��� ���ϰ�, ��� �𵨸����� ���ƿ�

	glTranslatef(0.0, 0.0, 3.0);
	glRotatef((GLfloat)Leftelbow+90, 1.0, 1.0, 0.0); //���� ����� ��� 90���̱⶧���� Leftelbow�� 0�̴���, 90�� �̸� ȸ���Ȼ���, ���� �㸮�� ���ִ� ���·�
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
	glRotatef((GLfloat)Rightshoulder + 90, 1.0, 1.0, 0.0); // gluƯ�������� 90�� �����µ�, ����� ���������ʰ� �ȸ� �㸮�� ���� �ִٰ� �ǰ�, �ٽ� ���ư��°�
	//ǥ���ϱ� ���ؼ� z�� ȸ��, �� ��� z���� +������.(���� ȸ��)
	glPushMatrix();	// ������ �𵨸��� ���ؼ� ���ÿ� ����
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.5, 0.5, 1.5);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8); //��� �׸���

	glPopMatrix(); //ũ�⸦ ������, ����� TR�� ���ư�.

	glTranslatef(0.0, 0.0, 3.0); //�̵���
	glRotatef((GLfloat)Rightelbow +90, 1.0,-1.0, 0.0); //������ ����������, (���� ȸ���� �ݴ�� ����ȸ���� �ϱ� ���ؼ� -1�� ��.)
	glScalef(0.5, 0.5, 1.0); //ũ�� Ű���
	gluCylinder(qobj, 1.0, 1.0, 1.0, 20, 8); //�Ʒ� ���� �׸�/

	glTranslatef(0.0, 0.0, 1.5);
	glScalef(1.0, 0.5, 0.5);
	gluSphere(qobj, 1.0, 50, 50); //���� �𵨸�.
	glPopMatrix(); //���� �׸� �Ʒ����� ���ؼ�, �ؿ� �ʿ��� �������𵨸��� ������ �����ʵ�����.

}

//����,�� �ٸ��� �𵨸��ϰ�, ������ �𵨸��ϴµ� ����ϴ� �Լ����� ȣ���� ���� �׸��� �׸��� �ݹ��Լ��̴�.
void MyDisplay() {
	glMatrixMode(GL_MODELVIEW); //�׵���ķ� �ʱ�ȭ
	glLoadIdentity();
	gluLookAt(0.0,0.0,0.0, pocusX, pocusY, pocusZ, 0.0, 1.0, 0.0); //�׵���ķ� �ʱ�ȭ�� ��, gluLookAt�� ����
	//�̷��� �����ν� ī�޶� ��ġ�� ����. ������ �����ν�, �������� �����Ͽ� ������ ������� �̵��� �� �ְ���.
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //�׸� �׸� ��� �ʱ�ȭ �� �ٽ� �׸�
	glPushMatrix();
	//������ ���, �̵��� �����ʱ� ������ �������� �𵨸����� �����ؾ��ҰͰ��Ƽ� ���ÿ� ���������ʾҴ�. 

	glTranslatef(0.0, 0.0, 0.0);	 // Pivot ���� �� ��ü �̵�
	glRotatef((GLfloat)init, 1.0, 0.0, 0.0); // glu�� ��� 90�� ������ ȸ����������� ���� ���� �𵨸��� ����� �����ִ�.
	glColor3f(1.0, 1.0, 1.0);
	glScalef(3.0, 3.0, 3.0);
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8);
	glPopMatrix(); //���ÿ� ���Ե����� �ʾ�����, TRS�� �ڵ������� ���̱⶧���� �ڵ������� ���� �κ��� pop���ش�

	glPushMatrix(); //���ÿ� �ٽ� �׵������ �������ش�. �� ���ĺ��ʹ� �������� �𵨸��� ����ϱ� ������ �� ������ �ߴ�.
	//���� �ٸ��ϼ�
	glTranslatef(-0.3, 0.5, -0.8);	 // �ٸ��� ��ġ�� ���� �̵����ϰ�
	glRotatef((GLfloat)LeftLeg + 90, 1.0, 0.0, 0.0); //������ ������ ���ÿ� �����ʾұ⶧���� glu�� Ư���� 90���� ������ä ����ؾ��ؼ� 90�� �������.
	glTranslatef(-0.3, 0.5, 4.5);	// ��ġ�� �̵�����
	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.0, 1.0, 2.0); //ũ�⸦ Ű���
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //���� �ٸ��� �𵨸��Ѵ�.
	glTranslatef(0.0, 0.0, 1.5); //������ �� �������µ� , z���� �ø��� ������ glRotate���� y��� z���� ������ �ٲ���⶧���̴�.
	gluCylinder(qobj, 0.3, 0.5, 0.5, 20, 8);  //���� �𵨸����ش�.
	glPopMatrix(); //���� ���������� �𵨸��� �ٸ��� ���������ν� �ؿ� ������ �����ʵ��� �Ѵ�.


	//�����ʴٸ�
	glPushMatrix();
	glTranslatef(0.3, 0.5, -0.8);	 // ������ �ٸ��� ���������� ���ʴٸ��� ����ѵ�, ���ʴٸ��� +0.3�Ѹ�ŭ �̵����� �ָ� ���� ���̰����� �������ϴ�.
	glRotatef((GLfloat)RightLeg + 90, 1.0, 0.0, 0.0); // ���� ���������� gluƯ���� 90�� ���ߴ�.
	glTranslatef(0.3, 0.5, 4.5);

	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.0, 1.0, 2.0); //ũ�⸦ Ű���
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //�����ٸ� �𵨸� ��
	glTranslatef(0.0, 0.0, 1.5); // ������ ������
	gluCylinder(qobj, 0.3, 0.5, 0.5, 20, 8); //�������� �𵨸�.
	glPopMatrix(); //�����ٸ��� ���������� �𵨸��� ������ ��.

	//�� �Ӹ�
	glPushMatrix();
	drawNeckAndHead();

	glPushMatrix();
	//������ �׸���
	drawLeftArm();
	//������ �׸���
	glPushMatrix();
	drawRightArm();

	glutSwapBuffers();
}

//���� �ڵ������� �������� ǥ���� �ݹ��Լ�
void MyTimer(int element) {

	//���� ��� ���õ� �޴��� �ش��ϴ� �οﺯ����, �ɼ��� �´� if������ ���� �������� ǥ���ϵ��� ��.
	if (LeftLeg_Control && op == 5 && !stop) {
		LeftLeg -= 1;
		if (LeftLeg < -25) //30������ ���� �÷ȴٰ� else�� ���� ����.
			LeftLeg_Control = false;
	}
	else if (!LeftLeg_Control && op == 5 && !stop) {
		LeftLeg += 1;
		if (LeftLeg > 0)
			stop = true;
	}
	if (RightLeg_Control && op == 4 && !stop) {
		RightLeg -= 1;
		if (RightLeg <-25) //���������� if���� ���õǸ�, 30������ �÷ȴٰ� else�� ���� ����
			RightLeg_Control = false;
	}
	else if (!RightLeg_Control && op == 4 && !stop) {
		RightLeg+= 1;
		if (RightLeg > 0)
			stop = true;
	}
	if (Head_Control && op == 1 && !stop) {
		if (Neck > 5) { //�ΰ��� ��츦 ������ ���� 5�� ������
			Neck += 0;
			if (Head > 10) //�Ӹ��� �� ������ ������,������ �λ��ϴ� ������ �ֱ����� 10���� ����.
				Head_Control = false;
		}
		Neck += 1;
		Head += 1;
	}
	else if (!Head_Control && op == 1 && !stop)
	{
		if (Neck < 0) { //else if���� �ش� ��,�Ӹ��� �ø�
			Neck += 0;
			if (Head < 0)
				stop = true;
		}
		Neck -= 1;
		Head -= 1;
	}
	if (RightArm_Control && op == 2 && !stop) {
		Rightelbow -= 1;

		if (Rightelbow < -90) { 
			RightArm_Control = false;
		}
	}
	else if (!RightArm_Control && op == 2 && !stop) {
		Rightelbow += 1;
		if (Rightelbow > 0) 
			stop = true;
	}
	if (LeftArm_Control && op == 3 && !stop) {
		Leftelbow -= 1;
		if (Leftelbow < -90) //���� rightArm�� �������� ������.
			LeftArm_Control = false;
	}
	else if (!LeftArm_Control && op == 3 && !stop) {
		Leftelbow += 1;
		if (Leftelbow > 0)
			stop = true;
	}
	glutPostRedisplay();
	glutTimerFunc(30, MyTimer, 1); //timer�� �ѹ��� ȣ���ϱ� ������, �ڿ������� �������� ǥ���ϱ� ���ؼ� �ݺ��� ȣ���� ����
}

//���õǴ� �޴��� ���� timer�� �̵��ؼ� �𵨵��� �����̵����ϴ� �Լ�.
void MyMainMenu(int value) {

	if (value == 1) {
		op = 1;
		RightLeg_Control = false; //�����ٸ��� �����̱�
		LeftLeg_Control = false; //�޴ٸ��� ���������ʾƾ���
		Head_Control = true;
		stop = false; //s�������� �̵� ����.
		glutTimerFunc(30, MyTimer, 1);
	}
	if (value == 2) {
		op = 2;
		RightLeg_Control = false; //�����ٸ��� �����̱�
		LeftLeg_Control = false; //�޴ٸ��� ���������ʾƾ���
		Head_Control = false;
		RightArm_Control = true;
		stop = false; //s�������� �̵� ����.
		glutTimerFunc(30, MyTimer, 1);
	}
	if (value == 3) {
		op = 3;
		LeftArm_Control = true;
		RightLeg_Control = false; //�����ٸ��� �����̱�
		LeftLeg_Control = false; //�޴ٸ��� ���������ʾƾ���
		Head_Control = false;
		stop = false; //s�������� �̵� ����.
		glutTimerFunc(30, MyTimer, 1);
	}
	if (value == 4) { //�����ٸ��� �޴ٸ��� �����ϱ� ���ؼ��� bool������ ������ �Ϲ� ���� ������ �ϳ��ξ �ٸ� ������ �����ߴ�.
		op = 4; //4���� �����ٸ��� �ǹ�
		RightLeg_Control = true; //�����ٸ��� �����̱�
		LeftLeg_Control = false; //�޴ٸ��� ���������ʾƾ���
		Head_Control = false;
		RightArm_Control = false;
		LeftArm_Control = false;
		stop = false; //s�������� �̵� ����.
		glutTimerFunc(30, MyTimer, 1);
	}
	if (value == 5) {
		op = 5;
		LeftLeg_Control = true;
		RightLeg_Control = false;
		Head_Control = false;
		RightArm_Control = false;
		LeftArm_Control = false;
		stop = false;
		glutTimerFunc(30, MyTimer, 1);
	}
}
void MyKeyboard(unsigned char key, int x, int y) {

	if (key == 's') {//sŰ�� ������� stop�� true�� �Ǹ鼭 �������� ����
		op = -1;
		stop = true;
	}
	glutPostRedisplay();
}

//�޴��� ���콺 ������ ��ư�� �޵��� �����ν�, �޴��� �����Ҽ� �ְ���.
void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);

	glutAddMenuEntry("Robot's head movement", 1);
	glutAddMenuEntry("Robot's right arm movement", 2);
	glutAddMenuEntry("Robot's left arm movement", 3);

	glutAddMenuEntry("Robot's right leg movement", 4);
	glutAddMenuEntry("Robot's left leg movement", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	gluQuadricDrawStyle(qobj, GLU_LINE); //qobj�� �������� �׸������ؼ� ���.
}

//gluLookAt���� ������ �������� Timer callback���� ���� ������Ŵ���ν�(ī�޶��� �̵��� ���� ����) ������ ���� �ɶ� ���ߵ����Ѵ�.
//1.0�� �������ν� ī�޶� ���� ����ų�� ���ߵ��� �Ͽ���.
void MyViewTimer(int value) {

	if (RightControl) {
		if(pocusX<=360)
			pocusX += 1.0;
	}//X��ǥ�� ������ 1.0 ����
	if (LeftControl)
		if(pocusX>=-360)
			pocusX -= 1.0;
	if (UpControl)
			pocusY += 1.0;
	if (DownControl)
			pocusY -= 1.0;

	if (InitControl)
	{
		if (pocusX > 0)
			pocusX -= 1.0;
		if (pocusX < 0)
			pocusX += 1.0;
		if (pocusY > 0)
			pocusY -= 1.0;
		if (pocusY < 0)
			pocusY += 1.0;
	}
	glutPostRedisplay();
	glutTimerFunc(30, MyViewTimer, 1);
}
//special callback�Լ��� �̿��ؼ�, ����ȿ��� ����� Ű�� ������, ī�޶��� ������ �����ϵ��� �Ͽ���
//��ɿ��� �����Ѱ�ó�� �����Ű�� �̿��Ͽ���, �� ��ġ�� �������� 'End'Ű�� �̿��Ͽ���.
//Ű�� ������ , �ش� control�� true�� �������´ٸ�, timer���ο��� true�� �ش��ϴ� if���� �����̵��� �����ߴ�.
void MySpecial(int key, int x, int y) {

	if (key == GLUT_KEY_RIGHT) {
		RightControl = true; 
		LeftControl = false;
		DownControl = false;
		UpControl = false;
		InitControl = false;
		glutTimerFunc(30, MyViewTimer, 1);
	}
	if (key == GLUT_KEY_LEFT) {
		LeftControl = true;
		RightControl = false;
		DownControl = false;
		UpControl = false;
		InitControl = false;
		glutTimerFunc(30, MyViewTimer, 1);
	}
	if (key == GLUT_KEY_UP) {
		LeftControl = false;
		RightControl = false;
		UpControl = true;
		DownControl = false;
		InitControl = false;
		glutTimerFunc(30, MyViewTimer, 1);

	}
	if (key == GLUT_KEY_DOWN) {
		LeftControl = false;
		RightControl = false;
		UpControl = false;
		DownControl = true;
		InitControl = false;
		glutTimerFunc(30, MyViewTimer, 1);
	}
	if (key == GLUT_KEY_END) {
		LeftControl = false;
		RightControl = false;
		UpControl = false;
		DownControl = false;
		InitControl = true;
		glutTimerFunc(30, MyViewTimer, 1);
	}
	glutPostRedisplay();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("5-2# RobotVCS");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial); //up down left right �� ���� �ڵ��� ���� �̵�
	glutMainLoop();
	return 0;
}