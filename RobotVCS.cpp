/****************************************************************/
/*                      HW#5-2 : RobotVCS                       */
/*  작성자 : 송수영                      날짜 : 2021년 11월 02일*/
/*                                                              */
/* 문제 정의 : HW#4에서 정의한 로봇을 사용하여 시점이 바뀔때마다*/
/* 어떤 형태를 유지하는지 확인해 본다.			                */
/* 기능 : HW#4 기능에다가 special callback함수와 새로운 timer ca*/
/* ll함수를 둠으로써 기능을 추가하였다.						    */
/* 'end'를 누를 시 원래 시점으로 전환, '→'을 누를시 (오른쪽)옆으*/
/* 로 시점전환, '←'을 누를시 (왼쪽)옆으로 시점전환, '↑'을 누를*/
/* 시 위로 시점전환, '↓'를 누를지 아래로 시점전환              */
/****************************************************************/

#include <Gl/glut.h>

//카메라의 시점을 변경하기 위함
GLfloat pocusX = 0.0, pocusY = 0.0, pocusZ = 90.0; //z축은 glu특성상 미리 돌려놓음
bool LeftControl = false,RightControl=false,UpControl=false,DownControl=false,InitControl=true;
static int init = 90, LeftLeg = 0, RightLeg = 0, Neck = 0, Head = 0, Leftshoulder = 0, Leftelbow = 0, Rightshoulder = 0, Rightelbow = 0;
//위에 선언된 변수들은 초기 각도,왼쪽다리,오른쪽다리,목,머리,왼쪽어깨,왼쪽팔,오른쪽어깨,오른쪽팔의 각 각도를 의미함
//초기 각도가 필요한 이유는 glu를 모델링할 경우, 90도를 돌리지않으면 정면이 위에서 바라보는 듯한 모양이였기때문에 일부로, 90도씩 회전시켜서
//각 모델들을 모델링했음.
static bool LeftLeg_Control = false, RightLeg_Control = false, Head_Control = false, RightArm_Control = false, LeftArm_Control = false;
//각 몸들을 제어하기위한 bool변수로, true가되었을때 이동하도록 함.
bool stop = false;
//stop이 true가 될경우, 모든 움직임이 stop되어야한다.
int op = -1;
//옵션의 경우 선택되는 오른쪽,왼쪽이 선택되는지 정확한 구분을 위해서 사용한 변수였다. 부울 변수만으로는 같이 움직일수도 있기때문에 정확한 변수값을
//선언해서 사용했다.
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
	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.0, 1.0, 2.0);
	gluCylinder(qobj, 0.5, 0.5, 0.5, 20, 8); //목을 모델링
	glPopMatrix(); //목의 크기를 키운것만 팝하게 되면, 머리와 계층적인 모델링이 가능함.

	//머리
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef((GLfloat)Head, 1.0, 0.0, 0.0); //머리는 목과 계층적임, 목이 약간 움직이고 (목 5도 머리 10도) 머리는 15도 정도까지 이동후 원자리로 돌아감
	glScalef(1.0, 1.0, 1.0); //크기를 1키움
	gluSphere(qobj, 1.2, 50, 50);

	//왼쪽 눈알
	gluQuadricDrawStyle(qobj, GLU_FILL); //눈알을 만들예정이라 fill로 바꿈
	glTranslatef(-0.5, 0.0, 0.0);
	gluSphere(qobj, 0.3, 50, 50);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(qobj, 0.1, 50, 50);
	glColor3f(1.0, 1.0, 1.0); //눈알의 흰색 바탕으로 바꾸기 위해서 색 변경

	//오른쪽 눈알
	gluQuadricDrawStyle(qobj, GLU_FILL); //눈알을 만들예정이라 fill로 바꿈
	glTranslatef(1.0, 0.0, 0.0);
	gluSphere(qobj, 0.3, 50, 50);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(qobj, 0.1, 50, 50);
	glColor3f(1.0, 1.0, 1.0); //눈알의 흰색 바탕으로 바꾸기 위해서 색 변경
	gluQuadricDrawStyle(qobj, GLU_LINE); //눈알 외에 나머지는 라인으로 그리기때문에 변경

	glPopMatrix();

}

