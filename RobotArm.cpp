/***********************************************************************/
/*                     HW#4 : 로봇 손-팔 모델링				    	   */
/*  작성자 : 송수영                             날짜 : 2021년 10월 26일*/
/*                                                                     */
/* 문제 정의 : 모델변환을 이용해서 물체를 이동시키고 회전, 크기를 키운 */
/* 다. 그리고 push와 pop을 이용해 계층적 모델링을 완성시킨후 같이 움직 */
/* 이는 로봇을 모델링한다.											   */	
/* 기능 : MyDisplay에서 실제 그림을 그리고, finger 변수들을 이용해서   */
/* 조건들을 만족시키고, 자연스러운 손을 연출하려고 했다. 키보드를 눌렀 */
/* 을때 time 콜백함수를 호출시켜서 연속적으로 손가락을 접는 행위를 하도*/
/* 록 했고, s키를 눌렀을때 멈추도록 했다.							   */	
/***********************************************************************/

#include <Gl/glut.h>
#define STOP -1 //멈춤을 의미하는 메크로

static int shoulder =20, elbow = 20, TwoFinger_bot = 0, TwoFinger_mid = 0, TwoFinger_top = 0; //두번째 손가락에 대한 변수와 아래팔, 위팔에 대한 변수
bool TwoFinger = true; //두번째 손가락이 접힐때 누름
bool OneFinger = true; //첫번째 손가락이 접힐때 누름
float move_X = 0., move_Y = 0.; //첫번째 손가락의 x와 y를 조절함으로써 자연스러운 손가락접힘을 보여주기위해서 사용.
float Twomove_X = 0., Twomove_Y = 0;//두번째 손가락의 xy를 조절함으로써 자연스러운 손가락접힘을 구현한다.
int op = 0; //어떤 손가락을 true시킬지 결정.
static int OneFinger_bot = 0, OneFinger_mid = 0, OneFinger_top = 0;
bool ThreeFinger = true;//세번째 손가락 접기
static int ThreeFinger_bot = 0, ThreeFinger_mid = 0, ThreeFinger_top = 0;
float Threemove_X = 0., Threemove_Y = 0.; //세번째 손가락 접기를 위한 변수들을 선언
bool AllFinger = false; //모든 손가락 접기 
int velocity = 3; //손가락 움직이는 속도
bool fold = false;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //그린 그림 모두 초기화 후 다시 그림

	glMatrixMode(GL_MODELVIEW); //항등행렬로 초기화
	glLoadIdentity();
	glPushMatrix();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	
	//위 어깨_ 위 팔
	glTranslatef(-1.0, 0.0, 0.0); //x축 -1.0 이동  
	glRotatef((GLfloat)shoulder, 0.0, 1.0, 1.0);// shoulder각도만큼 0,1,1 로 회전
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0); //즉 (0,0)에서 크기 2만큼 키운다.
	glutWireCube(1.0); //즉 양 측 x가 2인 사각형 
	glPopMatrix(); //pop으로 인해 TRT부분으로 이동 즉 0,0,0 원점

	//아래팔 모델링
	glTranslatef(1.0, 0.0, 0.0);//+ 1만큼해서 좌표가 2로 이동!
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0); //2,0...
	glPushMatrix(); //첫번째 손가락 모델링을 위함
	glPushMatrix(); //두번째 손가락 모델링을 위함
	glPushMatrix(); //세번째 손가락 모델링을 위함
	glScalef(2.0, 0.4, 1.0); //크기를 2만큼 키운후
	glutWireCube(1.0);
	glPopMatrix(); //아래팔 push 제거

	//손가락아랫마디 모델링
	glTranslatef(1.0, 0.2, 0.6);//아래팔 좌표에서 1.0이동 후 회전
	glRotatef((GLfloat)OneFinger_bot, 0.0, 0.0, 1.0); //z축 0,0,1을 기준으로 접힐 각도 설정, 맨 아래 마디는 90도밖에 회전이 안된다.
	glPushMatrix(); //계층적 모델링을 위해서 스택에 삽입
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix();

	//가운데 마디 모델링
	glTranslatef(0.7 + move_X, 0.0 + move_Y, 0.2);//가운데 손가락 마디를 이전 Translate보다 0.6만큼 이동시킨 후 z방향으로 회전
	glRotatef((GLfloat)OneFinger_mid, 0.0, 0.0, 1.0);
	glPushMatrix();
	//가운데 마디 위치와 방향 push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //크기를 제외한 가운데 마디로 위치로 이동

	//마지막 마디 모델링
	glTranslatef(0.7 + move_X, 0.0 + move_Y, 0.0);//3번째 마디 ,세번째마디는 2번째마디보다 더 빠르게 이동하며, 180도까지 꺾임이 가능하다.
	glRotatef((GLfloat)OneFinger_top, 0.0, 0.0, 1.0);
	glPushMatrix(); //마지막 마디 push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //마지막마디 스택에서 꺼냄
	glPopMatrix();

	//첫번째 스택을 꺼내지않고, 그위치에서 2번째 손가락 모델링
	glTranslatef(1.0, 0.2, 0.4);//아래팔 좌표에서 1.0이동 후 회전
	glRotatef((GLfloat)TwoFinger_bot, 0.0, 0.0, 1.0); //z축 0,0,1을 기준으로 접힐 각도 설정, 맨 아래 마디는 90도밖에 회전이 안된다.
	glPushMatrix(); //계층적 모델링을 위해서 스택에 삽입
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix();
	
	glTranslatef(0.7 + Twomove_X, 0.0 + Twomove_Y, 0.0);//가운데 손가락 마디를 이전 Translate보다 0.6만큼 이동시킨 후 z방향으로 회전
	glRotatef((GLfloat)TwoFinger_mid, 0.0, 0.0, 1.0);
	glPushMatrix();
	//가운데 마디 위치와 방향 push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //크기를 제외한 가운데 마디로 위치로 이동

	glTranslatef(0.7 + Twomove_X, 0.0+ Twomove_Y, 0.0);//3번째 마디 ,세번째마디는 2번째마디보다 더 빠르게 이동하며, 180도까지 꺾임이 가능하다.
	glRotatef((GLfloat)TwoFinger_top, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //마지막 마디 스택에서 꺼냄
	glPopMatrix();

	//세번째 손가락 모델링
	glTranslatef(1.0, 0.2,0.0);
	glRotatef((GLfloat)ThreeFinger_bot, 0, 0.0, 1.0); //z축 0,0,1을 기준으로 접힐 각도 설정, 맨 아래 마디는 90도밖에 회전이 안된다.
	glPushMatrix(); //계층적 모델링을 위해서 스택에 삽입
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.7 + Threemove_X, 0. + Threemove_Y, 0.);//가운데 손가락 마디를 이전 Translate보다 0.6만큼 이동시킨 후 z방향으로 회전
	glRotatef((GLfloat)ThreeFinger_mid, 0.0, 0.0, 1.0);
	glPushMatrix();
	//가운데 마디 위치와 방향 push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); //크기를 제외한 가운데 마디로 위치로 이동

	glTranslatef(0.7 + Threemove_X, 0. + Threemove_Y, 0.0);//3번째 마디 ,세번째마디는 2번째마디보다 더 빠르게 이동하며, 180도까지 꺾임이 가능하다.
	glRotatef((GLfloat)ThreeFinger_top, 0.0, 0.0, 1.0);
	glPushMatrix(); //마지막 마디 push
	glScalef(0.8, 0.2, 0.2);
	glutWireCube(1.0);
	glPopMatrix(); 
	glPopMatrix(); 
	//세마디를 모델링한 자료를 스택에서 제거함으로써 다음손가락은 계층적이지 않게함
	glutSwapBuffers();

}

