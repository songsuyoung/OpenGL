/****************************************************************/
/*                      HW#6 : glViewPort                       */
/*  �ۼ��� : �ۼ���                      ��¥ : 2021�� 11�� 09��*/
/*                                                              */
/* ���� ���� : ������ �� viewport�� Ű���� ��ǥ(g,d,f) ���� �Ʒ�*/
/* viewport�� Ű���� ��ǥ(l,j,k) �� ������ Ű���� ��ǥ�� �̿��ؼ�*/
/*  ī�޶��� ��ġ�� �̵����� �׷��� �𵨸��� ��������� �� �� �ִ�.*/    
/* ��� : Draw�Լ����� teapot�� torus 2���� �׸���, ���� �����Ŵ*/
/* MyReshape�� �̿��ؼ� �����찡 �ٲ� ���� viewport�� �����Ű��*/
/* glOrtho�� ��Ⱦ��� gluPerspective�� ��Ⱦ�� ��ġ���� ũ�Ⱑ ��*/
/* ��Ǵ��� �ְ������� ������ �ʵ����ߴ�. ����, display�ݹ��� �̿�*/
/* �� �׸��� �׸��� Ű���� �ݹ��� �̿��ؼ� ������ ������Ű�� */
/*  ī�޶��� ��ġ�� �̵����״�.*/    
/****************************************************************/

#include <gl/glut.h>

GLfloat leftfocusX = 0.0, leftfocusY = 0.0, leftfocusZ = 0.0;
//glOrtho�� focus�̵��� ����
GLfloat rightfocusX = 1.0, rightfocusY = -1.0, rightfocusZ = -2.0;
//gluPerspective�� ī�޶� ��ġ�� �̵���Ű�� ����.
GLint Width = 800, Height = 800; //���� ȭ��ũ��
GLfloat Widthfactor = (GLfloat)Width / (GLfloat)800, Heightfactor = (GLfloat)Height / (GLfloat)800; //������Ⱦ��

//���� �𵨸���, push/pop�� �̿��� �������� ������.
void Draw() {
    //���պ�ȯ�� �ؼ� �ϳ��� ȭ�鿡 �������� �׸��� �ֵ��� ��.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //��(���)
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(0.0, 0.0, 1.5);
    glutWireTeapot(1.0); //�����ڸ� �׸�
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); //��(������)
    glTranslatef(0, 0.5, 0);
    glRotatef(-45, 0, 1, 0);
    glScalef(0.1, 0.1, 0.1);
    glRotatef(45, 0, 1, 0);
    glutWireTorus(0.5, 1.0, 60, 60); //torus�� �׸�
    glPopMatrix();

    //���պ�ȯ ����.
    glPushMatrix();
    glColor3f(1.0, 0.0, 1.0); //���ֻ�
    glTranslatef(0.5, -0.5, 0.5);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(60, 1, 0, 0);
    glutWireTorus(0.5, 1.0, 60, 60); //torus�� �׸�
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����ۿ� ���̹��۸� �ʱ�ȭ
    
    glViewport(0, 0, Width / 2, Height / 2); //�ϳ��� �����쿡 4���� ����Ʈ�� ��. ������ �����ϴܰ� �����ʻ�ܸ� �̿��� ��
    glMatrixMode(GL_PROJECTION); //glOrtho�� �ϱ�����.
    glLoadIdentity();
    glOrtho(-1.0 * Widthfactor, 1.0 * Widthfactor, -1.0 * Heightfactor, 1.0 * Heightfactor, -1.0, 1.0);  //���ϴ��� glOrtho�� �̿��ؼ� ���� ��
 
    glMatrixMode(GL_MODELVIEW); //�𵨺����
    glLoadIdentity(); //�׵���ķ� �ʱ�ȭ
    glPushMatrix();
    gluLookAt(leftfocusX, leftfocusY, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    gluLookAt(leftfocusX, leftfocusY, leftfocusZ, 0.3,0.3,1.5, 0.0, 1.0, 0.0); //ī�޶��� ��ġ�� Ű�����Է¿����� �ٲٱ� ���ؼ� ������ ����.
    Draw(); //�����׸��� �׸�
    glPopMatrix(); //���� 
    
    glViewport(Width/2, Height/2, Width / 2, Height / 2);//������ ��ܿ� viewport�� ������ ���.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1.0f*Widthfactor/Heightfactor,1,1000); //gluPerspective�� �̿��ؼ� ����������ķ� ����

    glMatrixMode(GL_MODELVIEW); //�𵨺����
    glLoadIdentity(); //�׵���ķ� �ʱ�ȭ
    glPushMatrix();
    gluLookAt(rightfocusX,rightfocusY,rightfocusZ,0.3,0.3,1.5, 0.0, 1.0, 0.0); //ī�޶��� ��ġ�������Ű�� ���� ������ �����Ű���ʰ�, ī�޶� ��ġ�� �����ε�.
    Draw(); //���� �׸��׸���
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    
    glutSwapBuffers(); //�������� �׸��� �׸������ؼ� swapbuffer�� �ٲ���.
}
//������ â�� ����Ǿ����� ��Ⱦ�� ��ġ��Ű�� viewport�� ũ�⵵ ��������ֱ����� reshape�ݹ� ���.
void MyReshape(int NewWidth, int NewHeight) {
   
    Width = NewWidth;
    Height = NewHeight;

    Widthfactor = (GLfloat)NewWidth / (GLfloat)800;
    Heightfactor = (GLfloat)NewHeight / (GLfloat)800;
    //��Ⱦ�� ����
}
//Ű���� �ݹ��� �̿��ؼ� ī�޶��� ��ġ�� ���������.
void MyKeyboard(unsigned char key, int x, int y) {
    if (key == 'l'||key=='L') {//ī�޶��� ��ġ�� ���� �̵��ؼ� ��������
        leftfocusX = 0.5;
        leftfocusY = 0.5;
    }
    if (key == 'k' || key == 'K') //ī�޶��� ��ġ�� ��������
    {
        leftfocusX = 0.0;
        leftfocusY = 0.0;
    }
    if (key == 'j' || key == 'J') { 
        leftfocusX = -0.3;
        leftfocusY = -0.3;
    }
    if (key == 'F'||key=='f') { 
        rightfocusX = -1.0;
        rightfocusZ = -2.0;

    }

    if (key == 'd' || key == 'D') { 
        rightfocusX = -1.0;
        rightfocusZ = -1.0;
    }

    if (key == 'g' || key == 'G') { 
        rightfocusX = 1.0, rightfocusZ = -2.0;
    }

    glutPostRedisplay();
}
//������ �ʱ�ȭ�� ������ �ʿ��� �Լ��� ȣ���Ͽ� �𵨸��Ҽ� �ִ� ȯ���� ����.
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("HW6 ������ȯ");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}