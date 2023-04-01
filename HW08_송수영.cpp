/***********************************************************************/
/*                    HW#8 :밤에 혼자달리는 차                         */
/*  작성자 : 송수영                             날짜 : 2021년 12월 08일*/
/*                                                                     */
/* 문제 정의 : 어둠밖에 없는 세상에서 차량 한대가 지나가는 모습을 모델*/
/* 링했다. 건물과 자동차 좌표를 전부 손수 생각했고, 텍스처매핑을 이용*/
/* 해 실제 건물과 아스팔트를 표현하였다.*/      
/* 기능 : 키보드 우측 좌측을 이용해 자동차를 움직일수 있다. 키보드 콜백을*/
/*이용해서 화면 이동을 할 수 있다.전역 조명을 설치하였다.*/
/***********************************************************************/

#include <gl/glut.h>
#include <stdio.h>

GLfloat Movex =10.0;//자동차를 우측 왼측으로 이동하도록함
GLfloat Movey = 0.0;
GLfloat Movez = 0.0;
bool State = false;
GLfloat xAngle=0, yAngle=0, zAngle=-1; //카메라 돌리는데 이용할 예정
GLfloat carAngle = 0; //카메라에 맞춰 자동차를 변경
GLfloat carX, carY, carZ = 0;//카메라에 맞춰 자동차 

//자동차 모델링을 위한 함수 오른쪽 창문 
void DrawRightSide() {

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
    //자동차 모델링 예정 윗부분 (창문부터 자동차윗부분)
    glVertex3f(-0.5, 0.3, 0.5);
    glVertex3f(0.5, 0.3, 0.5);
    glVertex3f(0.4, 0.5, 0.5);
    glVertex3f(-0.4, 0.5, 0.5);
    glEnd();
    //창문부터 자동차 아래부분까지

    glBegin(GL_POLYGON);
    glVertex3f(-0.8, -0.3, 0.5);
    //바퀴를 넣기 위해서 부분제거
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

//자동차 모델링 왼쪽 창문
void DrawLeftSide() {

    glBegin(GL_POLYGON);
    //자동차 모델링 예정 윗부분 (창문부터 자동차윗부분)
    glVertex3f(-0.5, 0.3, -0.2);
    glVertex3f(-0.4, 0.5, -0.2);
    glVertex3f(0.4, 0.5, -0.2);
    glVertex3f(0.5, 0.3, -0.2);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-0.8, -0.3, -0.2);
    //바퀴를 넣기 위해서 부분제거
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

//자동차 천장 모델링
void DrawCeiling() {
    glBegin(GL_POLYGON);
    glVertex3f(-0.4,0.5,0.5);
    glVertex3f(0.4, 0.5, 0.5);
    glVertex3f(0.4, 0.5, -0.2);
    glVertex3f(-0.4, 0.5, -0.2);
    glEnd();
}
//자동차 앞문 모델링
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
//자동차 앞 모델링
void DrawFront() {
    glBegin(GL_POLYGON);
    glVertex3f(-0.8, 0.1, -0.2);
    glVertex3f(-0.8, 0.1, 0.5);
    glVertex3f(-0.5, 0.3, 0.5);
    glVertex3f(-0.5, 0.3, -0.2);
    glEnd();

}
//앞범퍼 모델링
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
//뒷창문 모델링
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
//뒤 번호판 부분 모델링
void DrawBack() {
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.3, -0.2);
    glVertex3f(0.5, 0.3, 0.5);
    glVertex3f(0.7, 0.3, 0.5);
    glVertex3f(0.7, 0.3, -0.2);
    glEnd();
}
//뒷범퍼 모델링
void DrawBackbumper() {
    glBegin(GL_POLYGON);
    glVertex3f(0.7, -0.3, 0.5);
    glVertex3f(0.7, 0.3, 0.5);
    glVertex3f(0.7, 0.3, -0.2);
    glVertex3f(0.7, -0.3, -0.2);
    glEnd();

}
//바퀴 모델링
void DrawWheel() {
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.2, 0.3, 30, 50);
}
//건물 모델링 텍스트 매칭
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

//시맨트 바닥 모델링 - 택스트 매핑해서 도로처럼 만들기
void DrawGround() {
   
    glBegin(GL_POLYGON);
    glVertex3f(-40.0, -3, 11.0);
    glVertex3f(40.0, -3, 11.0);
    glVertex3f(40.0, -3, 5.0);
    glVertex3f(-40.0, -3, 5.0);
    glEnd();

}
//가로등을 만들기 위해서 glu 이용
GLUquadricObj* qobj = gluNewQuadric();

