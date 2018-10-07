#include "Enemy.hpp"

Enemy & Enemy::operator=(Enemy const & copy)
{
	if (this != &copy)
	{
		this->x = copy.getX();
		this->y = copy.getY();
		this->xMax = copy.xMax;
		this->yMax = copy.yMax;
		this->visual = copy.visual;
		this->curwin = copy.curwin;
	}

	return (*this);
}

Enemy::Enemy(Enemy const & copy)
{
	*this = copy;

	return ;
}

Enemy::~Enemy(void)
{
	return ;
}

Enemy::Enemy(void)
{
	return ;
}

Enemy::Enemy(WINDOW * win, char c)
{
	this->hp = 1;
	this->curwin = win;
	getmaxyx(this->curwin, yMax, xMax);
	keypad(curwin, true);
	this->x = xMax - 3;
	this->y = std::rand() % yMax;
	this->visual = c;
	mvwaddch(curwin, y, x, visual);

	return ;
}

void			Enemy::setX(int x)
{
	this->x = x;
}

void			Enemy::move()
{
	if (y == 0)
		y = 1;
	if (y > 28)
		y = 28;
	mvwaddch(curwin, y, x, ' ');
	x--;
	mvwaddch(curwin, y, x, visual);
	if (x == 1)
		mvwaddch(curwin, y, x, ' ');
}

int				Enemy::getX() const
{
	return (x);
}

int				Enemy::getY() const
{
	return (y);
}

WINDOW *		Enemy::getWin() const
{
	return (curwin);
}

char			Enemy::getVisual() const
{
	return (visual);
}

