#include <ncurses.h>
#include <string>
#include "Player.hpp"
#include <ctime>

void				createEnemy(Enemy **e, WINDOW * w)
{
	int 			i;

	i = -1;
	while (++i < 64)
	{
		if (e[i] == NULL)
		{
			e[i] = new Enemy(w, '0');
			return ;
		}
	}
}

void				moveAllEnemy(Enemy **e)
{
	int 			i;

	i = -1;
	while (++i < 64)
	{
		if (e[i] != NULL)
			e[i]->move();
	}
}

void				deleteEnemy(Player *p, Enemy **e, int &my_score)
{
	int 			i;

	i = -1;
	while (++i < 64)
	{
		if (e[i] != NULL)
		{
			int j;

			j = -1;
			while (++j < 64)
			{
				if (p->getBullet(j) && e[i]->getX() == p->getBullet(j)->getX() \
					&& e[i]->getY() == p->getBullet(j)->getY())
				{
					my_score += 20;
					delete(e[i]);
					e[i] = NULL;
					p->setBul(p->getBulNow() - 1);
					break ;
				}
			} 
		}
	}
}

int					main()
{
	unsigned int start, stop;
	initscr();
	noecho();
	cbreak();

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	//!!!!!!!!!!!!!
	int my_score = 0;
	int level = 0;
	int enemy_speed = 15000;
	int min = 0;
	int sec = 0;
	int sum;
	clock_t t1,t2;
	WINDOW * statmenu = newwin(6, 15, 0, 0);
	box(statmenu, 0, 0);
	nodelay(statmenu, true);
	refresh();
	wrefresh(statmenu);
	mvwprintw(statmenu, 3, 1, "HP : %d", 100);
	//!!!!!!!!!!!!!
	WINDOW * menuwin = newwin(30, 80, (yMax/2) - 10, 10);
	Enemy		**e = new Enemy *[64];
	box(menuwin, 0, 0);
	nodelay(menuwin, true);
	refresh();
	wrefresh(menuwin);
	int i = -1;
	unsigned int		z = 0;
	int flag = 0;

	curs_set(0);
	while (++i < 64)
		e[i] = NULL;
	Player *p = new Player(menuwin, 1, 1, '$');

	std::cout << t1 << "\n";
	while (1)
	{
		deleteEnemy(p, e, my_score);
		if (my_score > 80)
		{ 
			level += 1;
			my_score = 0;
			enemy_speed /= 2;
		}
		sec = (int)(clock()/1000000.0) % 60;
		if (sec == 59 && flag == 0)
		{
			flag = 1;
			min++;
		}
		if (sec < 59)
			flag = 0;
		mvwprintw(statmenu, 1, 1, "Timer : %02i:%02i", min, sec);
		mvwprintw(statmenu, 2, 1, "Score: %02i", my_score);
		mvwprintw(statmenu, 4, 1, "Level : %d", level);
		wrefresh(statmenu);
		p->deleteBullet();
		if (z % 1000 == 0)
			p->flyBullet();
		if (z % enemy_speed == 0)
			moveAllEnemy(e);		
		if (z % 100000 == 0)
			createEnemy(e, menuwin);
		p->getMV();
		p->display();
		wrefresh(menuwin);
		z++;
		//std::cout << "runtime = " << clock()/1000000.0 << std::endl;
	}
	getch();
	endwin();
	return (0);
	//std::cout << "runtime = " << clock()/1000.0 << std::endl; // время работы программы                
}