//왼쪽 어깨-팔을 모델링하는 함수이다. 저의 의도는 팔을 허리에 굽히고 있는 상태에서, 어깨는 움직이지않고 팔만 폈다 다시 접어 허리에 손이 가있는 상태를
//만들고 싶었다. 그래서 어깨와 팔을 모델링을 했지만 실제로 움직이는 아래팔만 해당한다.
void drawLeftArm() {

	glTranslatef(-1.0, 0.0, 0.0);	 //어깨를 모델링하기 위해 이동 
	glRotatef((GLfloat)Leftshoulder + 90, 1.0, -1.0, 0.0); // 90도 회전하는데, z축으로 회전시킨이유는 사선의 팔을 만들기 위해서
	glPushMatrix();	// 계층적 모델링을 위해서 어깨를 스택에 삽입
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.5, 0.5, 1.5);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8); //어깨 모델링

	glPopMatrix(); //크기를 스택에서 팝하고, 어깨 모델링으로 돌아옴

	glTranslatef(0.0, 0.0, 3.0);
	glRotatef((GLfloat)Leftelbow+90, 1.0, 1.0, 0.0); //현재 어깨의 경우 90도이기때문에 Leftelbow는 0이더라도, 90도 미리 회전된상태, 손이 허리에 가있는 상태로
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
	glRotatef((GLfloat)Rightshoulder + 90, 1.0, 1.0, 0.0); // glu특성상으로 90도 돌리는데, 어깨는 움직이지않고 팔만 허리에 손이 있다가 피고, 다시 돌아가는걸
	//표현하기 위해서 z도 회전, 이 경우 z축이 +여야함.(좌측 회전)
	glPushMatrix();	// 계층적 모델링을 위해서 스택에 삽입
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.5, 0.5, 1.5);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8); //어깨 그리기

	glPopMatrix(); //크기를 팝한후, 어깨의 TR로 돌아감.

	glTranslatef(0.0, 0.0, 3.0); //이동후
	glRotatef((GLfloat)Rightelbow +90, 1.0,-1.0, 0.0); //좌측과 마찬가지로, (좌측 회전과 반대로 우측회전을 하기 위해서 -1을 함.)
	glScalef(0.5, 0.5, 1.0); //크기 키우고
	gluCylinder(qobj, 1.0, 1.0, 1.0, 20, 8); //아래 팔을 그림/

	glTranslatef(0.0, 0.0, 1.5);
	glScalef(1.0, 0.5, 0.5);
	gluSphere(qobj, 1.0, 50, 50); //손을 모델링.
	glPopMatrix(); //현재 그린 아래팔을 팝해서, 밑에 필요한 계층적모델링에 영향을 주지않도록함.

}