//가로등 모델링
void DrawStreetlight() {

    glPushMatrix();
    glTranslatef(5, -0.5, 1);
    glRotatef(90, 1.0, 0, 0);
    gluCylinder(qobj, 0.2, 0.2, 7.0, 50, 8); //가로등 봉
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 1.0, 0, 0);
    glTranslatef(5.0, 2.0, -0.5);
  
    glScalef(0.3, 0.6, 0.3);
    glutSolidTorus(0.3, 1.5, 20, 20); //torus와 cone을 합쳐서 가로등 머리를 표현함.
    glScalef(6, 6, 8);
    glRotatef(180, 1.0, 0, 0);
    glutSolidCone(0.3,0.5, 12, 12);


    
    glPopMatrix();
  
}
void MyDisplay() {

    glMatrixMode(GL_PROJECTION); //glOrtho를 하기위함.
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -20.0, 20.0); //직교투영

    
    glMatrixMode(GL_MODELVIEW); //항등행렬로 초기화
    glLoadIdentity();
    //이렇게 함으로써 카메라 위치를 설정. 변수를 둠으로써, 변수값은 변경하여 시점을 마음대로 이동할 수 있게함.
    gluLookAt(0.0, 10.0, 5.0, xAngle, yAngle, zAngle, 0, 1, 0); //이벤트 처리를 통해 카메라의 위치를 이동시킬 수 있다.

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //그린 그림 모두 초기화 후 다시 그림

    Drawbuilding(); //건물모델링
    DrawGround(); //땅 모델링
    DrawStreetlight(); //가로등 모델링
    //자동차를 세상좌표계로 가져오는 과정을 모델링
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

    glutSwapBuffers(); //연속적인 그림을 그리기위해서 swapbuffer로 바꿔줌.
}
void MyInit(void) {

    GLfloat global_ambient[] = { 0.3, 0.3, 0.3, 1.0 };	//전역 주변반사

    GLfloat Light0_Ambient[] = { 0.3, 0.3, 0.3, 1.0 };	//0번 광원 특성
    GLfloat Light0_Diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat Light0_Specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat Light1_Ambient[] = { 0.3, 0.3, 0.3, 1.0 };	//1번 광원 특성
    GLfloat Light1_Diffuse[] = { 0.3, 0.3, 0.3, 0.3 };
    GLfloat Light1_Specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat Light0_Position[] = { 5.0, 10.0, 5.0, 1.0 };	//0번 광원위치
    GLfloat Light0_Direction[] = { 0.5, 0.5, 0.5 };		//0번 광원 방향
    GLfloat Light0_Cutoff[] = { 90.0 };					//0번 광원 각도

    GLfloat Light1_Position[] = { 0.0, 0.0, 1.0, 1.0 };	//1번 광원위치

    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0_Ambient);	//0번 광원 특성할당
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0_Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Light0_Specular);

    glLightfv(GL_LIGHT1, GL_AMBIENT, Light1_Ambient);	//1번 광원 특성할당
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1_Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Light1_Specular);

    glLightfv(GL_LIGHT0, GL_POSITION, Light0_Position);	//스포트라이트
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light0_Direction);	//방향
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, Light0_Cutoff);	//각도
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);			//코사인 승수

    GLfloat material_ambient[] = { 0.0, 0.0, 0.0, 1.0 };	//물체 특성
    GLfloat material_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat material_shininess[] = { 127.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);//물체 특성할당
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);//전역주변반사 
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //근접시점


    glShadeModel(GL_SMOOTH);	//구로 셰이딩
    glEnable(GL_DEPTH_TEST);	//깊이 버퍼 활성화
    glEnable(GL_LIGHTING);		//조명 활성화
    glEnable(GL_LIGHT0);		//0번 광원 활성화
    glEnable(GL_LIGHT1);		//1번 광원 활성화
    glEnable(GL_COLOR_MATERIAL);
}

//k와 l을 누르면, 시점을 이동시켜 다양한 시각에서 자동차가 움직이는 것을 볼수있음
void MyKeyboard(unsigned char key, int x, int y) {
    if (key == 'l' || key == 'L') {//카메라의 위치를 위로 이동해서 내려보기
        if (xAngle < 5) {
            xAngle += 1;
        }//xAngle을 이동시킴
    }
   
    if (key == 'k' || key == 'K')
    {
        if (yAngle < 5)
            yAngle += 1;
    }//yAngle을 이동시킴

    //원래 시점으로 돌아감
    if (key == 'j' || key == 'J')
    {
        xAngle = 0;
        yAngle = 0;
    }
     glutPostRedisplay();
}
//키보드를 누를경우 자동차가 움직이고 한바퀴를 돌고 다시 화면에 등장
void MySpecial(int key, int x, int y) {

    if (!State) {

        if (key == GLUT_KEY_RIGHT) {
            if (Movex < 20.0) //뷰포트를 넘어가면 다시 들어오도록 설정하기 위함
                Movex += 1;
            else
                Movex = -20; //맨끝 -20부터시작
        }
        if (key == GLUT_KEY_LEFT) {
            if (Movex > -20.0) //뷰포트를 넘어가면 다시 돌아오도록 설정하기 위함
                Movex -= 1;
            else
                Movex = 20; //맨끝, 20부터 시작
        }
    }
    glutPostRedisplay();
}
//왜곡현상이 발생하지 않도록함
void MyReshape(int NewWidth,int NewHeight) {
    glViewport(0, 0, NewWidth, NewHeight);
    GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)600; //화면의 크기가 가로세로 600이기때문에
    GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)600;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(10.0 * Widthfactor, -10.0 * Widthfactor, 10.0 * Heightfactor, -10.0 * Heightfactor, -20.0, 20.0); //왜골 발생시 직교투영을 다시해서 종횡비를 맞춰줌
}
//모든 모델링을 시계방향으로 모델링했고, 보이지않는 곳은 삭제함.
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