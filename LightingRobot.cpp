/***********************************************************************/
/*                         HW#7 : 로봇 조명		                       */
/*  작성자 : 송수영                          날짜 : 2021년 11월 22일   */
/*                                                                     */
/* 문제 정의 : HW#4에서 정의한 로봇을 이용하여 조명을 넣고 달리는 모습 */
/* 을 구현함									                       */
/* 기능 : init에서 조명을 enable 및 적합값을 줌으로써 조명을 조절하고, */
/* 또한, 키보드콜백에서 r과 R을 누르면 Timer콜백을 이용하여, sin을 이용*/
/* 해 값을 변경시켜 로봇이 달리 도록 표현 했다.						   */
/***********************************************************************/

#include <Gl/glut.h>
#include <stdlib.h>
#include <math.h>

GLfloat pocusX = 0.0, pocusY = 0.0, pocusZ = 90.0; //z축은 glu특성상 미리 돌려놓음
static double time = 0; //로봇의 팔다리를 자연스럽게 움직이기 위해 선언한 time변수
static GLint Right = 0,Left=0; //오른 종아리부분과 왼쪽 종아리 부분을 표현하기 위함.

static float init = 90, LeftLeg = 0, RightLeg = 0, Neck = 0, Head = 0, Leftshoulder = 0, Leftelbow = 0, Rightshoulder = 0, Rightelbow = 0;
//위에 선언된 변수들은 초기 각도,왼쪽다리,오른쪽다리,목,머리,왼쪽어깨,왼쪽팔,오른쪽어깨,오른쪽팔의 각 각도를 의미함
//초기 각도가 필요한 이유는 glu를 모델링할 경우, 90도를 돌리지않으면 정면이 위에서 바라보는 듯한 모양이였기때문에 일부로, 90도씩 회전시켜서
//각 모델들을 모델링했음.
GLUquadricObj* qobj = gluNewQuadric();
//많은 primitive들 중 로봇을 모델링하기 위해 원기둥이 해당되는 glu를 이용하였다.

//목과 머리를 모델링하는 함수이다. 사람의 몸은 머리만 움직이는 구조가아닌, 목이 움직이면서, 머리가 더앞으로 가는 구조이기 때문에 둘을 계층적으로
//묶어서 모델링하게 되었다.
void drawNeckAndHead() {

	//목을 모델링. 이전에서 스택을 pop했기때문에, 목에 대해 90도 돌리고 모델링을 시작함.
	glTranslatef(0.0, 0.8, -1.0);
	glRotatef((GLfloat)Neck + 90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.8, 0.0);
	glPushMatrix();	// 목을 그리는데 필요한 변환 스택에 삽입
	glScalef(1.0, 1.0, 2.0);
	gluCylinder(qobj, 0.5, 0.5, 0.5, 20, 8); //목을 모델링
	glPopMatrix(); //목의 크기를 키운것만 팝하게 되면, 머리와 계층적인 모델링이 가능함.

	//머리
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef((GLfloat)Head, 1.0, 0.0, 0.0); //머리는 목과 계층적임, 목이 약간 움직이고 (목 5도 머리 10도) 머리는 15도 정도까지 이동후 원자리로 돌아감
	glScalef(1.0, 1.0, 1.0); //크기를 1키움
	gluSphere(qobj, 1.2, 50, 50);

	glPopMatrix();

}

//왼쪽 어깨-팔을 모델링하는 함수이다. 저의 의도는 팔을 허리에 굽히고 있는 상태에서, 어깨는 움직이지않고 팔만 폈다 다시 접어 허리에 손이 가있는 상태를
//만들고 싶었다. 그래서 어깨와 팔을 모델링을 했지만 실제로 움직이는 아래팔만 해당한다.
void drawLeftArm() {

	glTranslatef(-1.0, 0.0, 0.0);	 //어깨를 모델링하기 위해 이동 
	glRotatef((GLfloat)Leftshoulder + 90, 1.0, 0.0, -0.5); // 90도 회전하는데, z축으로 회전시킨이유는 사선의 팔을 만들기 위해서
	glPushMatrix();	// 계층적 모델링을 위해서 어깨를 스택에 삽입
	glScalef(0.5, 0.5, 1.5);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8); //어깨 모델링

	glPopMatrix(); //크기를 스택에서 팝하고, 어깨 모델링으로 돌아옴

	glTranslatef(0.0, 0.0, 3.0);
	glRotatef((GLfloat)Leftelbow -60 , 1.0, 0.0,0.0); //현재 어깨의 경우 90도이기때문에 Leftelbow는 0이더라도, 90도 미리 회전된상태, 손이 허리에 가있는 상태로
	//만들기 위해서 -120도를 해준다. (왜냐하면 왼쪽 모델링이기때문에 -값으로 되어야한다.
	glScalef(0.5, 0.5, 1.0);
	gluCylinder(qobj, 1.0, 1.0, 1.0, 20, 8); //팔 모델링

	glTranslatef(0.0, 0.0, 1.5);
	glScalef(1.0, 0.5, 0.5);
	gluSphere(qobj, 1.0, 50, 50); // 손 모델링

	glPopMatrix();

}

