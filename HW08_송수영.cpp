/***********************************************************************/
/*                    HW#8 :�㿡 ȥ�ڴ޸��� ��                         */
/*  �ۼ��� : �ۼ���                             ��¥ : 2021�� 12�� 08��*/
/*                                                                     */
/* ���� ���� : ��ҹۿ� ���� ���󿡼� ���� �Ѵ밡 �������� ����� ��*/
/* ���ߴ�. �ǹ��� �ڵ��� ��ǥ�� ���� �ռ� �����߰�, �ؽ�ó������ �̿�*/
/* �� ���� �ǹ��� �ƽ���Ʈ�� ǥ���Ͽ���.*/      
/* ��� : Ű���� ���� ������ �̿��� �ڵ����� �����ϼ� �ִ�. Ű���� �ݹ���*/
/*�̿��ؼ� ȭ�� �̵��� �� �� �ִ�.���� ������ ��ġ�Ͽ���.*/
/***********************************************************************/

#include <gl/glut.h>
#include <stdio.h>

GLfloat Movex =10.0;//�ڵ����� ���� �������� �̵��ϵ�����
GLfloat Movey = 0.0;
GLfloat Movez = 0.0;
bool State = false;
GLfloat xAngle=0, yAngle=0, zAngle=-1; //ī�޶� �����µ� �̿��� ����
GLfloat carAngle = 0; //ī�޶� ���� �ڵ����� ����
GLfloat carX, carY, carZ = 0;//ī�޶� ���� �ڵ��� 

//�ڵ��� �𵨸��� ���� �Լ� ������ â�� 
void DrawRightSide() {

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
    //�ڵ��� �𵨸� ���� ���κ� (â������ �ڵ������κ�)
    glVertex3f(-0.5, 0.3, 0.5);
    glVertex3f(0.5, 0.3, 0.5);
    glVertex3f(0.4, 0.5, 0.5);
    glVertex3f(-0.4, 0.5, 0.5);
    glEnd();
    //â������ �ڵ��� �Ʒ��κб���

    glBegin(GL_POLYGON);
    glVertex3f(-0.8, -0.3, 0.5);
    //������ �ֱ� ���ؼ� �κ�����
    glVertex3f(-0.5, -0.3, 0.5);
    glVertex3f(-0.4, -0.05, 0.5);
    glVertex3f(-0.5, 0.3, 0.5);
    glVertex3f(-0.8, 0.1, 0.5);
    glEnd();

    glBegin(GL_POLYGON);

    glVertex3f(-0.4, -0.05, 0.5);
    glVertex3f(-0.2, -0.05, 0.5);
    glVertex3f(-0.3,0.3, 0.5);
    glVertex3f(-0.5, 0.3, 0.5);

    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.2, -0.05, 0.5);
    glVertex3f(-0.1, -0.3, 0.5);
    glVertex3f(0.1, -0.3, 0.5);
    glVertex3f(0.2, -0.05, 0.5);
    glVertex3f(0.1, 0.3, 0.5);
    glVertex3f(-0.3, 0.3, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.2, -0.05, 0.5);
    glVertex3f(0.4,-0.05,0.5);
    glVertex3f(0.5, 0.3, 0.5);
    glVertex3f(0.1, 0.3, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.4, -0.05, 0.5);
    glVertex3f(0.5, -0.3, 0.5);
    glVertex3f(0.7, -0.3, 0.5);
    glVertex3f(0.7, 0.3, 0.5);
    glVertex3f(0.5, 0.3, 0.5);
    glEnd();
}

