#define _CRT_SECURE_NO_WARNINGS

#include"snake.h"

SNAKE snake1, snake2;
extern FOOD food;
extern char now_Dir;
char now_Dir1 = RIGHT;		//蛇1现在方向
char direction1 = RIGHT;	//蛇1方向
char now_Dir2 = RIGHT2;		//蛇2现在方向
char direction2 = RIGHT2;	//蛇2方向
int win;	//判断谁赢，返回1则玩家1赢，返回2则玩家2赢
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

void printFood2(void)		//初始化食物
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
				break;		//位置重叠，重新生成food
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


void initMap2()	//画出蛇,食物和墙
{
	initSnake2();	//初始化蛇
	printFood2();

	for (int i = 0; i < snake1.length; i++)		//画snake1
	{
		gotoxy(snake1.body[i].x, snake1.body[i].y);	

		if (i == 0)	
			putchar('@');
		else
			putchar('o');
	}

	for (int i = 0; i < snake2.length; i++)		//画snake2
	{
		gotoxy(snake2.body[i].x, snake2.body[i].y);

		if (i == 0)	
			putchar('@');
		else
			putchar('o');
	}

	gotoxy(food.x, food.y);		//画食物
	putchar('$');


	//绘制地图左右，上下边界
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

	//得分说明
	gotoxy(WIDTH + 2, HEIGHT + 2);
	printf("玩家1得分：0");
	gotoxy(WIDTH + 2, HEIGHT + 4);
	printf("玩家2得分：0");
}


int MoveSnake2()		//移动蛇 , 返回1继续 ，返回0结束
{
	BODY temp1 ,temp2;
	int flag1 = 0; int flag2 = 0;
	temp1 = snake1.body[snake1.length - 1];	//记录snake1蛇尾
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


	if (_kbhit())		//移动snake
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
	case UP: snake1.body[0].y--; break;		//上移
	case DOWN: snake1.body[0].y++; break;	//下移
	case LEFT: snake1.body[0].x--; break;	//左移
	case RIGHT:snake1.body[0].x++; break;	//右移
	}
	switch (now_Dir2)
	{
		//snake2
	case UP2: snake2.body[0].y--; break;	//上移
	case DOWN2: snake2.body[0].y++; break;	//下移
	case LEFT2: snake2.body[0].x--; break;	//左移
	case RIGHT2:snake2.body[0].x++; break;	//右移
	}

	//显示蛇头
	gotoxy(snake1.body[0].x, snake1.body[0].y);
	printf("@");
	gotoxy(snake2.body[0].x, snake2.body[0].y);
	printf("@");


	//判断snake1是否吃到食物
	if (snake1.body[0].x == food.x && snake1.body[0].y == food.y)
	{
		snake1.length++;
		flag1 = 1;		//flag1 表示吃到食物
		snake1.body[snake1.length - 1] = temp1;	//蛇尾加1节
	}

	if (!flag1)		//若没吃掉食物，则在原来的蛇尾显示一个空格
	{
		gotoxy(temp1.x, temp1.y);
		printf(" ");
	}
	//判断snake2是否吃到食物
	if (snake2.body[0].x == food.x && snake2.body[0].y == food.y)
	{
		snake2.length++;
		flag2 = 1;		//flag2 表示吃到食物
		snake2.body[snake2.length - 1] = temp2;	//蛇尾加1节
	}

	if (!flag2)		//若没吃掉食物，则在原来的蛇尾显示一个空格
	{
		gotoxy(temp2.x, temp2.y);
		printf(" ");
	}


	if(flag1||flag2)		//when snake1 or snake2 eating
	{
		//更新食物
		printFood2();
		gotoxy(WIDTH + 2, HEIGHT + 2);		
		printf("玩家1当前得分：%d", snake1.length - 2);
		gotoxy(WIDTH + 2, HEIGHT + 4);
		printf("玩家2当前得分：%d", snake2.length - 2);
	}


	//判断蛇是否死亡
	if (!IsCorrect2())		//如果自撞或撞墙，则清除屏幕，显示snake1snake2最终得分，游戏结束
	{
		system("cls");		//清屏
		gotoxy(45, 12);
		printf("玩家%d赢了！", win);
		gotoxy(45, 14);
		printf("玩家1最终得分：%d", snake1.length - 2);
		gotoxy(45, 16);
		printf("玩家2最终得分： %d", snake2.length - 2);
		gotoxy(45, 18);
		printf("按任意键返回主菜单");
		char temp = _getch();
		while (temp == UP || temp == DOWN || temp == LEFT || temp == RIGHT || temp == UP2 || temp == DOWN2 || temp == LEFT2 || temp == RIGHT2)
			temp = _getch();
		system("cls");

		/*
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
		*/
		return 0;
	}
	

	//调整速度
	SpeedControl2();
	Sleep(snake1.speed);		//将进程挂起一段时间，用于控制蛇的移动速度
	Sleep(snake2.speed);

	return 1;
}



int IsCorrect2()
{
	if (snake1.body[0].x == 0 || snake1.body[0].y == 0 || snake1.body[0].x == WIDTH - 1 || snake1.body[0].y == HEIGHT - 1)	//判定snake1蛇头是否撞墙
	{
		win = 2;	//players 2 win
		return 0;
	}
	if (snake2.body[0].x == 0 || snake2.body[0].y == 0 || snake2.body[0].x == WIDTH - 1 || snake2.body[0].y == HEIGHT - 1)	//判定snake2蛇头是否撞墙
	{
		win = 1;
		return 0;
	}
		
	for (int i = 1; i < snake1.length; i++)		//判断snake1是否自撞
	{
		if (snake1.body[0].x == snake1.body[i].x && snake1.body[0].y == snake1.body[i].y)
		{
			win = 2;
			return 0;
		}
	}
	for (int i = 1; i < snake2.length; i++)		//判断snake2是否自撞
	{
		if (snake2.body[0].x == snake2.body[i].x && snake2.body[0].y == snake2.body[i].y)
		{
			win = 1;
			return 0;
		}
	}

	for (int i = 0; i < snake2.length; i++)		//判断snake1是否撞到snake2上
	{
		if (snake1.body[0].x == snake2.body[i].x && snake1.body[0].y == snake2.body[i].y)
		{
			if (i == 0) 	//如果头碰头
			{
				if (snake1.length >= snake2.length)	//如果snake1长度大于snake2
					win = 1;
				else				//snake2长度大于snake1
					win = 2;
			}

			else			//如果头碰身体
				win = 2;	//snake2赢
			return 0;
		}
	}
	for (int i = 0; i < snake1.length; i++)		//判断snake2是否撞到snake1上
	{
		if (snake2.body[0].x == snake1.body[i].x && snake2.body[0].y == snake1.body[i].y)
		{
			if (i == 0) 	//如果头碰头
			{
				if (snake1.length >= snake2.length)	//如果snake1长度大于snake2
					win = 1;
				else				//snake2长度大于snake1
					win = 2;
			}

			else			//如果头碰身体
				win = 1;	//snake1赢
			return 0;
		}
	}

	return 1;
}


void SpeedControl2()		//根据蛇长调整蛇的移动速度
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
