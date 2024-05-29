#include <iostream>
#include <time.h>
#include <glut.h>

int N = 30, M = 20;                                // ������ ������ � ���������
int Scale = 25;                                    // ������� (������� �������� � ����������)

int w = Scale * N;                                 // ����������� ������
int h = Scale * M;                                 // � ������

int dir, num = 4;                                  // ����������� (0,1,2,3) , ����� ��������� ������

struct                                    // ������ ��������� � ������� �� ������� ���� ���������� � � � (�� ���� ���� ������)
{
	int x;
	int y;
} s[100];                                          // ����� ������� ������ �������� ����� ������

class Fructs                                       // ����� ���������� �� ���
{
public:
	int x, y;

	void New()                                     // ���������� ������ ������
	{
		x = rand() % N;
		y = rand() % M;
	}

	void DrawApple()                               // ����������� ������� ������ �������
	{
		glColor3f(0.0, 1.0, 0.0);
		glRectf(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);
	}

}  m[10];                                          // ����� ������� ������ �� 10 �������� ����� ������


void DrawField()                                   // ������� �������� ������ �� ������
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);


	for (int i = 0; i < w; i += Scale)             // ���� � ����� ��������
	{
		glVertex2f(i, 0); glVertex2f(i, h);        // ������ ������������ �����
	}

	for (int j = 0; j < h; j += Scale)
	{
		glVertex2f(0, j); glVertex2f(w, j);        // ������ �������������� �����
	}
	
	glEnd();

	                                               // ���� �����
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);

	glVertex2f(w, 0); glVertex2f(w, h);
	glVertex2f(0, 0); glVertex2f(w, 0);
	glVertex2f(0, 0); glVertex2f(0, h);
	glVertex2f(0, h); glVertex2f(w, h);

	glEnd();
	                                               // ���� �����
}

void Tick()                                         // ������� ����������� ������
{
	for (int i = num; i > 0; --i)                   // �� ���� �� ����� ������ ������
	{
		s[i].x = s[i - 1].x;                       // ��������� ������� �������� ���������� ��������������
		s[i].y = s[i - 1].y;
	}


	if (dir == 0) s[0].y += 1;                     // �����
	if (dir == 1) s[0].x -= 1;                     // ����
	if (dir == 2) s[0].x += 1;                     // �����
	if (dir == 3) s[0].y -= 1;                     // ���


	for (int i = 0; i < 10; i++)                      // ���� �� ������� �� ������
	{
		if ((s[0].x == m[i].x) && (s[0].y == m[i].y)) // ���������� ���������� ������ � ���� �����
		{ 
			num++;                                    // ����������� ����
			m[i].New();                               // ������� ������ "�����������" - ��� ��� ����� ����������
		}
	}

	if (s[0].x >= N) dir = 1;                          // ���� ���������� ����, ������ ����������� �� ���������������
	if (s[0].x <= 0) dir = 2;
	if (s[0].y >= M) dir = 3;
	if (s[0].y <= 0) dir = 0;

	for (int i = 1; i < num; i++)                     // ��������, ���� ������� ����
		if (s[0].x == s[i].x && s[0].y == s[i].y) num = i;

}

void DrawSnake()
{
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < num; i++)
	{
		glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + 1) * Scale, (s[i].y + 1) * Scale);
	}

}

void MyKeyboard(int key, int a, int b)      // key - ���� ������� ������� �� ����������
{
	switch (key)
	{
	case 101: dir = 0; break;
	case 102: dir = 2; break;
	case 100: dir = 1; break;
	case 103: dir = 3; break;
	}
}


void display()
{
	
	glClear(GL_COLOR_BUFFER_BIT);                  

	for (int i = 0; i < 10; i++)
		m[i].DrawApple();

	DrawField();
	DrawSnake();

	glFlush();                                    

}


void timer(int = 0)
{
	display();                                       // ������������ ��, ��� �� ������
	Tick();                                          // ����������� ������
	glutTimerFunc(150, timer, 0);                     // ������� ����������� ������� ������
}




int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));

	//-------------------------------------

	for (int i = 0; i < 10; i++)
	{
		m[i].New();
	}

	s[0].x = 10;                                    // ��������� ���������� ������
	s[0].y = 10;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w + 2 * Scale, h + 2 * Scale);                       // ������ ������ ����� ������ � ������
	glutCreateWindow("Test");                       // �������� ������ "test"
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w + 2 * Scale, 0, h + 2 * Scale);
	
	glutDisplayFunc (display);                      // ��������� �������, ������� ����� �������� �� ����� ��, ��� �� ������
	                                                // �������� ����������� ����!

	glutTimerFunc(150, timer, 0);                    // ��������� ���� ������� ������ (�������� � ������������)
	glutSpecialFunc(MyKeyboard);                    // ������������ ���� �������
	
	glutMainLoop();                                 // ������� � �������� ���� ���������


	//-------------------------------------

	system("pause");
	return 0;
}