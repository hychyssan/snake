#define _CRT_SECURE_NO_WARNINGS

#include"snake.h"

SNAKE snake;
FOOD food;
unsigned int score=0;
unsigned int max=0;
char now_Dir = RIGHT;
char direction = RIGHT;



int Menu()
{
	gotoxy(43, 10);
	printf("贪吃蛇小游戏");
	gotoxy(43, 12);
	printf("1. 开始游戏");
	gotoxy(43, 14);
	printf("2. 帮助");
	gotoxy(43, 16);
	printf("3. 关于");
	gotoxy(43, 18);
	printf("4. 最高分");
	gotoxy(43, 20);
	printf("按任意键退出游戏");
	Hide();
	char ch;
	ch = _getch();
	int result = 0;
	switch (ch)
	{
	case '1':result = 1; break;
	case '2':result = 2; break;
	case '3':result = 3; break;
	case '4':result = 4; break;
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
	gotoxy(43, 12);
	printf("懂得都懂");
	gotoxy(43, 14);
	printf("贪吃蛇游戏");
	gotoxy(43, 16);
	printf("按任意键返回上级菜单");
	Hide();
	char ch = _getch();
	system("cls");

}
void Help()
{
	
	gotoxy(40, 12);
	printf("w 上");
	gotoxy(40, 14);
	printf("s 下");
	gotoxy(40, 16);
	printf("a 左");
	gotoxy(40, 18);
	printf("d 右");
	gotoxy(40, 20);
	printf("蛇撞到自己或者墙时结束");
	gotoxy(45, 22);
	printf("按任意键返回上级菜单");
		char ch = _getch();
	system("cls");

}

void Top()
{
	unsigned int topscore;	//从top.txt读取最高分

	FILE* pt = fopen("top.txt", "r");

	fscanf(pt, "%u", &topscore);

	fclose(pt);

	gotoxy(43, 13);
	printf("最高分：%u", topscore);

	gotoxy(43, 16);
	printf("按任意键返回上级菜单");
	Hide();
	char ch = _getch();
	system("cls");
}

void initSnake(void)	//初始化蛇，确定蛇的初始大小和位置
{
	snake.length = 2;
	snake.speed = 250;

	snake.body[0].x = (WIDTH / 4) ;
	snake.body[0].y = (HEIGHT / 2) ;

	snake.body[1].x = (WIDTH / 2) - 1;
	snake.body[1].y = (HEIGHT / 2) ;
}

void printFood(void)		//初始化食物
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		food.x = rand() % (WIDTH-2) + 1;	//0~WIDTH
		food.y = rand() % (HEIGHT-2) +1;	//0~HEIGHT

		for (int k = 0; k <= snake.length - 1; k++)
		{
			if (food.x == snake.body[k].x && food.y == snake.body[k].y)
			{
				flag = 1;
				break;		//位置重叠，重新生成food
			}
		}

		gotoxy(food.x, food.y);
		printf("$");
	}


	return;
}

void gotoxy(int x, int y)	//光标定位函数，将光标定位到（x，y坐标位置）
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hout, coord);
}

void initMap()	//画出蛇,食物和墙
{
	initSnake();	//初始化蛇
	printFood();

	for (int i = 0; i < snake.length; i++)
	{
		gotoxy(snake.body[i].x, snake.body[i].y);	//将光标移到待描绘的蛇身上

		if (i == 0)	//如果是蛇头
			putchar('@');
		else
			putchar('o');
	}

	gotoxy(food.x, food.y);		//画食物
	putchar('$');


	//绘制地图左右，上下边界
	for (int i = 0; i < HEIGHT-1; i++)
	{
		gotoxy(0, i);
		printf("|");
		gotoxy(WIDTH -1 , i);
		printf("|");
	}

	for (int i = 0; i < WIDTH; i++)	//i is i early
	{
		gotoxy(i, 0);
		printf("-");
		gotoxy(i, HEIGHT - 1);
		printf("-");
	}

	//得分说明
	gotoxy(WIDTH+2, HEIGHT+2);
	printf("当前得分：0");
}

int MoveSnake()		//移动蛇 , 返回1继续 ，返回0结束
{
	BODY temp;
	int flag = 0;
	temp = snake.body[snake.length - 1];	//记录蛇尾
	for (int i = snake.length - 1; i >= 1; i--)	//所有蛇身向前移动一个位置
	{
		snake.body[i] = snake.body[i - 1];
	}
	gotoxy(snake.body[1].x, snake.body[1].y);
	printf("o");

	if (_kbhit())
	{
		int direction = _getch();		//原版没有int
		switch (direction)
		{
		case UP:
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
	case UP: snake.body[0].y--; break;		//上移
	case DOWN: snake.body[0].y++; break;	//下移
	case LEFT: snake.body[0].x--; break;	//左移
	case RIGHT:snake.body[0].x++; break;	//右移
	}

	//显示蛇头
	gotoxy(snake.body[0].x, snake.body[0].y);
	printf("@");

	//判断是否吃到食物
	if (snake.body[0].x == food.x && snake.body[0].y == food.y)
	{
		snake.length++;
		flag = 1;		//flag1 表示吃到食物
		snake.body[snake.length - 1] = temp;	//蛇尾加1节
	}

	if (!flag)		//若没吃掉食物，则在原来的蛇尾显示一个空格
	{
		gotoxy(temp.x, temp.y);
		printf(" ");
	}
	else
	{
		//更新食物
		printFood();
		gotoxy(WIDTH+2, HEIGHT+2);		//改发的哥哥哥哥哥哥哥哥哥哥哥哥哥哥哥哥哥
		printf("当前得分：%d", snake.length - 2);
	}


	//判断蛇是否死亡
	if (!IsCorrect())		//如果自撞或撞墙，则清除屏幕，显示最终得分，游戏结束
	{
		system("cls");		//清屏
		gotoxy(45, 14);
		printf("最终得分：%d", snake.length - 2);
		gotoxy(45, 16);
		printf("孩子你输了");
		gotoxy(45, 18);
		printf("按任意键返回主菜单");
		char c = _getch();
		system("cls");

		//计算最高分
		 int score = snake.length - 2;
		FILE* pt = fopen("top.txt", "r");	//打开文件读取之前最高分
		fscanf(pt, "%u", &max);
		fclose(pt);

		if (score > max)	//如果是最高分
		{
			pt = fopen("top.txt", "w");
			fprintf(pt, "%u", score);		//将最高分读入top.txt
			fclose(pt);
		}
		return 0;
	}

	//调整速度
	SpeedControl();
	Sleep(snake.speed);		//将进程挂起一段时间，用于控制蛇的移动速度

	return 1;
}


int IsCorrect()
{
	if (snake.body[0].x == 0 || snake.body[0].y == 0 ||snake.body[0].x == WIDTH - 1 || snake.body[0].y == HEIGHT-1 )	//判定蛇头是否撞墙
		return 0;

	//判断是否自撞
	for (int i = 1; i < snake.length; i++)
	{
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
			return 0;
	}

	return 1;
}

void SpeedControl()		//根据蛇长调整蛇的移动速度
{
	switch (snake.length)
	{
	case 6:snake.speed = 200; break;
	case 9:snake.speed = 180; break;
	case 12:snake.speed = 160; break;
	case 15:snake.speed = 140; break;
	case 18:snake.speed = 120; break;
	case 21:snake.speed = 100; break;
	case 24:snake.speed = 80; break;

	default: break;
	}
}