//�ڵ��� �𵨸� ���� â��
void DrawLeftSide() {

    glBegin(GL_POLYGON);
    //�ڵ��� �𵨸� ���� ���κ� (â������ �ڵ������κ�)
    glVertex3f(-0.5, 0.3, -0.2);
    glVertex3f(-0.4, 0.5, -0.2);
    glVertex3f(0.4, 0.5, -0.2);
    glVertex3f(0.5, 0.3, -0.2);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-0.8, -0.3, -0.2);
    //������ �ֱ� ���ؼ� �κ�����
    glVertex3f(-0.8, 0.1, -0.2);
    glVertex3f(-0.5, 0.3, -0.2);
    glVertex3f(-0.4, -0.05, -0.2);
    glVertex3f(-0.5, -0.3, -0.2);
    glEnd();
    
    glBegin(GL_POLYGON);

    glVertex3f(-0.4, -0.05, -0.2);
    glVertex3f(-0.5, 0.3, -0.2);
    glVertex3f(-0.3, 0.3, -0.2);
    glVertex3f(-0.2, -0.05, -0.2);
    
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.2, -0.05, -0.2);
    glVertex3f(-0.3, 0.3, -0.2);
    glVertex3f(0.1, 0.3, -0.2);
    glVertex3f(0.2, -0.05, -0.2);
    glVertex3f(0.1, -0.3, -0.2);

    glVertex3f(-0.1, -0.3, -0.2);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.2, -0.05, -0.2);
    glVertex3f(0.1, 0.3, -0.2);
    glVertex3f(0.5, 0.3, -0.2);
    glVertex3f(0.4, -0.05, -0.2);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.4, -0.05, -0.2);
    glVertex3f(0.5, 0.3, -0.2);
    glVertex3f(0.7, 0.3, -0.2);
    glVertex3f(0.7, -0.3, -0.2);
    glVertex3f(0.5, -0.3, -0.2);
    glEnd();
}

//�ڵ��� õ�� �𵨸�
void DrawCeiling() {
    glBegin(GL_POLYGON);
    glVertex3f(-0.4,0.5,0.5);
    glVertex3f(0.4, 0.5, 0.5);
    glVertex3f(0.4, 0.5, -0.2);
    glVertex3f(-0.4, 0.5, -0.2);
    glEnd();
}
//�ڵ��� �չ� �𵨸�
void DrawFrontWindshield() {

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, 0.3, 0.5);
    glVertex3f(-0.4, 0.5, 0.5);
    glVertex3f(-0.4, 0.5, -0.2);
    glVertex3f(-0.5, 0.3, -0.2);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
}
//�ڵ��� �� �𵨸�
void DrawFront() {
    glBegin(GL_POLYGON);
    glVertex3f(-0.8, 0.1, -0.2);
    glVertex3f(-0.8, 0.1, 0.5);
    glVertex3f(-0.5, 0.3, 0.5);
    glVertex3f(-0.5, 0.3, -0.2);
    glEnd();

}
//�չ��� �𵨸�
void DrawFrontbumper() {
    
    glBegin(GL_POLYGON);
    glVertex3f(-0.8, -0.3, -0.2);
    glVertex3f(-0.8, -0.3, 0.5);
    glVertex3f(-0.8, 0.1, 0.5);
    glVertex3f(-0.8, 0.1, -0.2);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.81, -0.2, 0.0);
    glVertex3f(-0.81, -0.2, 0.4);
    glVertex3f(-0.81, 0.0, 0.4);
    glVertex3f(-0.81, 0.0, 0.0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
}
//��â�� �𵨸�
void DrawBackWindshield() {
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.3, 0.5);
    glVertex3f(0.5, 0.3, -0.2);
    glVertex3f(0.4, 0.5, -0.2);
    glVertex3f(0.4, 0.5, 0.5);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
}
//�� ��ȣ�� �κ� �𵨸�
void DrawBack() {
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.3, -0.2);
    glVertex3f(0.5, 0.3, 0.5);
    glVertex3f(0.7, 0.3, 0.5);
    glVertex3f(0.7, 0.3, -0.2);
    glEnd();
}
//�޹��� �𵨸�
void DrawBackbumper() {
    glBegin(GL_POLYGON);
    glVertex3f(0.7, -0.3, 0.5);
    glVertex3f(0.7, 0.3, 0.5);
    glVertex3f(0.7, 0.3, -0.2);
    glVertex3f(0.7, -0.3, -0.2);
    glEnd();

}
//���� �𵨸�
void DrawWheel() {
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.2, 0.3, 30, 50);
}
//�ǹ� �𵨸� �ؽ�Ʈ ��Ī
void Drawbuilding() {
    glColor3f(0.5, 0.5, 0.5);

    glTranslatef(0, 0, -6);
    glutSolidCube(5);
    glTranslatef(0, 5, 0);
    glutSolidCube(5);

    glTranslatef(6, -2, -2);
    glutSolidCube(5);
    glTranslatef(0, -3, 0);
    glutSolidCube(5);
    glTranslatef(4, 5, 0);
    glutSolidCube(5);
    glTranslatef(0, -5, 0);
    glutSolidCube(5);

    glTranslatef(-15, 0, 0);
    glutSolidCube(5);

    glTranslatef(0,3,0);
    glutSolidCube(5);


    glTranslatef(-5, -3, 2);
    glutSolidCube(5);
}