//이 타이머 함수는 keyboard를 눌렀을때 자동적으로 손가락이 움직이는 것을 표현하기 위한 콜백함수이다.
//이때 사용되는 x,y는 손가락을 꺾었을때 관절의 유연성을 조절하기 위해서 사용된 변수이고, allFinger변수는 모든 손가락이 움직여야할때
//사용되는 bool함수이다.
//mid와 top, bot으로 나눈이유는 세마디를 구현했을때 자연스러운 접힘이 가능했기때문에 이처럼 구현하였다.

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
	//손가락은 90도 이상안꺾임.
	//fold변수만으로 반복이 일어나지않는 이유는 mouse는 한번만 왼쪽을 누르면 계속 true이기때문에.
	if (TwoFinger && (op == 2||AllFinger||fold)) { //첫번째 손가락에 대핸 
		Twomove_X = -0.25; //두번째 손가락에 유연성을 맞추기 위해서 값을 조절함.
		Twomove_Y += 0.01;

		TwoFinger_bot += velocity;
		TwoFinger_mid =(velocity+TwoFinger_bot); //원래 안쪽보다 바깥쪽이 더 크게도는 원리를 이용해서 이전 변수를 더해서 할당하는 방법을 사용했다.
		TwoFinger_top =(velocity+TwoFinger_mid);

		if (TwoFinger_bot > 80) {
			TwoFinger = false;

		}
	}
	else if (!TwoFinger && (op == 2||AllFinger||!fold)) {
		Twomove_X = -0.25; //x좌표 y좌표의 어색한 부분을 없애주기 위해서 move x와 move y변수를 사용했다. 
		Twomove_Y -= 0.01; //bot,mid,top이 이동할때마다 더해줘서, 관절들이 떨어지지않게 했다.
		TwoFinger_bot -= velocity;
		TwoFinger_mid = (TwoFinger_bot - velocity);
		TwoFinger_top = (TwoFinger_mid - velocity);

		if (TwoFinger_bot < 0) {
			TwoFinger = true;
		}

	}
	//위와 마찬가지로, 관절의 유연성을 위해 x,y를 사용했고, 멀리있는 마디가 가까이있는 마디보다 더 크게 회전하기때문에
	//이전 변수를 더해서 할당하는 방식을 이용했다.
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
		if (ThreeFinger_bot > 80) { //마지막 마디 관절이 손가락을 투과하지않도록 적당한 선에서 멈춰줌 
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
	//모든 finger들을 접게하기 위해서 allfinger이 true인 경우엔 모든 손가락이 접힘, 하지만 s를 누를 경우 false로 바껴버림.
	//손가락들을 하나씩 움직이게 하는 로직을 구현.
	glutPostRedisplay();
	glutTimerFunc(30, MyTimer, 1);
}
//손가락 선택에 옵션을 지정해, 해당 key가 눌렸을때 옵션을 전달하여 timer콜백함수 내부에서 해당 옵션을 시행하도록 함.
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
		op = 0; //세손가락 다 선택되었기때문에 op은 0이지만, allfinger이 true가 된다.
		AllFinger = true;
		glutTimerFunc(30, MyTimer, 1);
		break;
	case 's':
		op = 0; //초기화 어떤 손가락도 선택되지않음
		AllFinger = false;
		break;
	}
	//옵션에 따라서 손가락을 고르고, 그 손가락에 따라 숫자가 결정된다. 순자를 눌렀을때 전달되는 변수값에 의해서 손가락이 이동하게된다.

	glutPostRedisplay();
}
//마우스를 왼쪽을 눌렀을때 접히기때문에 fold는 true 손가락도 잡기위해 손가락 움직임 -> 한번만 움직이기 위해서 설정
//마우스 오른쪽을 눌렀을때 돌아오기 위해서 fold도 or로 연결함. 즉 fold true 나머지 손가락이 false이면 원래 자리로 돌아간다.
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

//윈도우 초기화및 생성, 배경색 초기화
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