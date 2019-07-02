// Game2048.h
#ifndef GAME_2048_H
#define GAME_2048_H

const int N = 4;

class Game2048
{
public:
	Game2048(int Win=2048);
	const int *operator[](int index) const;
	void Up(), Down(), Left(), Right();
	void Create();

private:
	int x[N][N], win;
};

#endif