//�ø�Ʈ �ٴ� �𵨸� - �ý�Ʈ �����ؼ� ����ó�� �����
void DrawGround() {
   
    glBegin(GL_POLYGON);
    glVertex3f(-40.0, -3, 11.0);
    glVertex3f(40.0, -3, 11.0);
    glVertex3f(40.0, -3, 5.0);
    glVertex3f(-40.0, -3, 5.0);
    glEnd();

}
//���ε��� ����� ���ؼ� glu �̿�
GLUquadricObj* qobj = gluNewQuadric();

//���ε� �𵨸�
void DrawStreetlight() {

    glPushMatrix();
    glTranslatef(5, -0.5, 1);
    glRotatef(90, 1.0, 0, 0);
    gluCylinder(qobj, 0.2, 0.2, 7.0, 50, 8); //���ε� ��
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 1.0, 0, 0);
    glTranslatef(5.0, 2.0, -0.5);
  
    glScalef(0.3, 0.6, 0.3);
    glutSolidTorus(0.3, 1.5, 20, 20); //torus�� cone�� ���ļ� ���ε� �Ӹ��� ǥ����.
    glScalef(6, 6, 8);
    glRotatef(180, 1.0, 0, 0);
    glutSolidCone(0.3,0.5, 12, 12);


    
    glPopMatrix();
  
}
void MyDisplay() {

    glMatrixMode(GL_PROJECTION); //glOrtho�� �ϱ�����.
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -20.0, 20.0); //��������

    
    glMatrixMode(GL_MODELVIEW); //�׵���ķ� �ʱ�ȭ
    glLoadIdentity();
    //�̷��� �����ν� ī�޶� ��ġ�� ����. ������ �����ν�, �������� �����Ͽ� ������ ������� �̵��� �� �ְ���.
    gluLookAt(0.0, 10.0, 5.0, xAngle, yAngle, zAngle, 0, 1, 0); //�̺�Ʈ ó���� ���� ī�޶��� ��ġ�� �̵���ų �� �ִ�.

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�׸� �׸� ��� �ʱ�ȭ �� �ٽ� �׸�

    Drawbuilding(); //�ǹ��𵨸�
    DrawGround(); //�� �𵨸�
    DrawStreetlight(); //���ε� �𵨸�
    //�ڵ����� ������ǥ��� �������� ������ �𵨸�
    glPushMatrix();
    glTranslatef(Movex, 0, 7);
    glScalef(3, 3, 3);
    glRotatef(carAngle, carZ, carY, carZ);
    DrawRightSide();
    DrawCeiling();
    DrawFrontWindshield();
    DrawBackWindshield();
    DrawFront();
    DrawLeftSide();
    DrawBack();
    DrawFrontbumper();
    DrawBackbumper();
    glPushMatrix();
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(0.0, 0.0, 0.0);
    glTranslatef(1.0, -0.6, -0.5);

    DrawWheel();
    glPushMatrix();
    glPopMatrix();
    glTranslatef(0.0, 0.0, 2.0);
    DrawWheel();
    glTranslatef(0.0, 0.0, 0.0);
    glTranslatef(-2.0, 0.0, 0.0);
    DrawWheel();
    glTranslatef(0.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, -2.0);
    DrawWheel();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers(); //�������� �׸��� �׸������ؼ� swapbuffer�� �ٲ���.
}
void MyInit(void) {

    GLfloat global_ambient[] = { 0.3, 0.3, 0.3, 1.0 };	//���� �ֺ��ݻ�

    GLfloat Light0_Ambient[] = { 0.3, 0.3, 0.3, 1.0 };	//0�� ���� Ư��
    GLfloat Light0_Diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat Light0_Specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat Light1_Ambient[] = { 0.3, 0.3, 0.3, 1.0 };	//1�� ���� Ư��
    GLfloat Light1_Diffuse[] = { 0.3, 0.3, 0.3, 0.3 };
    GLfloat Light1_Specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat Light0_Position[] = { 5.0, 10.0, 5.0, 1.0 };	//0�� ������ġ
    GLfloat Light0_Direction[] = { 0.5, 0.5, 0.5 };		//0�� ���� ����
    GLfloat Light0_Cutoff[] = { 90.0 };					//0�� ���� ����

    GLfloat Light1_Position[] = { 0.0, 0.0, 1.0, 1.0 };	//1�� ������ġ

    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0_Ambient);	//0�� ���� Ư���Ҵ�
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0_Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Light0_Specular);

    glLightfv(GL_LIGHT1, GL_AMBIENT, Light1_Ambient);	//1�� ���� Ư���Ҵ�
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1_Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Light1_Specular);

    glLightfv(GL_LIGHT0, GL_POSITION, Light0_Position);	//����Ʈ����Ʈ
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light0_Direction);	//����
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, Light0_Cutoff);	//����
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);			//�ڻ��� �¼�

    GLfloat material_ambient[] = { 0.0, 0.0, 0.0, 1.0 };	//��ü Ư��
    GLfloat material_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat material_shininess[] = { 127.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);//��ü Ư���Ҵ�
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);//�����ֺ��ݻ� 
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //��������


    glShadeModel(GL_SMOOTH);	//���� ���̵�
    glEnable(GL_DEPTH_TEST);	//���� ���� Ȱ��ȭ
    glEnable(GL_LIGHTING);		//���� Ȱ��ȭ
    glEnable(GL_LIGHT0);		//0�� ���� Ȱ��ȭ
    glEnable(GL_LIGHT1);		//1�� ���� Ȱ��ȭ
    glEnable(GL_COLOR_MATERIAL);
}

