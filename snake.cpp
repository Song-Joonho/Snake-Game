#include "snake.h"
#include <unistd.h>
using namespace std;
snakepart::snakepart(int col,int row)
{
	x=col;
	y=row;
}

snakepart::snakepart()
{
	x=0;
	y=0;
}
snakeclass::snakeclass()
{
	initscr();
	nodelay(stdscr,true);			
	keypad(stdscr,true);			
	noecho();									
	curs_set(0);							
	getmaxyx(stdscr,maxheight,maxwidth);
	partchar='@';
	oldalchar=(char)219;
	f_item = 'F';
	p_item = 'P';

	failed=false;
	for(int i=0;i<5;i++)
		snake.push_back(snakepart(40+i,10));
	direction='l';
	//윗벽 생성
	for(int i=0;i<maxwidth-1;i++)
	{
		move(0,i);
		addch(oldalchar);
	}
	//왼쪽벽 생성 
	for(int i=0;i<maxheight-1;i++)
	{
		move(i,0);
		addch(oldalchar);
	}
	//아래벽 생성
	for(int i=0;i<maxwidth-1;i++)
	{
		move(maxheight-2,i);
		addch(oldalchar);
	}
	//오른쪽 벽 생성
	for(int i=0;i<maxheight-1;i++)
	{
		move(i,maxwidth-2);
		addch(oldalchar);
	}
	//snake 생성
	for(int i=0;i<snake.size();i++)
	{
		move(snake[i].y,snake[i].x);
		addch(partchar);
	}
	refresh();
}

snakeclass::~snakeclass()
{
	nodelay(stdscr,false);			
	getch();										
	endwin();
}


bool snakeclass::collision()
{
	if(snake[0].x==0 || snake[0].x==maxwidth-1 || snake[0].y==0 || snake[0].y==maxheight-2)
		return true;
	for(int i=2;i<snake.size();i++)
	{
		if(snake[0].x==snake[i].x && snake[0].y==snake[i].y)
			return true;
	}
	
	
}


void snakeclass::movesnake()
{
	//detect key
	int tmp=getch();
	switch(tmp)
	{
		case KEY_LEFT:
			if(direction=='r')
				failed=true;
			else 	
				direction='l';
			break;
		case KEY_UP:
			if(direction=='d')
				failed=true;
			else 	
				direction='u';
			break;
		case KEY_DOWN:
			if(direction=='u')
				failed=true;
			else 	
				direction='d';
			break;
		case KEY_RIGHT:
			if(direction=='l')
				failed=true;
			else 	
				direction='r';
			break;
		
	}

	move(snake[snake.size()-1].y,snake[snake.size()-1].x);
	printw(" ");
	refresh();
	snake.pop_back();
	
	if(direction=='l')
	{
		snake.insert(snake.begin(),snakepart(snake[0].x-1,snake[0].y));
	}else if(direction=='r'){
		snake.insert(snake.begin(),snakepart(snake[0].x+1,snake[0].y));

	}else if(direction=='u'){
		snake.insert(snake.begin(),snakepart(snake[0].x,snake[0].y-1));
	}else if(direction=='d'){
		snake.insert(snake.begin(),snakepart(snake[0].x,snake[0].y+1));
	}
		move(snake[0].y,snake[0].x);
		addch(partchar);
	refresh();
}


void snakeclass::start()
{
	while(1)
	{
		if(failed || collision())
		{
			move(12,36);
			printw("Failed");
			break;
		}
		movesnake();
		usleep(200000);
	}
}