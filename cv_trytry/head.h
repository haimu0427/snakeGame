#pragma once
#include <easyx.h>
#include <conio.h>//使用getch()函数
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <ctime> // 用于记录时间
#include <string> // 用于字符串操作

//宏定义
#define SnakeLength 200
#define SnakeWidth 10
#define SPEED 100


extern int score; // 游戏分数
extern time_t startTime, endTime; // 游戏开始和结束时间

//定义方向枚举
enum orint
{
	//四个方向
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77
};

//定义第一个对象:蛇
struct coord {
	//坐标
	int x, y;
	//int color;//这个我需要吗?
};
struct Snake
{
	int length; //蛇的长度
	//头
	//尾巴
	coord body[SnakeLength]; //蛇的身体
	orint snake_orintion;

};
//定义第二个对象:食物
struct Food
{
	int x, y;
	bool is_eaten;
};

extern struct Snake snake;
extern struct Food food;

//函数声明

void ChangeTitle();
void BGM();
void GameInit();
void DrawGame();
void SnakeMove();
void CreateFood();
void EatFood();
void CheckCollision();
void ShowGameResult();

