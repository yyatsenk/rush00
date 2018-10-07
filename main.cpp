#include <ncurses.h>
#include <string>
#include "Player.hpp"
#include <ctime>

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}


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
	int i;
	unsigned int		z;

	i = -1;
	z = 0;
	curs_set(0);
	while (++i < 64)
		e[i] = NULL;
	Player *p = new Player(menuwin, 1, 1, '$');

	//std::srand(time(NULL));
	//t1 = clock();
	std::cout << t1 << "\n";
	while (1)
	{
		//t1 = clock();
		deleteEnemy(p, e, my_score);
		if (my_score > 80)
		{ 
			level += 1;
			my_score = 0;
			enemy_speed /= 2;
		}
		//t2 = clock();
		//sec += t1 /1000.0;
		//wait(1);
		//sec++;
		
		if (sec >= 60)
		{
			sec = 0;
			min++;
		}
		mvwprintw(statmenu, 1, 1, "Timer : %i:%i", min, sec);
		mvwprintw(statmenu, 2, 1, "Score: %i", my_score);
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
	}
	getch();
	endwin();
	return (0);
	std::cout << "runtime = " << clock()/1000.0 << std::endl; // время работы программы                
}
