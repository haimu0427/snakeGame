#define _CRT_SECURE_NO_WARNINGS 1
#include "head.h"


//�޸Ĵ��ڱ���
void ChangeTitle()
{

	//��ȡ���ھ��
	HWND hwnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hwnd, _T("����"));
	//��������,��ʾ�û�����
	int is_ok = MessageBox(hwnd, _T("ʹ�÷��������С�ߵ��ƶ�,����ESC���˳�"),
		_T("������ʾ"), MB_OKCANCEL);
	if (is_ok == IDCANCEL)
	{
		printf("�û�ȡ���˲���\n");
	}
	else if (is_ok == IDOK)
	{
		printf("�û�������ȷ��\n");
	}

}
//���ű�������
void BGM() {
	// �ڴ��ļ�ǰ�ȹرտ��ܴ��ڵ��豸
	mciSendString(_T("close all"), NULL, 0, NULL);

	// ��Ȼ�󲥷�����
	mciSendString(_T("open ./�����Ҽǵ�.mp3 alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
	mciSendString(_T("setaudio mymusic volume to 300"), NULL, 0, NULL);
}


//��Ϸ��ʼ��
void GameInit()
{
	startTime = time(nullptr); // ��¼��Ϸ��ʼʱ��
	score = 0; // ��ʼ������

	//��ʼ����
	snake.length = 3;
	snake.snake_orintion = RIGHT;
	snake.body[0].x = 300;//�����ܲ�����for����ʼ��,��Ȼ����	
	snake.body[0].y = 300;
	snake.body[1].x = 290;
	snake.body[1].y = 300;
	snake.body[2].x = 280;
	snake.body[2].y = 300;

	//��ʼ��ʳ��
	srand((unsigned int)time(NULL));//�������������
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.is_eaten = false;

}
//������Ϸ
void DrawGame()
{

	BeginBatchDraw();
	cleardevice();

	//����ͼƬ,���Ʊ���
	IMAGE img;
	loadimage(&img, _T("./����.jpg"));
	putimage(0, 0, &img);

	//������
	/*setfillcolor(RED);
	fillrectangle(snake.body[0].x, snake.body[0].y,
		snake.body[0].x + SnakeWidth, snake.body[0].y + SnakeWidth);
	setfillcolor(GREEN);*/
	// �����ߣ�ʹ��ͼƬ
	IMAGE snakeHeadImg;
	loadimage(&snakeHeadImg, _T("./snake_head.png")); // ������ͼƬ
	putimage(snake.body[0].x, snake.body[0].y, &snakeHeadImg); // ��ͼƬ���Ƶ���ͷλ��


	for (int i = 1; i < snake.length; i++)
	{
		/*fillrectangle(snake.body[i].x, snake.body[i].y,
			snake.body[i].x + SnakeWidth, snake.body[i].y + SnakeWidth);*/

			// �����ߣ�ʹ��ͼƬ
		IMAGE snakeBodyImg;
		loadimage(&snakeBodyImg, _T("./snake_body.png")); // ������ͼƬ
		putimage(snake.body[i].x, snake.body[i].y, &snakeBodyImg); // ��ͼƬ���Ƶ�����λ��

	}
	//����ʳ��
	setfillcolor(BLUE);
	//fillroundrect(food.x, food.y, food.x + SnakeWidth, food.y + SnakeWidth, 5, 5);
	
	// ����ʳ�ʹ��ͼƬ
	IMAGE foodImg;
	loadimage(&foodImg, _T("./apple.png")); // ����ƻ��ͼƬ
	putimage(food.x, food.y, &foodImg); // ��ͼƬ���Ƶ�ʳ��λ��

}


//�ߵ��ƶ�
void SnakeMove()
{

	//�ߵ������ƶ�
	for (int i = snake.length - 1; i > 0; i--)
	{
		snake.body[i].x = snake.body[i - 1].x;
		snake.body[i].y = snake.body[i - 1].y;
	}
	//��ͷ�ƶ�, Ҳ���Ǹ��ݹ���ģ���
	orint current_direction = snake.snake_orintion;

	// ���ݼ���������·��򣬵����ⷴ��
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

	// ���ݷ��������ͷ����
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
//����ʳ��
void CreateFood()
{
	if (food.is_eaten)
	{
		bool flag;
		while (1)
		{
			flag = false; //��־λ

			//ʳ����Ҫ����ʮ��
			food.x = (rand() % 64) * 10;
			food.y = (rand() % 48) * 10;
			food.is_eaten = false;

			//ʳ�ﲻ�����ߵ�������
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
//��ʳ��
void EatFood()
{
	if (abs(snake.body[0].x - food.x) < SnakeWidth && abs(snake.body[0].y - food.y) < SnakeWidth)
	{
		// �߳Ե�ʳ��
		snake.length++;// �ߵĳ�������
		score += 10; // ÿ�γԵ�ʳ������10��
		food.is_eaten = true;// ʳ�ﱻ�Ե�
		
	}
}

//��ײ����
void CheckCollision()
{
	//�����ͷ�Ƿ������߽�
	if (snake.body[0].x < 0 || snake.body[0].x >= 640 || snake.body[0].y < 0 || snake.body[0].y >= 480)
	{
		MessageBox(GetHWnd(), _T("��Ϸ����,��ײ���˱߽�"), _T("��Ϸ����"), MB_OK);
		ShowGameResult();
		exit(0);
	}
	//�����ͷ�Ƿ������Լ�������
	for (int i = 1; i < snake.length; i++)
	{
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
		{
			MessageBox(GetHWnd(), _T("��Ϸ����,��ײ�����Լ�"), _T("��Ϸ����"), MB_OK);
			ShowGameResult();
			exit(0);
		}
	}
}

//��Ϸ����������ʾ
void ShowGameResult()  
{  
   endTime = time(nullptr); // ��¼��Ϸ����ʱ��  
   double duration = difftime(endTime, startTime); // ������Ϸʱ��  

   // �������ַ���  
   std::wstring result = L"��Ϸ������\n";  
   result += L"����: " + std::to_wstring(score) + L"\n";  
   result += L"ʱ��: " + std::to_wstring(duration) + L" ��";  

   // ����������ʾ���  
   MessageBox(NULL, result.c_str(), L"��Ϸ���", MB_OK);  
}
