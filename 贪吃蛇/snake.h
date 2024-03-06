#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>


#define WIDTH 40
#define HEIGHT 20
#define MAX 120
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

struct BODY
{
	int x;
	int y;
};

struct SNAKE
{
	struct BODY body[20 * 60];		//snake body ,body[0]=snake head
	int speed;
	int length;
};

struct FOOD
{
	int x;
	int y;
};


//function declaretion
int Menu();
void Hide();
void About();
void Help();
void initSnake(void);
void printFood(void);
void gotoxy(int x, int y);
void initMap();
int MoveSnake();
int IsCorrect();
void SpeedControl();

/*
SNAKE snake;
FOOD food;
char now_Dir = RIGHT;
char direction = RIGHT;


int Menu()
{
	gotoxy(40, 12);
	printf("̰~��~��~С~��~Ϸ");
	gotoxy(43, 14);
	printf("1. ��ʼ��Ϸ");
	gotoxy(43, 16);
	printf("2. ����");
	gotoxy(43,18);
	printf("3. ����");
	gotoxy(43, 22);
	printf("��������˳���Ϸ");
	Hide();
	char ch;
	ch = _getch();
	int result = 0;
	switch (ch)
	{
	case '1':result = 1; break;
	case '2':result = 2; break;
	case '3':result = 3; break;
	}
	system("cls");
	return result;
}

void Hide()
{
	HANDLE	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cor_info);
}

void About()
{
	gotoxy(30, 12);
	printf("���ö���");
	gotoxy(43, 14);
	printf("̰������Ϸ");
	gotoxy(43, 16);
	printf("������������ϼ��˵�");
	Hide();
	char ch = _getch();
	system("cls");

}
void Help()
{
	//�����
}

void initSnake(void)	//��ʼ���ߣ�ȷ���ߵĳ�ʼ��С��λ��
{
	snake.length = 2;

	snake.body[0].x = WIDTH / 2;
	snake.body[0].y = HEIGHT / 2;

	snake.body[1].x = WIDTH / 2 -1;
	snake.body[1].y = HEIGHT / 2;
}

void printFood(void)		//��ʼ��ʳ��
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		food.x = rand() % WIDTH - 1;	//0~WIDTH
		food.y = rand() % HEIGHT - 1;	//0~HEIGHT

		for (int k = 0; k <= snake.length-1; k++)
		{
			if (food.x == snake.body[k].x && food.y == snake.body[k].y)
			{
				flag = 1;
				break;		//λ���ص�����������food
			}
		}

		gotoxy(food.x, food.y);
		printf("$");
	}


	return;
}

void gotoxy(int x, int y)	//��궨λ����������궨λ����x��y����λ�ã�
{
	COORD coord;
	coord.X = x;
	coord.Y = snake.body[0].y;

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hout, coord);
}

void initMap()	//������,ʳ���ǽ
{
	initSnake();	//��ʼ����
	printFood();

	for (int i = 0; i < snake.length; i++)
	{
		gotoxy(snake.body[i].x, snake.body[i].y);	//������Ƶ�������������

		if (i == 0)	//�������ͷ
			putchar('@');
		else
			putchar('o');
	}

	gotoxy(food.x, food.y);		//��ʳ��
	putchar('$');


	//���Ƶ�ͼ���ң����±߽�
	for (int i = 0; i < WIDTH; i++)
	{
		gotoxy(0, i);
		printf("-");
		gotoxy(HEIGHT - 1, i);
		printf("-");
	}

	for (int i = 1; i < HEIGHT; i++)
	{
		gotoxy(i, 0);
		printf("|");
		gotoxy(i, WIDTH - 1);
		printf("|");
	}

	//�÷�˵��
	gotoxy(5, 60);
	printf("��ǰ�÷֣�0");
}

int MoveSnake()		//�ƶ��� , ����1���� ������0����
{
	BODY temp;
	int flag = 0;
	temp = snake.body[snake.length - 1];	//��¼��β
	for (int i = snake.length - 1; i >= 1; i--)	//����������ǰ�ƶ�һ��λ��
	{
		snake.body[i] = snake.body[i - 1];
	}
	gotoxy(snake.body[1].x, snake.body[1].y);
	printf("o");

	if (_kbhit())
	{
		int direction = _getch();		//ԭ��û��int
		switch (direction)
		{
		case UP :
			if (now_Dir != DOWN)
				now_Dir = direction;
		break;

		case DOWN:
			if (now_Dir != UP)
				now_Dir = direction;
			break;
		case LEFT:
			if (now_Dir != RIGHT)
				now_Dir = direction;
			break;
		case RIGHT:
			if (now_Dir != LEFT)
				now_Dir = direction;
			break;
		}
	}

	switch (now_Dir)
	{
	case UP: snake.body[0].y--; break;		//����
	case DOWN: snake.body[0].y++; break;	//����
	case LEFT: snake.body[0].x--; break;	//����
	case RIGHT:snake.body[0].x++; break;	//����
	}

	//��ʾ��ͷ
	gotoxy(snake.body[0].x, snake.body[0].y);
	printf("@");

	//�ж��Ƿ�Ե�ʳ��
	if (snake.body[0].x == food.x && snake.body[0].y == food.y)
	{
		snake.length++;
		flag = 1;		//flag1 ��ʾ�Ե�ʳ��
		snake.body[snake.length - 1] = temp;	//��β��1��
	}

	if (!flag)		//��û�Ե�ʳ�����ԭ������β��ʾһ���ո�
	{
		gotoxy(temp.x, temp.y);
		printf(" ");
	}
	else
	{
			//����ʳ��
		printFood();
		gotoxy(5, 60);
		printf("��ǰ�÷֣�%d", snake.length - 3);
	}


	//�ж����Ƿ�����
	if (!IsCorrect())		//�����ײ��ײǽ���������Ļ����ʾ���յ÷֣���Ϸ����
	{
		system("cls");		//����
		gotoxy(45, 14);
		printf("���յ÷֣�%d", snake.length - 3);
		gotoxy(45, 16);
		printf("����������");
		gotoxy(45, 18);
		printf("��������������˵�");
		char c = _getch();
		system("cls");
		return 0;
	}

	//�����ٶ�
	SpeedControl();
	Sleep(snake.speed);		//�����̹���һ��ʱ�䣬���ڿ����ߵ��ƶ��ٶ�

	return 1;
}


int IsCorrect()
{
	if (snake.body[0].x == 0 || snake.body[0].y == 0 ||
		snake.body[0].x == WIDTH - 1 || snake.body[0].y == HEIGHT - 1)	//�ж���ͷ�Ƿ�ײǽ
		return 0;

	//�ж��Ƿ���ײ
	for (int i = 1; i < snake.length; i++)
	{
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
			return 0;
	}

	return 1;
}

void SpeedControl()		//�����߳������ߵ��ƶ��ٶ�
{
	switch (snake.length)
	{
	case 6:snake.speed = 200; break;
	case 9:snake.speed = 180; break;
	case 12:snake.speed = 160; break;
	case 15:snake.speed = 120; break;	//��д
	default: break;
	}
}

*/



