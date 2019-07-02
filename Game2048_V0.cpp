// Game2048.cpp
#include "Game2048_V0.h"
#include <stdlib.h>

Game2048::Game2048(int Win) : win(Win)		// �˹��캯����Ϊ���������ͬ��ֵ֮��
{
	int i = 0, j = 0, originNum = 2;
	while (originNum > 0)
	{
		i = rand() % N;
		j = rand() % N;
		if (x[i][j] == 0)
		{
			x[i][j] = 2;
			originNum--;
		}
	}
}

void Game2048::Create()
{
	int i = 0, j = 0, randomNum;
	while (1)
	{
		i = rand() % N;
		j = rand() % N;
		if (x[i][j] == 0)
		{
			randomNum = rand() % 2;
			if (randomNum == 0)
			{
				x[i][j] = 4;
			}
			else
			{
				x[i][j] = 2;
			}
			break;
		}
	}
}

const int *Game2048::operator[](int index) const
{
	return x[index];
}

void Game2048::Up()					// �����ڲ��ԣ�δ������任��
{
	int merged[4] = { 0, 0, 0, 0 };
	for (int row = 1; row < N; ++row)
	{
		for (int crow = row; crow >= 1; --crow)
		{
			for (int col = 0; col < N; ++col)
			{
				//��һ������Ϊ��
				if (x[crow - 1][col] == 0)
				{
					x[crow - 1][col] = x[crow][col];
					x[crow][col] = 0;
				}
				else
				{
					//�ϲ�
					if (x[crow - 1][col] == x[crow][col] && merged[col] != 1)
					{
						x[crow - 1][col] *= 2;
						x[crow][col] = 0;
						merged[col] = 1;
					}

				}
			}
		}
	}
	Create();
}

void Game2048::Down()
{
	int merged[4] = { 0, 0, 0, 0 };
	for (int row = N - 2; row >= 0; --row)
	{
		for (int crow = row; crow < N - 1; ++crow)
		{
			for (int col = 0; col < N; ++col)
			{
				//��һ������Ϊ��
				if (x[crow + 1][col] == 0)
				{
					x[crow + 1][col] = x[crow][col];
					x[crow][col] = 0;
				}
				else
				{
					//�ϲ�
					if (x[crow + 1][col] == x[crow][col] && merged[col] != 1)
					{
						x[crow + 1][col] *= 2;
						x[crow][col] = 0;
						merged[col] = 1;
					}

				}
			}
		}
	}
	Create();
}

void Game2048::Left()
{
	int merged[4] = { 0, 0, 0, 0 };
	//�����һ�в���
	for (int col = 1; col < N; ++col)
	{
		for (int ccol = col; ccol >= 1; --ccol)
		{
			for (int row = 0; row < N; ++row)
			{
				//��һ������Ϊ��
				if (x[row][ccol - 1] == 0)
				{
					x[row][ccol - 1] = x[row][ccol];
					x[row][ccol] = 0;
				}
				else
				{
					//�ϲ�
					if (x[row][ccol - 1] == x[row][ccol] && merged[row] != 1)
					{
						x[row][ccol - 1] *= 2;
						x[row][ccol] = 0;
						merged[row] = 1;
					}
				}
			}
		}
	}
	Create();
}

void Game2048::Right()
{
	int merged[4] = { 0, 0, 0, 0 };
	//���ұ�һ�в���
	for (int col = N - 2; col >= 0; --col)
	{
		for (int ccol = col; ccol <= N - 2; ++ccol)
		{
			for (int row = 0; row < N; ++row)
			{
				//��һ������Ϊ��
				if (x[row][ccol + 1] == 0)
				{
					x[row][ccol + 1] = x[row][ccol];
					x[row][ccol] = 0;
				}
				else
				{
					//�ϲ�
					if (x[row][ccol + 1] == x[row][ccol] && merged[row] != 1)
					{
						x[row][ccol + 1] *= 2;
						x[row][ccol] = 0;
						merged[row] = 1;
					}
				}
			}
		}
	}
	Create();
}
