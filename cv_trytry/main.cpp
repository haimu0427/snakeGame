#include "head.h"
struct Snake snake;
struct Food food;

int main()
{
	//ǰ������,����
	initgraph(640, 480); //������ͼ����
	ChangeTitle();
	BGM();
	GameInit();

	while (1)
	{
		//��ʳ��
		CreateFood();
		EatFood();
		//�ı䷽��
		SnakeMove();
		//����
		DrawGame();
		FlushBatchDraw();

		//��ײ����
		CheckCollision();

		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
	}
	int ch = getchar();			  // ��ͣ�Բ鿴Ч��
	closegraph();				  // �رջ�ͼ����
	return 0;

}