//오른쪽 어깨-팔을 모델링하는 함수이다. 위의 의도와 마찬가지로 손이 허리를 짚고 있는 상태에서, 폈다가, 다시 허리를 짚고있는 자세로 돌아가는 움직임을 가지도록
//모델링했다.
void drawRightArm() {

	glTranslatef(1.0, 0.0, 0.0);	 // 오른쪽 어깨가 그려지는 곳으로 이동
	glRotatef((GLfloat)Rightshoulder + 90, 1.0, 0.0,0.5); // glu특성상으로 90도 돌리는데, 어깨는 움직이지않고 팔만 허리에 손이 있다가 피고, 다시 돌아가는걸
	//표현하기 위해서 z도 회전, 이 경우 z축이 +여야함.(좌측 회전)
	glPushMatrix();	// 계층적 모델링을 위해서 스택에 삽입
	glScalef(0.5, 0.5, 1.5);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8); //어깨 그리기

	glPopMatrix(); //크기를 팝한후, 어깨의 TR로 돌아감.

	glTranslatef(0.0, 0.0, 3.0); //이동후
	glRotatef((GLfloat)Rightelbow-90, 1.0, 0.0,0.0);
	glScalef(0.5, 0.5, 1.0); //크기 키우고
	gluCylinder(qobj, 1.0, 1.0, 1.0, 20, 8); //아래 팔을 그림/

	glTranslatef(0.0, 0.0, 1.5);
	glScalef(1.0, 0.5, 0.5);
	gluSphere(qobj, 1.0, 50, 50); //손을 모델링.
	glPopMatrix(); //현재 그린 아래팔을 팝해서, 밑에 필요한 계층적모델링에 영향을 주지않도록함.

}

//몸통,두 다리를 모델링하고, 위에서 모델링하는데 사용하는 함수들을 호출해 실제 그림을 그리는 콜백함수이다.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //항등행렬로 초기화
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, pocusX, pocusY, pocusZ, 0.0, 1.0, 0.0); //항등행렬로 초기화한 후, gluLookAt을 설정
	//이렇게 함으로써 카메라 위치를 설정. 변수를 둠으로써, 변수값은 변경하여 시점을 마음대로 이동할 수 있게함.
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glPushMatrix();
	//몸통의 경우, 이동을 하지않기 때문에 계층적인 모델링에서 제외해야할것같아서 스택에 삽입하지않았다. 

	glColor3f(0.2, 0.3, 0.5);

	glTranslatef(0.0, 0.0, 0.0);	 // Pivot 지정 및 객체 이동

	glRotatef((GLfloat)init, 1.0, 0.0, 0.0); // glu의 경우 90도 가량을 회전시켜줘야지 현재 제가 모델링한 모습을 볼수있다.
	glTranslatef(0.0, 0.0, 0.0);	 // Pivot 지정 및 객체 이동
	gluQuadricDrawStyle(qobj, GLU_FILL);
	glScalef(3.0, 3.0, 3.0);
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8);
	glPopMatrix(); //스택에 삽입되지는 않았지만, TRS는 자동적으로 쌓이기때문에 자동적으로 쌓인 부분을 pop해준다

	glPushMatrix(); //스택에 다시 항등행렬을 삽입해준다. 이 이후부터는 계층적인 모델링을 사용하기 때문에 또 삽입을 했다.
	//왼쪽 다리완성

	glTranslatef(0.0, 0.0, 0.0);	 // 다리가 위치할 곳에 이동을하고
	glRotatef((GLfloat)LeftLeg + 90, 1.0, 0.0, 0.0); //위에서 몸통을 스택에 넣지않았기때문에 glu의 특성상 90도를 돌려준채 사용해야해서 90을 더해줬다.
	glTranslatef(-0.7, 0.0, 4.0);	// 위치를 이동한후
	glScalef(1.0, 1.0, 1.5); //크기를 키우고
	//glRotatef((GLfloat)Left, 1.0, 0.0, 0.0); //위에서 몸통을 스택에 넣지않았기때문에 glu의 특성상 90도를 돌려준채 사용해야해서 90을 더해줬다.
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //실제 무릎밑을 모델링한다.
	
	//무릎 밑 다리 모델링 
	glTranslatef(0.0, 0.0, 1.0);
	glRotatef((GLfloat)Left, 1.0, 0.0, 0.0); //위에서 몸통을 스택에 넣지않았기때문에 glu의 특성상 90도를 돌려준채 사용해야해서 90을 더해줬다.
	glScalef(1.0, 1.0, 1.0); //크기를 키우고
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //오른무릎 모델링 후

	glTranslatef(0.0, 0.0, 1.5); //밑으로 더 내려가는데 , z축을 늘리는 이유가 glRotate에서 y축과 z축의 방향이 바뀌었기때문이다.
	gluCylinder(qobj, 0.3, 0.5, 0.5, 20, 8);  //발을 모델링해준다.
	glPopMatrix(); //현재 계층적으로 모델링한 다리를 팝해줌으로써 밑에 영향이 가지않도록 한다.


	//오른쪽다리
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);	 // 오른쪽 다리도 마찬가지로 왼쪽다리와 비슷한데, 왼쪽다리에 +0.3한만큼 이동시켜 주면 둘의 사이간격이 딱적당하다.
	glRotatef((GLfloat)RightLeg + 90, 1.0, 0.0, 0.0); // 위와 마찬가지로 glu특성상 90을 더했다.
	glTranslatef(0.7, 0.0, 4.0);
	glScalef(1.0, 1.0, 1.5); //크기를 키우고
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //오른무릎 모델링 후
	
	glTranslatef(0.0, 0.0, 1.0);
	glRotatef((GLfloat)Right, 1.0, 0.0, 0.0); //위에서 몸통을 스택에 넣지않았기때문에 glu의 특성상 90도를 돌려준채 사용해야해서 90을 더해줬다.
	glScalef(1.0, 1.0, 1.0); //크기를 키우고
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //오른무릎 모델링 후

	glTranslatef(0.0, 0.0, 1.5); // 밑으로 내려가
	gluCylinder(qobj, 0.3, 0.5, 0.5, 20, 8); //오른발을 모델링.
	glPopMatrix(); //오른다리를 계층적으로 모델링한 스택을 팝.


	//목 머리
	glPushMatrix();
	drawNeckAndHead();

	gluQuadricDrawStyle(qobj, GLU_FILL);

	glPushMatrix();
	//왼쪽팔 그리기
	gluQuadricDrawStyle(qobj, GLU_FILL);

	drawLeftArm();
	//오른팔 그리기
	glPushMatrix();
	drawRightArm();

	glutSwapBuffers();
}

