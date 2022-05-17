/***********************************************************************/
/*                     HW#4 : �κ� ��-�� �𵨸�				    	   */
/*  �ۼ��� : �ۼ���                             ��¥ : 2021�� 10�� 26��*/
/*                                                                     */
/* ���� ���� : �𵨺�ȯ�� �̿��ؼ� ��ü�� �̵���Ű�� ȸ��, ũ�⸦ Ű�� */
/* ��. �׸��� push�� pop�� �̿��� ������ �𵨸��� �ϼ���Ų�� ���� ���� */
/* �̴� �κ��� �𵨸��Ѵ�.											   */	
/* ��� : MyDisplay���� ���� �׸��� �׸���, finger �������� �̿��ؼ�   */
/* ���ǵ��� ������Ű��, �ڿ������� ���� �����Ϸ��� �ߴ�. Ű���带 ���� */
/* ���� time �ݹ��Լ��� ȣ����Ѽ� ���������� �հ����� ���� ������ �ϵ�*/
/* �� �߰�, sŰ�� �������� ���ߵ��� �ߴ�.							   */	
/***********************************************************************/

#include <Gl/glut.h>
#define STOP -1 //������ �ǹ��ϴ� ��ũ��

static int shoulder =20, elbow = 20, TwoFinger_bot = 0, TwoFinger_mid = 0, TwoFinger_top = 0; //�ι�° �հ����� ���� ������ �Ʒ���, ���ȿ� ���� ����
bool TwoFinger = true; //�ι�° �հ����� ������ ����
bool OneFinger = true; //ù��° �հ����� ������ ����
float move_X = 0., move_Y = 0.; //ù��° �հ����� x�� y�� ���������ν� �ڿ������� �հ��������� �����ֱ����ؼ� ���.
float Twomove_X = 0., Twomove_Y = 0;//�ι�° �հ����� xy�� ���������ν� �ڿ������� �հ��������� �����Ѵ�.
int op = 0; //� �հ����� true��ų�� ����.
static int OneFinger_bot = 0, OneFinger_mid = 0, OneFinger_top = 0;
bool ThreeFinger = true;//����° �հ��� ����
static int ThreeFinger_bot = 0, ThreeFinger_mid = 0, ThreeFinger_top = 0;
float Threemove_X = 0., Threemove_Y = 0.; //����° �հ��� ���⸦ ���� �������� ����
bool AllFinger = false; //��� �հ��� ���� 
int velocity = 3; //�հ��� �����̴� �ӵ�
bool fold = false;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //�׸� �׸� ��� �ʱ�ȭ �� �ٽ� �׸�

	glMatrixMode(GL_MODELVIEW); //�׵���ķ� �ʱ�ȭ
	glLoadIdentity();
	glPushMatrix();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	
	//�� ���_ �� ��
	glTranslatef(-1.0, 0.0, 0.0); //x�� -1.0 �̵�  
	glRotatef((GLfloat)shoulder, 0.0, 1.0, 1.0);// shoulder������ŭ 0,1,1 �� ȸ��
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0); //�� (0,0)���� ũ�� 2��ŭ Ű���.
	glutWireCube(1.0); //�� �� �� x�� 2�� �簢�� 
	glPopMatrix(); //pop���� ���� TRT�κ����� �̵� �� 0,0,0 ����

	//�Ʒ��� �𵨸�
	glTranslatef(1.0, 0.0, 0.0);//+ 1��ŭ�ؼ� ��ǥ�� 2�� �̵�!
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0); //2,0...
	glPushMatrix(); //ù��° �հ��� �𵨸��� ����
	glPushMatrix(); //�ι�° �հ��� �𵨸��� ����
	glPushMatrix(); //����° �հ��� �𵨸��� ����
	glScalef(2.0, 0.4, 1.0); //ũ�⸦ 2��ŭ Ű����
	glutWireCube(1.0);
	glPopMatrix(); //�Ʒ��� push ����

	//�հ����Ʒ����� �𵨸�
	glTranslatef(1.0, 0.2, 0.6);//�Ʒ��� ��ǥ���� 1.0�̵� �� ȸ��
	glRotatef((GLfloat)OneFinger_bot, 0.0, 0.0, 1.0); //z�� 0,0,1�� �������� ���� ���� ����, �� �Ʒ� ����� 90���ۿ� ȸ���� �ȵȴ�.
	glPushMatrix(); //������ �𵨸��� ���ؼ� ���ÿ� ����
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix();

	//��� ���� �𵨸�
	glTranslatef(0.7 + move_X, 0.0 + move_Y, 0.2);//��� �հ��� ���� ���� Translate���� 0.6��ŭ �̵���Ų �� z�������� ȸ��
	glRotatef((GLfloat)OneFinger_mid, 0.0, 0.0, 1.0);
	glPushMatrix();
	//��� ���� ��ġ�� ���� push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //ũ�⸦ ������ ��� ����� ��ġ�� �̵�

	//������ ���� �𵨸�
	glTranslatef(0.7 + move_X, 0.0 + move_Y, 0.0);//3��° ���� ,����°����� 2��°���𺸴� �� ������ �̵��ϸ�, 180������ ������ �����ϴ�.
	glRotatef((GLfloat)OneFinger_top, 0.0, 0.0, 1.0);
	glPushMatrix(); //������ ���� push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //���������� ���ÿ��� ����
	glPopMatrix();

	//ù��° ������ �������ʰ�, ����ġ���� 2��° �հ��� �𵨸�
	glTranslatef(1.0, 0.2, 0.4);//�Ʒ��� ��ǥ���� 1.0�̵� �� ȸ��
	glRotatef((GLfloat)TwoFinger_bot, 0.0, 0.0, 1.0); //z�� 0,0,1�� �������� ���� ���� ����, �� �Ʒ� ����� 90���ۿ� ȸ���� �ȵȴ�.
	glPushMatrix(); //������ �𵨸��� ���ؼ� ���ÿ� ����
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix();
	
	glTranslatef(0.7 + Twomove_X, 0.0 + Twomove_Y, 0.0);//��� �հ��� ���� ���� Translate���� 0.6��ŭ �̵���Ų �� z�������� ȸ��
	glRotatef((GLfloat)TwoFinger_mid, 0.0, 0.0, 1.0);
	glPushMatrix();
	//��� ���� ��ġ�� ���� push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //ũ�⸦ ������ ��� ����� ��ġ�� �̵�

	glTranslatef(0.7 + Twomove_X, 0.0+ Twomove_Y, 0.0);//3��° ���� ,����°����� 2��°���𺸴� �� ������ �̵��ϸ�, 180������ ������ �����ϴ�.
	glRotatef((GLfloat)TwoFinger_top, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //������ ���� ���ÿ��� ����
	glPopMatrix();

	//����° �հ��� �𵨸�
	glTranslatef(1.0, 0.2,0.0);
	glRotatef((GLfloat)ThreeFinger_bot, 0, 0.0, 1.0); //z�� 0,0,1�� �������� ���� ���� ����, �� �Ʒ� ����� 90���ۿ� ȸ���� �ȵȴ�.
	glPushMatrix(); //������ �𵨸��� ���ؼ� ���ÿ� ����
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.7 + Threemove_X, 0. + Threemove_Y, 0.);//��� �հ��� ���� ���� Translate���� 0.6��ŭ �̵���Ų �� z�������� ȸ��
	glRotatef((GLfloat)ThreeFinger_mid, 0.0, 0.0, 1.0);
	glPushMatrix();
	//��� ���� ��ġ�� ���� push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //ũ�⸦ ������ ��� ����� ��ġ�� �̵�

	glTranslatef(0.7 + Threemove_X, 0. + Threemove_Y, 0.0);//3��° ���� ,����°����� 2��°���𺸴� �� ������ �̵��ϸ�, 180������ ������ �����ϴ�.
	glRotatef((GLfloat)ThreeFinger_top, 0.0, 0.0, 1.0);
	glPushMatrix(); //������ ���� push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); 
	glPopMatrix(); 
	//������ �𵨸��� �ڷḦ ���ÿ��� ���������ν� �����հ����� ���������� �ʰ���
	glutSwapBuffers();

}