//몸통,두 다리를 모델링하고, 위에서 모델링하는데 사용하는 함수들을 호출해 실제 그림을 그리는 콜백함수이다.
void MyDisplay() {
	glMatrixMode(GL_MODELVIEW); //항등행렬로 초기화
	glLoadIdentity();
	gluLookAt(0.0,0.0,0.0, pocusX, pocusY, pocusZ, 0.0, 1.0, 0.0); //항등행렬로 초기화한 후, gluLookAt을 설정
	//이렇게 함으로써 카메라 위치를 설정. 변수를 둠으로써, 변수값은 변경하여 시점을 마음대로 이동할 수 있게함.
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //그린 그림 모두 초기화 후 다시 그림
	glPushMatrix();
	//몸통의 경우, 이동을 하지않기 때문에 계층적인 모델링에서 제외해야할것같아서 스택에 삽입하지않았다. 

	glTranslatef(0.0, 0.0, 0.0);	 // Pivot 지정 및 객체 이동
	glRotatef((GLfloat)init, 1.0, 0.0, 0.0); // glu의 경우 90도 가량을 회전시켜줘야지 현재 제가 모델링한 모습을 볼수있다.
	glColor3f(1.0, 1.0, 1.0);
	glScalef(3.0, 3.0, 3.0);
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8);
	glPopMatrix(); //스택에 삽입되지는 않았지만, TRS는 자동적으로 쌓이기때문에 자동적으로 쌓인 부분을 pop해준다

	glPushMatrix(); //스택에 다시 항등행렬을 삽입해준다. 이 이후부터는 계층적인 모델링을 사용하기 때문에 또 삽입을 했다.
	//왼쪽 다리완성
	glTranslatef(-0.3, 0.5, -0.8);	 // 다리가 위치할 곳에 이동을하고
	glRotatef((GLfloat)LeftLeg + 90, 1.0, 0.0, 0.0); //위에서 몸통을 스택에 넣지않았기때문에 glu의 특성상 90도를 돌려준채 사용해야해서 90을 더해줬다.
	glTranslatef(-0.3, 0.5, 4.5);	// 위치를 이동한후
	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.0, 1.0, 2.0); //크기를 키우고
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //실제 다리를 모델링한다.
	glTranslatef(0.0, 0.0, 1.5); //밑으로 더 내려가는데 , z축을 늘리는 이유가 glRotate에서 y축과 z축의 방향이 바뀌었기때문이다.
	gluCylinder(qobj, 0.3, 0.5, 0.5, 20, 8);  //발을 모델링해준다.
	glPopMatrix(); //현재 계층적으로 모델링한 다리를 팝해줌으로써 밑에 영향이 가지않도록 한다.


	//오른쪽다리
	glPushMatrix();
	glTranslatef(0.3, 0.5, -0.8);	 // 오른쪽 다리도 마찬가지로 왼쪽다리와 비슷한데, 왼쪽다리에 +0.3한만큼 이동시켜 주면 둘의 사이간격이 딱적당하다.
	glRotatef((GLfloat)RightLeg + 90, 1.0, 0.0, 0.0); // 위와 마찬가지로 glu특성상 90을 더했다.
	glTranslatef(0.3, 0.5, 4.5);

	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.0, 1.0, 2.0); //크기를 키우고
	gluCylinder(qobj, 0.5, 0.5, 1.5, 20, 8); //오른다리 모델링 후
	glTranslatef(0.0, 0.0, 1.5); // 밑으로 내려가
	gluCylinder(qobj, 0.3, 0.5, 0.5, 20, 8); //오른발을 모델링.
	glPopMatrix(); //오른다리를 계층적으로 모델링한 스택을 팝.

	//목 머리
	glPushMatrix();
	drawNeckAndHead();

	glPushMatrix();
	//왼쪽팔 그리기
	drawLeftArm();
	//오른팔 그리기
	glPushMatrix();
	drawRightArm();

	glutSwapBuffers();
}

