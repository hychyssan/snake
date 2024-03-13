#define _CRT_SECURE_NO_WARNINGS

#include"snake.h"

SNAKE snake1, snake2;
extern FOOD food;
extern char now_Dir;
char now_Dir1 = RIGHT;		//��1���ڷ���
char direction1 = RIGHT;	//��1����
char now_Dir2 = RIGHT2;		//��2���ڷ���
char direction2 = RIGHT2;	//��2����
int win;	//�ж�˭Ӯ������1�����1Ӯ������2�����2Ӯ
//no score temporily

void initSnake2(void)
{
	snake1.length = 2;		//snake1
	snake1.speed = 250;
	snake1.body[0].x = (WIDTH / 4);
	snake1.body[0].y = (HEIGHT / 4);
	snake1.body[1].x = (WIDTH / 4)-1;
	snake1.body[1].y = (HEIGHT / 4);


	snake2.length = 2;		//snake2
	snake2.speed = 250;
	snake2.body[0].x = (WIDTH / 4);
	snake2.body[0].y = 3*(HEIGHT / 4);
	snake2.body[1].x = (WIDTH / 4) - 1;
	snake2.body[1].y = 3*(HEIGHT / 4);
}

void printFood2(void)		//��ʼ��ʳ��
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		food.x = rand() % (WIDTH - 2) + 1;	//0~WIDTH
		food.y = rand() % (HEIGHT - 2) + 1;	//0~HEIGHT

		for (int k = 0; k <= snake1.length - 1; k++)
		{
			if (food.x == snake1.body[k].x && food.y == snake1.body[k].y)		//can't touch snake1
			{
				flag = 1;
				break;		//λ���ص�����������food
			}
			else if (food.x == snake2.body[k].x && food.y == snake2.body[k].y)		//snake2
			{
				flag = 1;
				break;
			}
		}

		gotoxy(food.x, food.y);
		printf("$");
	}


	return;
}


void initMap2()	//������,ʳ���ǽ
{
	initSnake2();	//��ʼ����
	printFood2();

	for (int i = 0; i < snake1.length; i++)		//��snake1
	{
		gotoxy(snake1.body[i].x, snake1.body[i].y);	

		if (i == 0)	
			putchar('@');
		else
			putchar('o');
	}

	for (int i = 0; i < snake2.length; i++)		//��snake2
	{
		gotoxy(snake2.body[i].x, snake2.body[i].y);

		if (i == 0)	
			putchar('@');
		else
			putchar('o');
	}

	gotoxy(food.x, food.y);		//��ʳ��
	putchar('$');


	//���Ƶ�ͼ���ң����±߽�
	for (int i = 0; i < HEIGHT - 1; i++)
	{
		gotoxy(0, i);
		printf("|");
		gotoxy(WIDTH - 1, i);
		printf("|");
	}

	for (int i = 0; i < WIDTH; i++)	//i is i early
	{
		gotoxy(i, 0);
		printf("-");
		gotoxy(i, HEIGHT - 1);
		printf("-");
	}

	//�÷�˵��
	gotoxy(WIDTH + 2, HEIGHT + 2);
	printf("���1�÷֣�0");
	gotoxy(WIDTH + 2, HEIGHT + 4);
	printf("���2�÷֣�0");
}