//�� Ÿ�̸� �Լ��� keyboard�� �������� �ڵ������� �հ����� �����̴� ���� ǥ���ϱ� ���� �ݹ��Լ��̴�.
//�̶� ���Ǵ� x,y�� �հ����� �������� ������ �������� �����ϱ� ���ؼ� ���� �����̰�, allFinger������ ��� �հ����� ���������Ҷ�
//���Ǵ� bool�Լ��̴�.
//mid�� top, bot���� ���������� ������ ���������� �ڿ������� ������ �����߱⶧���� ��ó�� �����Ͽ���.

void MyTimer(int element) {

	if (fold&&op==5) {
		shoulder += 1;
		elbow += 1;
		if (elbow > 50)
			op = STOP;
	}
	else if(!fold&&op==5){
		shoulder -= 1;
		elbow -= 1;
		if (elbow < 20)
			op = STOP;
	}
	//�հ����� 90�� �̻�Ȳ���.
	//fold���������� �ݺ��� �Ͼ���ʴ� ������ mouse�� �ѹ��� ������ ������ ��� true�̱⶧����.
	if (TwoFinger && (op == 2||AllFinger||fold)) { //ù��° �հ����� ���� 
		Twomove_X = -0.25; //�ι�° �հ����� �������� ���߱� ���ؼ� ���� ������.
		Twomove_Y += 0.01;

		TwoFinger_bot += velocity;
		TwoFinger_mid =(velocity+TwoFinger_bot); //���� ���ʺ��� �ٱ����� �� ũ�Ե��� ������ �̿��ؼ� ���� ������ ���ؼ� �Ҵ��ϴ� ����� ����ߴ�.
		TwoFinger_top =(velocity+TwoFinger_mid);

		if (TwoFinger_bot > 80) {
			TwoFinger = false;

		}
	}
	else if (!TwoFinger && (op == 2||AllFinger||!fold)) {
		Twomove_X = -0.25; //x��ǥ y��ǥ�� ����� �κ��� �����ֱ� ���ؼ� move x�� move y������ ����ߴ�. 
		Twomove_Y -= 0.01; //bot,mid,top�� �̵��Ҷ����� �����༭, �������� ���������ʰ� �ߴ�.
		TwoFinger_bot -= velocity;
		TwoFinger_mid = (TwoFinger_bot - velocity);
		TwoFinger_top = (TwoFinger_mid - velocity);

		if (TwoFinger_bot < 0) {
			TwoFinger = true;
		}

	}
	//���� ����������, ������ �������� ���� x,y�� ����߰�, �ָ��ִ� ���� �������ִ� ���𺸴� �� ũ�� ȸ���ϱ⶧����
	//���� ������ ���ؼ� �Ҵ��ϴ� ����� �̿��ߴ�.
	if (OneFinger && (op == 1||AllFinger||fold)) {
		move_X = -0.25;
		move_Y += 0.01;

		OneFinger_bot += velocity;
		OneFinger_mid = (OneFinger_bot + velocity);
		OneFinger_top = (OneFinger_mid + velocity);
		if (OneFinger_bot > 80) {
			OneFinger = false;
		}
	}
	else if (!OneFinger && (op == 1||AllFinger||!fold)) {
		move_X = -0.25;
		move_Y -= 0.01;

		OneFinger_bot -= velocity;
		OneFinger_mid = (OneFinger_bot - velocity);
		OneFinger_top = (OneFinger_mid - velocity);

		if (OneFinger_bot < 0) {
			OneFinger = true;
		}

	}

	if (ThreeFinger && (op == 3 || AllFinger||fold)) {
		Threemove_X = -0.25;
		Threemove_Y += 0.01;

		ThreeFinger_bot += velocity;
		ThreeFinger_mid = (ThreeFinger_bot + velocity);
		ThreeFinger_top = (ThreeFinger_mid + velocity);
		if (ThreeFinger_bot > 80) { //������ ���� ������ �հ����� ���������ʵ��� ������ ������ ������ 
			ThreeFinger = false;

		}
	}
	else if (!ThreeFinger && (op == 3|| AllFinger|| !fold)) {
		Threemove_X = -0.25;
		Threemove_Y -= 0.01;

		ThreeFinger_bot -= velocity;
		ThreeFinger_mid = (ThreeFinger_bot - velocity);
		ThreeFinger_top = (ThreeFinger_mid - velocity);

		if (ThreeFinger_bot < 0) {
			ThreeFinger = true;
		}

	}
	//��� finger���� �����ϱ� ���ؼ� allfinger�� true�� ��쿣 ��� �հ����� ����, ������ s�� ���� ��� false�� �ٲ�����.
	//�հ������� �ϳ��� �����̰� �ϴ� ������ ����.
	glutPostRedisplay();
	glutTimerFunc(30, MyTimer, 1);
}
//�հ��� ���ÿ� �ɼ��� ������, �ش� key�� �������� �ɼ��� �����Ͽ� timer�ݹ��Լ� ���ο��� �ش� �ɼ��� �����ϵ��� ��.
void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		op = 1;
		glutTimerFunc(30, MyTimer, 1);
		break;
	case '2':
		op = 2;
		glutTimerFunc(30, MyTimer, 1);
		break;
	case '3':
		op = 3;
		glutTimerFunc(30, MyTimer, 1);
		break;
	case '4':
		op = 0; //���հ��� �� ���õǾ��⶧���� op�� 0������, allfinger�� true�� �ȴ�.
		AllFinger = true;
		glutTimerFunc(30, MyTimer, 1);
		break;
	case 's':
		op = 0; //�ʱ�ȭ � �հ����� ���õ�������
		AllFinger = false;
		break;
	}
	//�ɼǿ� ���� �հ����� ����, �� �հ����� ���� ���ڰ� �����ȴ�. ���ڸ� �������� ���޵Ǵ� �������� ���ؼ� �հ����� �̵��ϰԵȴ�.

	glutPostRedisplay();
}
//���콺�� ������ �������� �����⶧���� fold�� true �հ����� ������� �հ��� ������ -> �ѹ��� �����̱� ���ؼ� ����
//���콺 �������� �������� ���ƿ��� ���ؼ� fold�� or�� ������. �� fold true ������ �հ����� false�̸� ���� �ڸ��� ���ư���.
void MyMouse(int button,int state,int x,int y) {

	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		fold = true;
		TwoFinger = true;
		OneFinger = true;
		ThreeFinger = true;

		op = 5;
		glutTimerFunc(30, MyTimer, 1);
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		fold = false;
		AllFinger = false;
		TwoFinger = false;
		OneFinger = false;
		ThreeFinger = false;
		op = 5;
		glutTimerFunc(30, MyTimer, 1);
	}
}

//������ �ʱ�ȭ�� ����, ���� �ʱ�ȭ
void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Robot Arm");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouse);

	glutMainLoop();
	return 0;
}