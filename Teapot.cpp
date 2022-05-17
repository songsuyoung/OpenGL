/***********************************************************************/
/*                   HW#5-1 : �� ������ ������ȯ                       */
/*  �ۼ��� : �ۼ���                         ��¥ : 2021�� 10�� 31��    */
/*                                                                     */
/* ���� ���� : DrawGround�Լ��� MyDisplay�Լ� ������ �𵨸��� �𵨵��� */
/* ������������ �����̴� ī�޶� �̿��ؼ� ��� ���ϴ��� ����� ����.*/
/* ��� : DrawGround�� �ٴ��� �׸��� �Լ���, ������ �ϳ��� ���� �׾� ��*/
/* ���� ����� ������ teapot�� �׸���(mydisplay�Լ�). �׸��� ����� ī */
/* �޶��� x,y,z�� special�ݹ��Լ����� �̵���Ű��, ī�޶��� pocus���� ��*/
/* ������ keyboard�ݹ��Լ����� ������������ �̵���ų �� �ִ�.          */
/***********************************************************************/
#include <gl/glut.h>
GLfloat cameraX = 0.0, cameraY = 3.5, cameraZ = 3.5; //ī�޶��� ��ġ�� �ű�� ���� ����� ����
GLfloat focusX = 0.0, focusY = 0.0, focusZ = 0.0; //ī�޶��� ������ �ű�� ���� ����� ����

void DrawGround() {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON); //�ٴ��� �簢���� �׸��� ���� ���Ǵ� �𵨸�.
    glVertex3f(-2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, -2.0);
    glVertex3f(-2.0, -0.71, -2.0);
    glEnd();

    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_LINES); //������ �𵨸��� �������� �𵨸��ϱ� ���� line
    for (float x = -2.0; x <= 2.2; x += 0.2) { //�𵨸��� ������ ����,�������� �߱����ؼ� ���Ǵ� for��
        glVertex3f(x, -0.7, -2.0); 
        glVertex3f(x, -0.7, 2.0); 
    }

    for (float z = -2.0; z <= 2.2; z += 0.2) {
        glVertex3f(-2.0, -0.7, z);
        glVertex3f(2.0, -0.7, z);
    }
    glEnd();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����ۿ� ���̹��۸� �ʱ�ȭ
    glMatrixMode(GL_MODELVIEW); //�𵨺����
    glLoadIdentity(); //�׵���ķ� �ʱ�ȭ

    gluLookAt(cameraX, cameraY, cameraZ, focusX, focusY, focusZ, 0.0,1.0,0.0); //���� ��ȯ �Լ��� �̿���, ���� ����� ��������.
    //������ ���������ν�, ������ ���� ����Ǹ� ī�޶��� ��ġ�� �������� �����Ҽ� �ֵ��� ����.
    DrawGround(); //�ٴ��� �׸��� �Լ�

    glColor3f(1.0, 1.0, 0.0); //��(���)
    glutWireTeapot(1.0); //�����ڸ� �׸�

    glutSwapBuffers(); //�������� �׸��� �׸������ؼ� swapbuffer�� �ٲ���.
}

//������ ���� �� ũ�⺯��ɶ� ������ ���� �ְ� �ذ� ����
void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLsizei)w / (GLsizei)h, 0.0, 100);
}

void MyKeyboard(unsigned char key, int x, int y) {

    //switch�� Ư���� break�� �������ʴ� �̻� ������ ������.
    //�� Ư���� �̿��ؼ� 'a'�� 'A'�� ���� ����� �� �� �ֵ��� �ߴ�.
    switch (key) {
    case 'a':
    case 'A':
        focusX += 0.1; //camera�� ���� x�� ��ǥ�� 0.1�� ����
        break;
    case 'f':
    case 'F':
        focusX -= 0.1; //camera�� ���� x�� ��ǥ�� 0.1�� ����
        break;
    case 'r':
    case 'R':
        focusY += 0.1;//camera�� ���� y�� ��ǥ�� 0.1�� ����
        break;
    case 'v':
    case 'V':
        focusY -= 0.1; //camera�� ���� y�� ��ǥ�� 0.1�� ����
        break;
    case 'z':
    case 'Z':
        focusZ += 0.1; //camera�� ���� z�� ��ǥ�� 0.1�� ����
        break;
    case 't':
    case 'T':
        focusZ -= 0.1; //camera�� ���� z�� ��ǥ�� 0.1�� ����
        break;
    }
    glutPostRedisplay();
}

//�����̼� Ű�� �����ԵǸ� ī�޶��� ��ǥ�� 0.1�� ������.
void MySpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        cameraY += 0.1; //ī�޶��� y�� ��ǥ 0.1�� ����
    }
    if (key == GLUT_KEY_DOWN) {
        cameraY -= 0.1; //ī�޶��� y�� ��ǥ 0.1�� ����
    }
    if (key == GLUT_KEY_RIGHT) {
        cameraX += 0.1; //ī�޶��� x����ǥ 0.1 ����
    }
    if (key == GLUT_KEY_LEFT) {
        cameraX -= 0.1; //ī�޶� x����ǥ 0.1 ����
    }
    glutPostRedisplay(); //display�ݹ��Լ� ����ȣ��
}

//������ �ʱ�ȭ�� ������ �ʿ��� �Լ��� ȣ���Ͽ� �𵨸��Ҽ� �ִ� ȯ���� ����.
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Hw#5 �� ������ ������ȯ");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
    return 0;
}

