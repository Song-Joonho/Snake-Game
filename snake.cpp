#include "snake.h"
#include <unistd.h>
#include <time.h>
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
	g_item = 'G';
	p_item = 'P';
    growth.x =0;
    growth.y =0;
    poison.x =0;
    poison.y=0;
	failed=false;
	for(int i=0;i<5;i++)
		snake.push_back(snakepart(40+i,10));
	gget=0;
	pget=0;

	direction='l';
	putgrowth();
	putpoison();
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

void snakeclass::putgrowth()
{
    while(1)
    {
        int tmpx=rand()%maxwidth+1;
        int tmpy=rand()%maxheight+1;
        for(int i=0;i<snake.size();i++)
            if(snake[i].x==tmpx && snake[i].y==tmpy)
                continue;
        if(tmpx>=maxwidth-2 || tmpy>=maxheight-3)
            continue;
        growth.x=tmpx;
        growth.y=tmpy;
        break;
    }
    move(growth.y,growth.x);
    addch(g_item);
    Gstart = time(NULL);
    refresh();
}
void snakeclass::putpoison()
{
    while(1)
    {
        int tmpx=rand()%maxwidth+1;
        int tmpy=rand()%maxheight+1;
        for(int i=0;i<snake.size();i++)
            if(snake[i].x==tmpx && snake[i].y==tmpy)
                continue;
        if(tmpx>=maxwidth-2 || tmpy>=maxheight-3)
            continue;
        poison.x=tmpx;
        poison.y=tmpy;
        break;
    }
    move(poison.y,poison.x);
    addch(p_item);
    Pstart = time(NULL);
    refresh();
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
	Gend=time(NULL);
    if(snake[0].x==growth.x && snake[0].y==growth.y)
    {
        gget=true;
        putgrowth();
    }else if(Gend-Gstart>7)
    {
        move(growth.y, growth.x);
        printw(" ");
        refresh();
        putgrowth();
        gget=false;
    }
    else
        gget=false;
    Pend=time(NULL);
    if(snake[0].x==poison.x && snake[0].y==poison.y)
    {
        pget=true;
        putpoison();
    }else if(Pend-Pstart>7)
    {
        move(poison.y, poison.x);
        printw(" ");
        refresh();
        putpoison();
        pget=false;
    }else
        pget=false;
    return false;
	
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

	if(!gget) {
        move(snake[snake.size() - 1].y, snake[snake.size() - 1].x);
        printw(" ");
        refresh();
        snake.pop_back();
    }
	if(pget)
    {
        move(snake[snake.size() - 1].y, snake[snake.size() - 1].x);
        printw(" ");
        refresh();
        snake.pop_back();
        if(snake.size()<2)
        {
            failed=true;
        }
    }
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
		usleep(150000);
	}
}