int MoveSnake2()		//�ƶ��� , ����1���� ������0����
{
	BODY temp1 ,temp2;
	int flag1 = 0; int flag2 = 0;
	temp1 = snake1.body[snake1.length - 1];	//��¼snake1��β
	temp2 = snake2.body[snake2.length - 1];

	for (int i = snake1.length - 1; i >= 1; i--)	//move snake1 and draw it body
	{
		snake1.body[i] = snake1.body[i - 1];
	}
	gotoxy(snake1.body[1].x, snake1.body[1].y);
	printf("o");
	for (int i = snake2.length - 1; i >= 1; i--)	//move snake1 and draw it body
	{
		snake2.body[i] = snake2.body[i - 1];
	}
	gotoxy(snake2.body[1].x, snake2.body[1].y);
	printf("o");


	if (_kbhit())		//�ƶ�snake
	{
		int direction = _getch();		
		switch (direction)
		{
		case UP:
			//direction1 = direction;
			if (now_Dir1 != DOWN) {
				now_Dir1 = direction;
				//now_Dir = direction;	//save th cotten
			}
			break;

		case DOWN:
			//direction1 = direction;
			if (now_Dir1 != UP) {
				now_Dir1 = direction;
				//now_Dir = direction;
			}
			break;
		case LEFT:
			//direction1 = direction;
			if (now_Dir1 != RIGHT) {
				now_Dir1 = direction;
				//now_Dir = direction;
			}
			break;
		case RIGHT:
			//direction1 = direction;
			if (now_Dir1 != LEFT) {
				now_Dir1 = direction;
				//now_Dir = direction;
			}
			break;
		case UP2:
			//direction2 = direction;
			if (now_Dir2 != DOWN2) {
				now_Dir2 = direction;
				//now_Dir = direction;
			}
			break;

		case DOWN2:
			//direction2 = direction;
			if (now_Dir2 != UP2) {
				now_Dir2 = direction;
				//now_Dir = direction;
			}
			break;
		case LEFT2:
			//direction2 = direction;
			if (now_Dir2 != RIGHT2) {
				now_Dir2 = direction;
				//now_Dir = direction;
			}
			break;
		case RIGHT2:
			//direction2 = direction;
			if (now_Dir2 != LEFT2) {
				now_Dir2 = direction;
				//now_Dir = direction;
			}
			break;
		}
	}

	switch (now_Dir1)
	{
		//snake1
	case UP: snake1.body[0].y--; break;		//����
	case DOWN: snake1.body[0].y++; break;	//����
	case LEFT: snake1.body[0].x--; break;	//����
	case RIGHT:snake1.body[0].x++; break;	//����
	}
	switch (now_Dir2)
	{
		//snake2
	case UP2: snake2.body[0].y--; break;	//����
	case DOWN2: snake2.body[0].y++; break;	//����
	case LEFT2: snake2.body[0].x--; break;	//����
	case RIGHT2:snake2.body[0].x++; break;	//����
	}

	//��ʾ��ͷ
	gotoxy(snake1.body[0].x, snake1.body[0].y);
	printf("@");
	gotoxy(snake2.body[0].x, snake2.body[0].y);
	printf("@");


	//�ж�snake1�Ƿ�Ե�ʳ��
	if (snake1.body[0].x == food.x && snake1.body[0].y == food.y)
	{
		snake1.length++;
		flag1 = 1;		//flag1 ��ʾ�Ե�ʳ��
		snake1.body[snake1.length - 1] = temp1;	//��β��1��
	}

	if (!flag1)		//��û�Ե�ʳ�����ԭ������β��ʾһ���ո�
	{
		gotoxy(temp1.x, temp1.y);
		printf(" ");
	}
	//�ж�snake2�Ƿ�Ե�ʳ��
	if (snake2.body[0].x == food.x && snake2.body[0].y == food.y)
	{
		snake2.length++;
		flag2 = 1;		//flag2 ��ʾ�Ե�ʳ��
		snake2.body[snake2.length - 1] = temp2;	//��β��1��
	}

	if (!flag2)		//��û�Ե�ʳ�����ԭ������β��ʾһ���ո�
	{
		gotoxy(temp2.x, temp2.y);
		printf(" ");
	}


	if(flag1||flag2)		//when snake1 or snake2 eating
	{
		//����ʳ��
		printFood2();
		gotoxy(WIDTH + 2, HEIGHT + 2);		
		printf("���1��ǰ�÷֣�%d", snake1.length - 2);
		gotoxy(WIDTH + 2, HEIGHT + 4);
		printf("���2��ǰ�÷֣�%d", snake2.length - 2);
	}


	//�ж����Ƿ�����
	if (!IsCorrect2())		//�����ײ��ײǽ���������Ļ����ʾsnake1snake2���յ÷֣���Ϸ����
	{
		system("cls");		//����
		gotoxy(45, 12);
		printf("���%dӮ�ˣ�", win);
		gotoxy(45, 14);
		printf("���1���յ÷֣�%d", snake1.length - 2);
		gotoxy(45, 16);
		printf("���2���յ÷֣� %d", snake2.length - 2);
		gotoxy(45, 18);
		printf("��������������˵�");
		char temp = _getch();
		while (temp == UP || temp == DOWN || temp == LEFT || temp == RIGHT || temp == UP2 || temp == DOWN2 || temp == LEFT2 || temp == RIGHT2)
			temp = _getch();
		system("cls");

		/*
		//������߷�
		int score = snake.length - 2;
		FILE* pt = fopen("top.txt", "r");	//���ļ���ȡ֮ǰ��߷�
		fscanf(pt, "%u", &max);
		fclose(pt);

		if (score > max)	//�������߷�
		{
			pt = fopen("top.txt", "w");
			fprintf(pt, "%u", score);		//����߷ֶ���top.txt
			fclose(pt);
		}
		*/
		return 0;
	}
	

	//�����ٶ�
	SpeedControl2();
	Sleep(snake1.speed);		//�����̹���һ��ʱ�䣬���ڿ����ߵ��ƶ��ٶ�
	Sleep(snake2.speed);

	return 1;
}



