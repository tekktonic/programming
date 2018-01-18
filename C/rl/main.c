#include "sanify.h"
#include "entity.h"
#include "player.h"
#include <ncurses.h>
#include <stdlib.h>

int main()
{
    struct Entity_s e;
    Player p;
    struct Entity_s w;
    Player wp;
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);

    e.data = malloc(sizeof(struct Player_s));
    p = (Player)e.data;

    p->position[0] = p->position[1] = 0;
    e.vis = '@';
    e.attrs[0] = A_UNDERLINE;
    e.attrs[1] = 0;

    w.data = malloc(sizeof(struct Player_s));
    wp = w.data;
    wp->position[0] = wp->position[1] = 1;
    w.vis = '#';
    w.attrs[0] = 0;

    print_entity(&e);
    print_entity(&w);
    refresh();
    while (1) {
	switch (getch())
	{
	case 'h':
	    p->position[0]--;
	    if (p->position[0] == wp->position[0] && p->position[1] == wp->position[1])
		p->position[0]++;
	    break;
	case 'n':
	    p->position[1]++;
	    if (p->position[0] == wp->position[0] && p->position[1] == wp->position[1])
		p->position[1]--;
	    break;
	case 'e':
	    p->position[1]--;
	    if ((p)->position[0] == (wp)->position[0] && p->position[1] == wp->position[1])
		p->position[1]++;
	    break;
	case 'i':
	    p->position[0]++;
	    if (p->position[0] == wp->position[0] && p->position[1] == wp->position[1])
		p->position[0]--;
	    break;
	case 'b':
	    p->position[0]--;
	    if (p->position[0] == wp->position[0] && p->position[1] == wp->position[1])
		p->position[0]--;
	    break;

	}
	erase();

	print_entity(&e);
	print_entity(&w);
	refresh();
	redrawwin(stdscr);
    }
    
    endwin();
}
       
