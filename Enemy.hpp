#ifndef ENEMY_HPP
# define ENEMY_HPP

# include <ncurses.h>
# include <string>
# include <iostream>

class				Enemy
{
	private :
		int			hp;
		int			x;
		int			y;
		int			xMax;
		int			yMax;
		char		visual;
		WINDOW *	curwin;

	public :

		Enemy & operator=(Enemy const & copy);
		Enemy(WINDOW * win, char c);
		Enemy(void);
		Enemy(Enemy const & copy);
		~Enemy(void);

		void		move();
		void		createEnemy();
		void		setNext(Enemy * e);
		int			getX() const ;
		int			getY() const ;
		void		setX(int x);
		char		getVisual() const;
		WINDOW *	getWin() const;

};

#endif