//k�� l�� ������, ������ �̵����� �پ��� �ð����� �ڵ����� �����̴� ���� ��������
void MyKeyboard(unsigned char key, int x, int y) {
    if (key == 'l' || key == 'L') {//ī�޶��� ��ġ�� ���� �̵��ؼ� ��������
        if (xAngle < 5) {
            xAngle += 1;
        }//xAngle�� �̵���Ŵ
    }
   
    if (key == 'k' || key == 'K')
    {
        if (yAngle < 5)
            yAngle += 1;
    }//yAngle�� �̵���Ŵ

    //���� �������� ���ư�
    if (key == 'j' || key == 'J')
    {
        xAngle = 0;
        yAngle = 0;
    }
     glutPostRedisplay();
}
//Ű���带 ������� �ڵ����� �����̰� �ѹ����� ���� �ٽ� ȭ�鿡 ����
void MySpecial(int key, int x, int y) {

    if (!State) {

        if (key == GLUT_KEY_RIGHT) {
            if (Movex < 20.0) //����Ʈ�� �Ѿ�� �ٽ� �������� �����ϱ� ����
                Movex += 1;
            else
                Movex = -20; //�ǳ� -20���ͽ���
        }
        if (key == GLUT_KEY_LEFT) {
            if (Movex > -20.0) //����Ʈ�� �Ѿ�� �ٽ� ���ƿ����� �����ϱ� ����
                Movex -= 1;
            else
                Movex = 20; //�ǳ�, 20���� ����
        }
    }
    glutPostRedisplay();
}
//�ְ������� �߻����� �ʵ�����
void MyReshape(int NewWidth,int NewHeight) {
    glViewport(0, 0, NewWidth, NewHeight);
    GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)600; //ȭ���� ũ�Ⱑ ���μ��� 600�̱⶧����
    GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)600;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(10.0 * Widthfactor, -10.0 * Widthfactor, 10.0 * Heightfactor, -10.0 * Heightfactor, -20.0, 20.0); //�ְ� �߻��� ���������� �ٽ��ؼ� ��Ⱦ�� ������
}
//��� �𵨸��� �ð�������� �𵨸��߰�, �������ʴ� ���� ������.
void InitVisibility() {
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc,char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("HW#8 Project");
    InitVisibility();
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
}