//실제 자동적으로 움직임을 표현할 콜백함수
void MyTimer(int element) {

	//이의 경우 선택된 메뉴에 해당하는 부울변수와, 옵션이 맞는 if문으로 가서 움직임을 표현하도록 함.
	if (LeftLeg_Control && op == 5 && !stop) {
		LeftLeg -= 1;
		if (LeftLeg < -25) //30도가량 위로 올렸다가 else에 의해 내림.
			LeftLeg_Control = false;
	}
	else if (!LeftLeg_Control && op == 5 && !stop) {
		LeftLeg += 1;
		if (LeftLeg > 0)
			stop = true;
	}
	if (RightLeg_Control && op == 4 && !stop) {
		RightLeg -= 1;
		if (RightLeg <-25) //마찬가지로 if문이 선택되면, 30도가량 올렸다가 else에 의해 내림
			RightLeg_Control = false;
	}
	else if (!RightLeg_Control && op == 4 && !stop) {
		RightLeg+= 1;
		if (RightLeg > 0)
			stop = true;
	}
	if (Head_Control && op == 1 && !stop) {
		if (Neck > 5) { //인간의 경우를 생각해 목은 5도 내리고
			Neck += 0;
			if (Head > 10) //머리는 더 내릴수 있지만,앞으로 인사하는 느낌을 주기위해 10도만 내림.
				Head_Control = false;
		}
		Neck += 1;
		Head += 1;
	}
	else if (!Head_Control && op == 1 && !stop)
	{
		if (Neck < 0) { //else if에서 해당 목,머리를 올림
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
		if (Leftelbow < -90) //위의 rightArm과 마찬가지 원리임.
			LeftArm_Control = false;
	}
	else if (!LeftArm_Control && op == 3 && !stop) {
		Leftelbow += 1;
		if (Leftelbow > 0)
			stop = true;
	}
	glutPostRedisplay();
	glutTimerFunc(30, MyTimer, 1); //timer는 한번만 호출하기 때문에, 자연스러운 움직임을 표현하기 위해서 반복적 호출을 해줌
}

//선택되는 메뉴에 따라서 timer로 이동해서 모델들이 움직이도록하는 함수.
void MyMainMenu(int value) {

	if (value == 1) {
		op = 1;
		RightLeg_Control = false; //오른다리를 움직이기
		LeftLeg_Control = false; //왼다리는 움직이지않아야함
		Head_Control = true;
		stop = false; //s눌렀을때 이동 중지.
		glutTimerFunc(30, MyTimer, 1);
	}
	if (value == 2) {
		op = 2;
		RightLeg_Control = false; //오른다리를 움직이기
		LeftLeg_Control = false; //왼다리는 움직이지않아야함
		Head_Control = false;
		RightArm_Control = true;
		stop = false; //s눌렀을때 이동 중지.
		glutTimerFunc(30, MyTimer, 1);
	}
	if (value == 3) {
		op = 3;
		LeftArm_Control = true;
		RightLeg_Control = false; //오른다리를 움직이기
		LeftLeg_Control = false; //왼다리는 움직이지않아야함
		Head_Control = false;
		stop = false; //s눌렀을때 이동 중지.
		glutTimerFunc(30, MyTimer, 1);
	}
	if (value == 4) { //오른다리와 왼다리를 구별하기 위해서는 bool변수를 제외한 일반 정수 변수를 하나두어서 다리 구별을 제어했다.
		op = 4; //4번은 오른다리를 의미
		RightLeg_Control = true; //오른다리를 움직이기
		LeftLeg_Control = false; //왼다리는 움직이지않아야함
		Head_Control = false;
		RightArm_Control = false;
		LeftArm_Control = false;
		stop = false; //s눌렀을때 이동 중지.
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

	if (key == 's') {//s키를 누를경우 stop이 true가 되면서 움직임이 멈춤
		op = -1;
		stop = true;
	}
	glutPostRedisplay();
}

//메뉴를 마우스 오른쪽 버튼에 달도록 함으로써, 메뉴를 선택할수 있게함.
void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);

	glutAddMenuEntry("Robot's head movement", 1);
	glutAddMenuEntry("Robot's right arm movement", 2);
	glutAddMenuEntry("Robot's left arm movement", 3);

	glutAddMenuEntry("Robot's right leg movement", 4);
	glutAddMenuEntry("Robot's left leg movement", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	gluQuadricDrawStyle(qobj, GLU_LINE); //qobj를 라인으로 그리기위해서 사용.
}

//gluLookAt에서 선언한 변수들을 Timer callback에서 값을 증가시킴으로써(카메라의 이동을 볼수 있음) 일정한 값이 될때 멈추도록한다.
//1.0씩 더함으로써 카메라가 옆을 가리킬때 멈추도록 하였다.
void MyViewTimer(int value) {

	if (RightControl) {
		if(pocusX<=360)
			pocusX += 1.0;
	}//X좌표로 시점을 1.0 증가
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
//special callback함수를 이용해서, 스페셜에서 선언된 키를 누르면, 카메라의 시점을 변경하도록 하였다
//기능에서 설명한것처럼 →←↑↓키를 이용하였고, 현 위치로 돌릴때는 'End'키를 이용하였다.
//키를 누른후 , 해당 control만 true로 만들어놓는다면, timer내부에서 true에 해당하는 if문만 움직이도록 설정했다.
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
	glutSpecialFunc(MySpecial); //up down left right 에 따라 자동의 시점 이동
	glutMainLoop();
	return 0;
}