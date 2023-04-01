/***********************************************************************/
/*                 HW#1 : 3D Sierpinski Gasket	                       */
/*  작성자 : 송수영                              날짜 : 2021년 9월 17일*/
/*                                                                     */
/* 문제 정의 : 2d로 정의된 sierpinski gasket 코드를 3d 코드로 변환하는 */
/* 문제와 덧붙여 Reshape callback 함수를 사용해서 왜곡 문제 해결	   */
/* 기능 : main에서 설정한 콜백함수를 이용해서 화면의 좌표를 정하고 왜곡*/
/* 문제를 해결한다. MyDisplay는 3d 삼각형을 만들기 위해 좌표 4개를 찍고*/
/*임의의 점을 하나 설정하여 중점을 구한다.그 후 50000번 좌표를 정하고 한*/
/*꺼번에 출력한다. MyReshape의 경우 새로운 윈도우 크기를 현재 윈도우 크기*/
/*와의 비율을 재고나서, 그에 맞게 뷰포트를 설정해 준다.그럼으로써 왜곡문*/
/*제를 해결한다. MyInit의 경우 색과 초기 투영변환을 실시한다.           */
/***********************************************************************/

#include <gl/glut.h>
#include <stdlib.h> //random을 가져오니깐.

//callback함수 이름 정의, main작성 후 코드 작성할 예정
void MyDisplay();
void MyReshape(int NewWidth,int NewHeight);
void MyInit();

void main(int argc, char** argv) {

	glutInit(&argc, argv); //argc ,argv를 인자값으로 넘겨서 glut 초기화를 수행함.
	glutInitDisplayMode(GLUT_RGB); //window 창을 RGB모드 기본색으로 설정하기
	glutInitWindowSize(500, 500); //윈도우 창 크기는 500,500으로, 위치는 0,0 에서 시작함.
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2D->3D Sierpinski gasket");
	glutDisplayFunc(MyDisplay); //그림 그리는 콜백함수
	// 윈도우창에 그려질 sierpinski gasket 코드를 담은 함수를 콜백함수로 등록.
	glutReshapeFunc(MyReshape); //왜곡문제 해결 콜백함수
	// 윈도우창의 크기가 변경될시 변경된 크기를 윈도우가 인지하여 인자값으로 전달
	// 그 인자값을 이용해서 왜곡이 발생하지 않게 투영변환을 바꿔줄 코드를 콜백함수로 등록
	MyInit();
	glutMainLoop(); //윈도우 창이 종료되기 전까지 유지
	
}

void MyDisplay() {
	float vertices[4][3] = { {0.0,130.0,-1.0},{230,500.0,0.3},{500.0,130.0,-1.0},{200.0,0.0,1.0} };
	//3d를 만들기 위해 z값을 설정하고, 3차원 삼각형을 만들기 위해 4개의 꼭지점을 생성해준다.
	float p[3] = { 250.0,100.0,0.5 }; //찍힐 포인트 3d형이기 때문에 x,y,z값을만들어줘야함
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT); //색을 저장하는 BUFFER를 비움

	for (j = 0; j < 50000; j++) {
		i = rand() % 4; //3d로 만들기 위해서 설정한 4개의 점들 중 하나를 랜덤으로 고른다.
		p[0] = (p[0] + vertices[i][0]) / 2.0;  
		p[1] = (p[1] + vertices[i][1]) / 2.0;
		p[2] = (p[2] + vertices[i][2]) / 2.0;
		//랜덤으로 골라진 수의 x,y,z 좌표의 중점을 구한 후 
		glBegin(GL_POINTS);
			glVertex3fv(p);
			//3개의 실수 값을 입력받는 glvertex를 이용한다. 뒤에 v가 붙여져있기때문에 배열임...
		glEnd();
	}
	glFlush(); //한번에 출력
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight); //위치, 새로 만들어진 윈도우 크기에 맞춰 뷰포트 설정
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)500.0;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)500.0;
	//비율비를 구해서 투영변환를 수행하기 위한 변수

	glMatrixMode(GL_PROJECTION); //투영변환 함수
	glLoadIdentity(); //항등함수로 설정
	glOrtho(0.0 * WidthFactor, 500.0 * WidthFactor, 0.0 * HeightFactor, 500.0 * HeightFactor, 1, -1);
	//새로운 크기에 맞춰 glOrtho 변화
}

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //흰배경으로 초기화
	glColor3f(1.0,0.0,0.0); //빨간색으로 설정

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //항등행렬
	glOrtho(0.0, 500.0, 0.0, 500.0, 1, -1); //초기 투영변환

}
