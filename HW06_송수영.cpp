/****************************************************************/
/*                      HW#6 : glViewPort                       */
/*  작성자 : 송수영                      날짜 : 2021년 11월 09일*/
/*                                                              */
/* 문제 정의 : 오른쪽 위 viewport의 키보드 좌표(g,d,f) 왼쪽 아래*/
/* viewport의 키보드 좌표(l,j,k) 로 세개의 키보드 좌표를 이용해서*/
/*  카메라의 위치를 이동시켜 그려진 모델링의 여러모습을 볼 수 있다.*/    
/* 기능 : Draw함수에서 teapot과 torus 2개를 그리고, 색을 변경시킴*/
/* MyReshape를 이용해서 윈도우가 바뀜에 따라 viewport를 변경시키고*/
/* glOrtho의 종횡비와 gluPerspective의 종횡비를 일치시켜 크기가 변*/
/* 경되더라도 왜곡현상이 생기지 않도록했다. 또한, display콜백을 이용*/
/* 해 그림을 그리고 키보드 콜백을 이용해서 시점은 고정시키고 */
/*  카메라의 위치를 이동시켰다.*/    
/****************************************************************/

#include <gl/glut.h>

GLfloat leftfocusX = 0.0, leftfocusY = 0.0, leftfocusZ = 0.0;
//glOrtho의 focus이동을 위함
GLfloat rightfocusX = 1.0, rightfocusY = -1.0, rightfocusZ = -2.0;
//gluPerspective의 카메라 위치를 이동시키기 위함.
GLint Width = 800, Height = 800; //현재 화면크기
GLfloat Widthfactor = (GLfloat)Width / (GLfloat)800, Heightfactor = (GLfloat)Height / (GLfloat)800; //현재종횡비

//실제 모델링함, push/pop을 이용해 계층형을 유지함.
void Draw() {
    //복합변환을 해서 하나의 화면에 여러개의 그림이 있도록 함.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //색(노란)
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(0.0, 0.0, 1.5);
    glutWireTeapot(1.0); //주전자를 그림
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); //색(빨간색)
    glTranslatef(0, 0.5, 0);
    glRotatef(-45, 0, 1, 0);
    glScalef(0.1, 0.1, 0.1);
    glRotatef(45, 0, 1, 0);
    glutWireTorus(0.5, 1.0, 60, 60); //torus를 그림
    glPopMatrix();

    //복합변환 진행.
    glPushMatrix();
    glColor3f(1.0, 0.0, 1.0); //자주색
    glTranslatef(0.5, -0.5, 0.5);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(60, 1, 0, 0);
    glutWireTorus(0.5, 1.0, 60, 60); //torus를 그림
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //색버퍼와 깊이버퍼를 초기화
    
    glViewport(0, 0, Width / 2, Height / 2); //하나의 윈도우에 4개의 뷰포트를 둠. 하지만 왼쪽하단과 오른쪽상단만 이용할 것
    glMatrixMode(GL_PROJECTION); //glOrtho를 하기위함.
    glLoadIdentity();
    glOrtho(-1.0 * Widthfactor, 1.0 * Widthfactor, -1.0 * Heightfactor, 1.0 * Heightfactor, -1.0, 1.0);  //좌하단은 glOrtho를 이용해서 모델을 봄
 
    glMatrixMode(GL_MODELVIEW); //모델뷰행렬
    glLoadIdentity(); //항등행렬로 초기화
    glPushMatrix();
    gluLookAt(leftfocusX, leftfocusY, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    gluLookAt(leftfocusX, leftfocusY, leftfocusZ, 0.3,0.3,1.5, 0.0, 1.0, 0.0); //카메라의 위치를 키보드입력에따라 바꾸기 위해서 변수로 설정.
    Draw(); //실제그림을 그림
    glPopMatrix(); //현재 
    
    glViewport(Width/2, Height/2, Width / 2, Height / 2);//오른쪽 상단에 viewport를 나눠서 사용.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1.0f*Widthfactor/Heightfactor,1,1000); //gluPerspective를 이용해서 원근투영행렬로 해줌

    glMatrixMode(GL_MODELVIEW); //모델뷰행렬
    glLoadIdentity(); //항등행렬로 초기화
    glPushMatrix();
    gluLookAt(rightfocusX,rightfocusY,rightfocusZ,0.3,0.3,1.5, 0.0, 1.0, 0.0); //카메라의 위치를변경시키기 위해 시점은 변경시키지않고, 카메라 위치만 변수로둠.
    Draw(); //실제 그림그리기
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    
    glutSwapBuffers(); //연속적인 그림을 그리기위해서 swapbuffer로 바꿔줌.
}
//윈도우 창이 변경되었을때 종횡비를 일치시키고 viewport의 크기도 변경시켜주기위해 reshape콜백 사용.
void MyReshape(int NewWidth, int NewHeight) {
   
    Width = NewWidth;
    Height = NewHeight;

    Widthfactor = (GLfloat)NewWidth / (GLfloat)800;
    Heightfactor = (GLfloat)NewHeight / (GLfloat)800;
    //종횡비 변경
}
//키보드 콜백을 이용해서 카메라의 위치를 변경시켜줌.
void MyKeyboard(unsigned char key, int x, int y) {
    if (key == 'l'||key=='L') {//카메라의 위치를 위로 이동해서 내려보기
        leftfocusX = 0.5;
        leftfocusY = 0.5;
    }
    if (key == 'k' || key == 'K') //카메라의 위치를 원점으로
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
//윈도우 초기화및 생성에 필요한 함수를 호출하여 모델링할수 있는 환경을 만듬.
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("HW6 시점변환");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}