#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <time.h>
#ifndef SNAKE_H
#define SNAKE_H
struct snakepart{
	int x,y;
	snakepart(int col, int row);
	snakepart();
};
class snakeclass{
    time_t Gstart, Pstart, Gend,Pend;
	char direction;
    bool gget;
    bool pget;
	int maxwidth;
	int maxheight;
	char partchar;
	char oldalchar;
    snakepart growth;
    snakepart poison;
	char g_item;
	char p_item;
	bool failed;
	std::vector<snakepart> snake;
    void putgrowth();
    void putpoison();
	void movesnake();
	bool collision();
public:
	snakeclass();
	~snakeclass();
	void start();
};
#endif