//실제 자동적으로 달리기를 표현할 콜백함수
void MyTimer(int element) {
	time = time + 0.1047;//시간 증가변수.
	
	Leftshoulder = sin(time) * 40;//왼팔은 40도 각도로.
	Rightshoulder = -Leftshoulder;//오른팔은 왼팔 반대로 20도 각도.

	LeftLeg = -sin(time) * 20;//왼다리는 오른팔과 같은 각도로. (sin으로 시간 증가 변수 줌으로써 이동하는 모습을 표현
	RightLeg = -LeftLeg;//오른다리는 왼팔과 같은 각도로.

	Left = fabs(LeftLeg / 0.5f); //왼무릎의 다리 각도를 0.5f로 나눈 절대각도로, 다리를 접혀서 달리기를 표현
	Right = fabs(RightLeg / 0.5f);//오른무릎의 다리 각도를 0.5f로 나눈 절대각도로, 다리를 접혀서 달리기를 표현

	glutPostRedisplay();
	glutTimerFunc(30, MyTimer, 1); //timer는 한번만 호출하기 때문에, 자연스러운 움직임을 표현하기 위해서 반복적 호출을 해줌
}

//양 팔과 양다리를 달리는 형식으로 표현하기 위해 사용되는 키보드콜백
void MyKeyboard(unsigned char key, int x, int y) {

	if (key == 'r'|| key=='R') {//s키를 누를경우 stop이 true가 되면서 움직임이 멈춤
		glutTimerFunc(30, MyTimer, 1); //timer는 한번만 호출하기 때문에, 자연스러운 움직임을 표현하기 위해서 반복적 호출을 해줌
	}
	glutPostRedisplay();
}

//init함수 내부에서 조명을 초기화함으로써 조명 표현함.
void MyInit(void) {
	glEnable(GL_DEPTH_TEST); //깊이를 enable시킴
	glEnable(GL_NORMALIZE); //법선벡터를 외적으로
	glEnable(GL_LIGHTING); //조명사용

	//조명에 사용될 변수들 선언
	GLfloat ambientLight[] = { 0.3f,0.3f,0.3f,1.0f };
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat position[] = { 400.0f,300.0f,700.0f,1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //주변광을 나타내는 조명으로,
	//전체적인 분위기를 만들어 내며 단일 지점에 균등하게 광원 방출을 위함.
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	//발산광으로 특정 방향과 위치로
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular); 
	//반사광으로, 오브젝트의 표면을 더 밝도록
	glLightfv(GL_LIGHT0, GL_POSITION, position); //광원의 위치 설정
	glEnable(GL_LIGHT0); //조명 0번을 enable시킨다.

	glEnable(GL_COLOR_MATERIAL); //색깔 질감 enable
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//앞면에 재질 설정
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//반사광 설정
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	//광택 설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}

//윈도우 창이 변경되어도 똑같은 그림을 유지하기 위해서 사용.
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
	glutCreateWindow("7장 Robot 조명");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}