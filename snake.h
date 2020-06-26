#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#ifndef SNAKE_H
#define SNAKE_H
struct snakepart{
	int x,y;
	snakepart(int col, int row);
	snakepart();
};
class snakeclass{
	char direction;

	int maxwidth;
	int maxheight;
	char partchar;
	char oldalchar;
    snakepart food;
    snakepart poison;
	char f_item;
	char p_item;
	bool failed;
	std::vector<snakepart> snake;
    void putfood();
	void movesnake();
	bool collision();
public:
	snakeclass();
	~snakeclass();
	void start();
};
#endif