int IsCorrect2()
{
	if (snake1.body[0].x == 0 || snake1.body[0].y == 0 || snake1.body[0].x == WIDTH - 1 || snake1.body[0].y == HEIGHT - 1)	//�ж�snake1��ͷ�Ƿ�ײǽ
	{
		win = 2;	//players 2 win
		return 0;
	}
	if (snake2.body[0].x == 0 || snake2.body[0].y == 0 || snake2.body[0].x == WIDTH - 1 || snake2.body[0].y == HEIGHT - 1)	//�ж�snake2��ͷ�Ƿ�ײǽ
	{
		win = 1;
		return 0;
	}
		
	for (int i = 1; i < snake1.length; i++)		//�ж�snake1�Ƿ���ײ
	{
		if (snake1.body[0].x == snake1.body[i].x && snake1.body[0].y == snake1.body[i].y)
		{
			win = 2;
			return 0;
		}
	}
	for (int i = 1; i < snake2.length; i++)		//�ж�snake2�Ƿ���ײ
	{
		if (snake2.body[0].x == snake2.body[i].x && snake2.body[0].y == snake2.body[i].y)
		{
			win = 1;
			return 0;
		}
	}

	for (int i = 0; i < snake2.length; i++)		//�ж�snake1�Ƿ�ײ��snake2��
	{
		if (snake1.body[0].x == snake2.body[i].x && snake1.body[0].y == snake2.body[i].y)
		{
			if (i == 0) 	//���ͷ��ͷ
			{
				if (snake1.length >= snake2.length)	//���snake1���ȴ���snake2
					win = 1;
				else				//snake2���ȴ���snake1
					win = 2;
			}

			else			//���ͷ������
				win = 2;	//snake2Ӯ
			return 0;
		}
	}
	for (int i = 0; i < snake1.length; i++)		//�ж�snake2�Ƿ�ײ��snake1��
	{
		if (snake2.body[0].x == snake1.body[i].x && snake2.body[0].y == snake1.body[i].y)
		{
			if (i == 0) 	//���ͷ��ͷ
			{
				if (snake1.length >= snake2.length)	//���snake1���ȴ���snake2
					win = 1;
				else				//snake2���ȴ���snake1
					win = 2;
			}

			else			//���ͷ������
				win = 1;	//snake1Ӯ
			return 0;
		}
	}

	return 1;
}


void SpeedControl2()		//�����߳������ߵ��ƶ��ٶ�
{
	switch (snake1.length)
	{
	case 3:snake1.speed = 120; break;
	case 6:snake1.speed = 100; break;
	case 9:snake1.speed = 80; break;
	case 12:snake1.speed = 60; break;
	case 15:snake1.speed = 50; break;
	case 18:snake1.speed = 40; break;
	case 21:snake1.speed = 30; break;
	case 24:snake1.speed = 20; break;

	default: break;
	}

	switch (snake2.length)
	{
	case 3:snake2.speed = 120; break;
	case 6:snake2.speed = 100; break;
	case 9:snake2.speed = 80; break;
	case 12:snake2.speed = 60; break;
	case 15:snake2.speed = 50; break;
	case 18:snake2.speed = 40; break;
	case 21:snake2.speed = 40; break;
	case 24:snake2.speed = 30; break;
	default: break;
	}
}
