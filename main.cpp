#include <iostream>
#include <time.h>
#include <glut.h>

int N = 30, M = 20;                                // ширина высота в квадратах
int Scale = 25;                                    // масштаб (скольок пикселей в квадратике)

int w = Scale * N;                                 // высчитываем ширину
int h = Scale * M;                                 // и высоту

int dir, num = 4;                                  // направление (0,1,2,3) , число квадратов змейки

struct                                    // массив элементов у каждого из которых есть координата ’ и ” (по сути наша змейка)
{
	int x;
	int y;
} s[100];                                          // сразу создаем массив объектов этого класса

class Fructs                                       //  ласс отвечающий за еду
{
public:
	int x, y;

	void New()                                     // координаты нового фрукта
	{
		x = rand() % N;
		y = rand() % M;
	}

	void DrawApple()                               // закрашиваем зеленым нужный квадрат
	{
		glColor3f(0.0, 1.0, 0.0);
		glRectf(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);
	}

}  m[10];                                          // сразу создаем массив из 10 объектов этого класса


void DrawField()                                   // функци€ рисующа€ клетки на экране
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);


	for (int i = 0; i < w; i += Scale)             // идем с шагом масштаба
	{
		glVertex2f(i, 0); glVertex2f(i, h);        // рисуем ¬≈–“» јЋ№Ќџ≈ линии
	}

	for (int j = 0; j < h; j += Scale)
	{
		glVertex2f(0, j); glVertex2f(w, j);        // рисуем горизонтальные линии
	}
	
	glEnd();

	                                               // кра€ карты
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);

	glVertex2f(w, 0); glVertex2f(w, h);
	glVertex2f(0, 0); glVertex2f(w, 0);
	glVertex2f(0, 0); glVertex2f(0, h);
	glVertex2f(0, h); glVertex2f(w, h);

	glEnd();
	                                               // кра€ карты
}

void Tick()                                         // функци€ перемещени€ змейки
{
	for (int i = num; i > 0; --i)                   // от нул€ до числа секций змейки
	{
		s[i].x = s[i - 1].x;                       // последний элемент получает координаты предпоследнего
		s[i].y = s[i - 1].y;
	}


	if (dir == 0) s[0].y += 1;                     // вверх
	if (dir == 1) s[0].x -= 1;                     // лево
	if (dir == 2) s[0].x += 1;                     // право
	if (dir == 3) s[0].y -= 1;                     // низ


	for (int i = 0; i < 10; i++)                      // ≈сли мы наехали на €блоко
	{
		if ((s[0].x == m[i].x) && (s[0].y == m[i].y)) // сравниваем координаты головы и всех €блок
		{ 
			num++;                                    // увеличиваем змею
			m[i].New();                               // текущее €блоко "пересоздаем" - дав ему новые координаты
		}
	}

	if (s[0].x >= N) dir = 1;                          // если упераемс€в край, мен€ем направление на противоположное
	if (s[0].x <= 0) dir = 2;
	if (s[0].y >= M) dir = 3;
	if (s[0].y <= 0) dir = 0;

	for (int i = 1; i < num; i++)                     // проверка, если укусили себ€
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

void MyKeyboard(int key, int a, int b)      // key - коды клавишь нажатых на клавиатуре
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
	display();                                       // отображаетс€ то, что на экране
	Tick();                                          // перемещение змейки
	glutTimerFunc(150, timer, 0);                     // поновой запускаетс€ функци€ таймер
}




int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));

	//-------------------------------------

	for (int i = 0; i < 10; i++)
	{
		m[i].New();
	}

	s[0].x = 10;                                    // начальные координаты головы
	s[0].y = 10;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w + 2 * Scale, h + 2 * Scale);                       // размер экрана равен высоте и ширине
	glutCreateWindow("Test");                       // название экрана "test"
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w + 2 * Scale, 0, h + 2 * Scale);
	
	glutDisplayFunc (display);                      // назначаем функцию, котора€ будет выводить на экран то, что мы рисуем
	                                                // название придумываем сами!

	glutTimerFunc(150, timer, 0);                    // объ€вл€ем нашу функцию таймер (задержка в милисекундах)
	glutSpecialFunc(MyKeyboard);                    // регистрируем нашу функцию
	
	glutMainLoop();                                 // заходим в основной цикл программы


	//-------------------------------------

	system("pause");
	return 0;
}