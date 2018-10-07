#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <string>
# include <iostream>
# include <ncurses.h>
# include "Bullet.hpp"
# include "Enemy.hpp"
# define HP 100
class				Player
{
	private	:
		int				x;
		int				y;
		int				xMax;
		int				yMax;
		char			visual;
		WINDOW *		curwin;
		Bullet **		bullets;
		int				maxBullet;
		int				bulletsNow;
		int				hp;
	
	public :

		Player & operator=(Player const & copy);
		Player(WINDOW * win, int y, int x, char c);
		Player(void);
		Player(Player const & copy);
		~Player(void);

		void 		mvUp();
		void 		mvDown();
		void 		mvRight();
		void 		mvLeft();
		void 		display();
		int			getMV();
		void		createBullet();
		Bullet *	getBullet(int i) const;
		void		deleteBullet();
		void		flyBullet();
		void		setBul(int i);
		int			getBulNow() const;
};

#endif
