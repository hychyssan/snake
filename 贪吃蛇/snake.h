#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>


#define WIDTH 60
#define HEIGHT 20
#define MAX 120
#define UP 'w'		//snake1's move
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define UP2 72		//snake2's move
#define DOWN2 80
#define LEFT2 75
#define RIGHT2 77

struct BODY
{
	int x;
	int y;
};

struct SNAKE
{
	struct BODY body[20 * 60];		//snake body ,body[0]=snake's head
	int speed;
	int length;
};

struct FOOD
{
	int x;
	int y;
};


//function declaration
int Menu();
void Hide();
void About();
void Help();
void Top();
void Mode();
void initSnake(void);
void initSnake2(void);
void printFood(void);
void printFood2(void);
void gotoxy(int x, int y);
void initMap();
void initMap2();
int MoveSnake();
int MoveSnake2();
int IsCorrect();
int IsCorrect2();
void SpeedControl();
void SpeedControl2();





