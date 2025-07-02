#include "head.h"
struct Snake snake;
struct Food food;
int score = 0;
time_t startTime, endTime;

int main()
{
	//前置任务,画画
	initgraph(640, 480); //创建绘图窗口
	ChangeTitle();
	BGM();
	GameInit();

	while (1)
	{
		//吃食物
		CreateFood();
		EatFood();
		//改变方向
		SnakeMove();
		//画布
		DrawGame();
		FlushBatchDraw();

		//碰撞检验
		CheckCollision();

		if (GetAsyncKeyState(VK_ESCAPE)) {
			ShowGameResult(); // 显示游戏结果
			break;
		}
	}
	int ch = getchar();			  // 暂停以查看效果
	closegraph();				  // 关闭绘图窗口
	return 0;

}

