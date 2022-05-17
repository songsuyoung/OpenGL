/***********************************************************************/
/*                   HW#5-1 : 차 주전자 시점변환                       */
/*  작성자 : 송수영                         날짜 : 2021년 10월 31일    */
/*                                                                     */
/* 문제 정의 : DrawGround함수와 MyDisplay함수 내에서 모델링한 모델들을 */
/* 여러방향으로 움직이는 카메라를 이용해서 어떻게 변하는지 모습을 본다.*/
/* 기능 : DrawGround는 바닥을 그리는 함수로, 폴리곤 하나에 줄을 그어 바*/
/* 닥을 만들고 그위에 teapot을 그린다(mydisplay함수). 그리고 선언된 카 */
/* 메라의 x,y,z를 special콜백함수에서 이동시키고, 카메라의 pocus관련 변*/
/* 수들을 keyboard콜백함수에서 여러방향으로 이동시킬 수 있다.          */
/***********************************************************************/
#include <gl/glut.h>
GLfloat cameraX = 0.0, cameraY = 3.5, cameraZ = 3.5; //카메라의 위치를 옮기기 위해 선언된 변수
GLfloat focusX = 0.0, focusY = 0.0, focusZ = 0.0; //카메라의 초점을 옮기기 위해 선언된 변수

void DrawGround() {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON); //바닥의 사각형을 그리기 위해 사용되는 모델링.
    glVertex3f(-2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, -2.0);
    glVertex3f(-2.0, -0.71, -2.0);
    glEnd();

    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_LINES); //가로줄 모델링과 세로줄을 모델링하기 위한 line
    for (float x = -2.0; x <= 2.2; x += 0.2) { //모델링에 일정한 가로,세로줄을 긋기위해서 사용되는 for문
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //색버퍼와 깊이버퍼를 초기화
    glMatrixMode(GL_MODELVIEW); //모델뷰행렬
    glLoadIdentity(); //항등행렬로 초기화

    gluLookAt(cameraX, cameraY, cameraZ, focusX, focusY, focusZ, 0.0,1.0,0.0); //시점 변환 함수를 이용해, 시점 행렬을 삽입해줌.
    //변수로 선언함으로써, 변수의 값이 변경되면 카메라의 위치값 초점값을 변경할수 있도록 만듬.
    DrawGround(); //바닥을 그리는 함수

    glColor3f(1.0, 1.0, 0.0); //색(노란)
    glutWireTeapot(1.0); //주전자를 그림

    glutSwapBuffers(); //연속적인 그림을 그리기위해서 swapbuffer로 바꿔줌.
}

//윈도우 생성 및 크기변경될때 비율을 맞춰 왜곡 해결 선언
void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLsizei)w / (GLsizei)h, 0.0, 100);
}

void MyKeyboard(unsigned char key, int x, int y) {

    //switch문 특성상 break를 만나지않는 이상 밑으로 내려감.
    //그 특성을 이용해서 'a'와 'A'는 같은 기능을 할 수 있도록 했다.
    switch (key) {
    case 'a':
    case 'A':
        focusX += 0.1; //camera의 초점 x축 좌표가 0.1씩 증가
        break;
    case 'f':
    case 'F':
        focusX -= 0.1; //camera의 초점 x축 좌표가 0.1씩 감소
        break;
    case 'r':
    case 'R':
        focusY += 0.1;//camera의 초점 y축 좌표가 0.1씩 증가
        break;
    case 'v':
    case 'V':
        focusY -= 0.1; //camera의 초점 y축 좌표가 0.1씩 감소
        break;
    case 'z':
    case 'Z':
        focusZ += 0.1; //camera의 초점 z축 좌표가 0.1씩 증가
        break;
    case 't':
    case 'T':
        focusZ -= 0.1; //camera의 초점 z축 좌표가 0.1씩 감소
        break;
    }
    glutPostRedisplay();
}

//스페이셜 키를 누르게되면 카메라의 좌표가 0.1씩 증가함.
void MySpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        cameraY += 0.1; //카메라의 y축 좌표 0.1씩 증가
    }
    if (key == GLUT_KEY_DOWN) {
        cameraY -= 0.1; //카메라의 y축 좌표 0.1씩 감소
    }
    if (key == GLUT_KEY_RIGHT) {
        cameraX += 0.1; //카메라의 x축좌표 0.1 증가
    }
    if (key == GLUT_KEY_LEFT) {
        cameraX -= 0.1; //카메라 x축좌표 0.1 감소
    }
    glutPostRedisplay(); //display콜백함수 강제호출
}

//윈도우 초기화및 생성에 필요한 함수를 호출하여 모델링할수 있는 환경을 만듬.
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Hw#5 차 주전자 시점변환");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
    return 0;
}

