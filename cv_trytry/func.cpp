#define _CRT_SECURE_NO_WARNINGS 1
#include "head.h"


//修改窗口标题
void ChangeTitle()
{

	//获取窗口句柄
	HWND hwnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hwnd, _T("玉子"));
	//弹出窗口,提示用户操作
	int is_ok = MessageBox(hwnd, _T("使用方向键控制小蛇的移动,按下ESC键退出"),
		_T("操作提示"), MB_OKCANCEL);
	if (is_ok == IDCANCEL)
	{
		printf("用户取消了操作\n");
	}
	else if (is_ok == IDOK)
	{
		printf("用户按下了确定\n");
	}

}
//播放背景音乐
void BGM() {
	// 在打开文件前先关闭可能存在的设备
	mciSendString(_T("close all"), NULL, 0, NULL);

	// 打开然后播放音乐
	mciSendString(_T("open ./赵雷我记得.mp3 alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
	mciSendString(_T("setaudio mymusic volume to 300"), NULL, 0, NULL);
}


//游戏初始化
void GameInit()
{
	startTime = time(nullptr); // 记录游戏开始时间
	score = 0; // 初始化分数

	//初始化蛇
	snake.length = 3;
	snake.snake_orintion = RIGHT;
	snake.body[0].x = 300;//这里能不能用for来初始化,当然可以	
	snake.body[0].y = 300;
	snake.body[1].x = 290;
	snake.body[1].y = 300;
	snake.body[2].x = 280;
	snake.body[2].y = 300;

	//初始化食物
	srand((unsigned int)time(NULL));//产生随机数种子
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.is_eaten = false;

}
//绘制游戏
void DrawGame()
{

	BeginBatchDraw();
	cleardevice();

	//加载图片,绘制背景
	IMAGE img;
	loadimage(&img, _T("./玉子.jpg"));
	putimage(0, 0, &img);

	//绘制蛇
	/*setfillcolor(RED);
	fillrectangle(snake.body[0].x, snake.body[0].y,
		snake.body[0].x + SnakeWidth, snake.body[0].y + SnakeWidth);
	setfillcolor(GREEN);*/
	// 绘制蛇：使用图片
	IMAGE snakeHeadImg;
	loadimage(&snakeHeadImg, _T("./snake_head.png")); // 加载蛇图片
	putimage(snake.body[0].x, snake.body[0].y, &snakeHeadImg); // 将图片绘制到蛇头位置


	for (int i = 1; i < snake.length; i++)
	{
		/*fillrectangle(snake.body[i].x, snake.body[i].y,
			snake.body[i].x + SnakeWidth, snake.body[i].y + SnakeWidth);*/

			// 绘制蛇：使用图片
		IMAGE snakeBodyImg;
		loadimage(&snakeBodyImg, _T("./snake_body.png")); // 加载蛇图片
		putimage(snake.body[i].x, snake.body[i].y, &snakeBodyImg); // 将图片绘制到蛇身位置

	}
	//绘制食物
	setfillcolor(BLUE);
	//fillroundrect(food.x, food.y, food.x + SnakeWidth, food.y + SnakeWidth, 5, 5);
	
	// 绘制食物：使用图片
	IMAGE foodImg;
	loadimage(&foodImg, _T("./apple.png")); // 加载苹果图片
	putimage(food.x, food.y, &foodImg); // 将图片绘制到食物位置

}


//蛇的移动
void SnakeMove()
{

	//蛇的身体移动
	for (int i = snake.length - 1; i > 0; i--)
	{
		snake.body[i].x = snake.body[i - 1].x;
		snake.body[i].y = snake.body[i - 1].y;
	}
	//蛇头移动, 也算是根据过程模拟的
	orint current_direction = snake.snake_orintion;

	// 根据键盘输入更新方向，但避免反向
	if (GetAsyncKeyState(VK_UP) && current_direction != DOWN) {
		snake.snake_orintion = UP;
	}
	else if (GetAsyncKeyState(VK_DOWN) && current_direction != UP) {
		snake.snake_orintion = DOWN;
	}
	else if (GetAsyncKeyState(VK_LEFT) && current_direction != RIGHT) {
		snake.snake_orintion = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && current_direction != LEFT) {
		snake.snake_orintion = RIGHT;
	}

	// 根据方向更新蛇头坐标
	switch (snake.snake_orintion)
	{
	case UP:
		snake.body[0].y -= SnakeWidth;
		break;
	case DOWN:
		snake.body[0].y += SnakeWidth;
		break;
	case LEFT:
		snake.body[0].x -= SnakeWidth;
		break;
	case RIGHT:
		snake.body[0].x += SnakeWidth;
		break;
	}
	Sleep(SPEED);//??
}
//创建食物
void CreateFood()
{
	if (food.is_eaten)
	{
		bool flag;
		while (1)
		{
			flag = false; //标志位

			//食物需要是整十数
			food.x = (rand() % 64) * 10;
			food.y = (rand() % 48) * 10;
			food.is_eaten = false;

			//食物不能在蛇的身体上
			for (int i = 0; i < snake.length; i++)
			{
				if (food.x == snake.body[i].x && food.y == snake.body[i].y)
				{
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				break;
			}
		}
	}
}
//吃食物
void EatFood()
{
	if (abs(snake.body[0].x - food.x) < SnakeWidth && abs(snake.body[0].y - food.y) < SnakeWidth)
	{
		// 蛇吃到食物
		snake.length++;// 蛇的长度增加
		score += 10; // 每次吃到食物增加10分
		food.is_eaten = true;// 食物被吃掉
		
	}
}

//碰撞检验
void CheckCollision()
{
	//检测蛇头是否碰到边界
	if (snake.body[0].x < 0 || snake.body[0].x >= 640 || snake.body[0].y < 0 || snake.body[0].y >= 480)
	{
		MessageBox(GetHWnd(), _T("游戏结束,蛇撞到了边界"), _T("游戏结束"), MB_OK);
		ShowGameResult();
		exit(0);
	}
	//检测蛇头是否碰到自己的身体
	for (int i = 1; i < snake.length; i++)
	{
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
		{
			MessageBox(GetHWnd(), _T("游戏结束,蛇撞到了自己"), _T("游戏结束"), MB_OK);
			ShowGameResult();
			exit(0);
		}
	}
}

//游戏结束积分显示
void ShowGameResult()  
{  
   endTime = time(nullptr); // 记录游戏结束时间  
   double duration = difftime(endTime, startTime); // 计算游戏时长  

   // 构造结果字符串  
   std::wstring result = L"游戏结束！\n";  
   result += L"分数: " + std::to_wstring(score) + L"\n";  
   result += L"时间: " + std::to_wstring(duration) + L" 秒";  

   // 弹出窗口显示结果  
   MessageBox(NULL, result.c_str(), L"游戏结果", MB_OK);  
}
