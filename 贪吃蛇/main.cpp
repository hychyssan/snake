#define _CRT_SECURE_NO_WARNINGS

#include"snake.h"

int main()
{
	srand((unsigned int)time(0));
	int end = 1, result;
	while (end)
	{
		result = Menu();	//ÏÔÊ¾Ö÷²Ëµ¥
		switch (result)
		{
		case 1:
			initMap();
			while (MoveSnake());
			break;
		case 2:
			Help();
			break;
		case 3:
			About();
			break;
		case 4:
			Top();
			break;
		case 0:
			end = 0; break;
		}
	}

	return 0;
}