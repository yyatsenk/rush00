#include "Player.hpp"

Player & Player::operator=(Player const & copy)
{
	if (this != &copy)
	{
		this->x = copy.x;
		this->y = copy.y;
		this->yMax = copy.yMax;
		this->xMax = copy.xMax;
		this->visual = copy.visual;
		this->curwin = copy.curwin;
		this->hp = HP;
	}

	return (*this);
}

Player::Player(Player const & copy)
{
	*this = copy;
	
	return ;
}

Player::Player(void)
{
	return ;
}

Player::~Player(void)
{
	return ;
}

Player::Player(WINDOW * win, int y, int x, char c) : x(x), y(y), xMax(0), \
												 yMax(0), visual(c),\
												curwin(win)
{
	int			i;

	i = -1;
	bullets = new Bullet *[64];
	while (++i < 64)
		bullets[i] = NULL;
	getmaxyx(this->curwin, yMax, xMax);
	keypad(curwin, true);
	maxBullet = 12;
	bulletsNow = 0;
	return ;
}

void		Player::mvUp()
{
	mvwaddch(curwin, y, x, ' ');
	this->y--;
	if (this->y < 1)
		this->y = 1;
}

void		Player::mvDown()
{
	mvwaddch(curwin, y, x, ' ');
	y++;
	if (y > yMax - 2)
		y = yMax - 2;
}

void		Player::mvLeft()
{

	mvwaddch(curwin, y, x, ' ');
	x--;
	if (x < 1)
		x = 1;
}

void		Player::mvRight()
{

	mvwaddch(curwin, y, x, ' ');
	x++;
	if (x > xMax - 2)
		x = xMax - 2 ;
}

int			Player::getMV()
{
	int		choice;

	choice = wgetch(curwin);
	switch (choice)
	{
		case KEY_UP:
			mvUp();
			break;
		case KEY_DOWN :
			mvDown();
			break;
		case KEY_RIGHT :
			mvRight();
			break;
		case KEY_LEFT :
			mvLeft();
			break;
		case ' ' :
			createBullet();
			break;
		default :
			break;
	}
	return (choice);
}

void		Player::display()
{
	mvwaddch(curwin, y, x, visual);
}

void		Player::createBullet()
{
	int		i;

	i = -1;
	while (++i < 64 && bulletsNow <= maxBullet)
	{
		if (bullets[i] == NULL)
		{
			bullets[i] = new Bullet(curwin, x, y);
			bulletsNow++;
			return ;
		}
	}
}

void	Player::deleteBullet()
{
	int i;

	i = -1;
	while (++i < 64)
	{
		if (bullets[i] != NULL && bullets[i]->getX() == xMax - 3)
		{
			delete(bullets[i]);
			bullets[i] = NULL;
			bulletsNow--;
		}
	}
}

Bullet *		Player::getBullet(int i) const
{
	return (bullets[i]);
}

void			Player::flyBullet()
{
	int			i;

	i = -1;
	while (++i < 64)
	{
		if (bullets[i] != NULL)
			bullets[i]->fly();
	}
}

void			Player::setBul(int i)
{
	bulletsNow = i;
}

int				Player::getBulNow() const
{
	return (bulletsNow);
}

