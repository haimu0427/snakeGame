#pragma once
#include <easyx.h>
#include <conio.h>//ʹ��getch()����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <ctime> // ���ڼ�¼ʱ��
#include <string> // �����ַ�������

//�궨��
#define SnakeLength 200
#define SnakeWidth 10
#define SPEED 100


extern int score; // ��Ϸ����
extern time_t startTime, endTime; // ��Ϸ��ʼ�ͽ���ʱ��

//���巽��ö��
enum orint
{
	//�ĸ�����
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77
};

//�����һ������:��
struct coord {
	//����
	int x, y;
	//int color;//�������Ҫ��?
};
struct Snake
{
	int length; //�ߵĳ���
	//ͷ
	//β��
	coord body[SnakeLength]; //�ߵ�����
	orint snake_orintion;

};
//����ڶ�������:ʳ��
struct Food
{
	int x, y;
	bool is_eaten;
};

extern struct Snake snake;
extern struct Food food;

//��������

void ChangeTitle();
void BGM();
void GameInit();
void DrawGame();
void SnakeMove();
void CreateFood();
void EatFood();
void CheckCollision();
void ShowGameResult();

