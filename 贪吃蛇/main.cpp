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
		case 2: //´ýÐ´
			initMap2();
			while (MoveSnake2());
			break;
		case 3:
			Help();
			break;
		case 4:
			About();
			break;
		case 5:
			Top();
			break;
		case 0:
			end = 0; break;
		}
	}

	return 0;
}