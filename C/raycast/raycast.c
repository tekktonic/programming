#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define TAU (M_PI*2)
#define FOV  (TAU/4) // 90 degrees, wolfenstein style
#define DRAW_DISTANCE 16
#include <SDL.h>

#include <dtype.h>


struct vector
{
    int x, y;
};

struct vectorf
{
    float x, y;
};


struct Player
{
    struct vectorf pos;
    float direction;
};

bool map[64][64];


struct Player Player_rotate(struct Player player, float angle)
{
    struct Player ret;
    ret.pos = player.pos;
    ret.direction = (player.direction + angle + TAU) % TAU;

    return ret;
}

struct Player Player_move(struct Player player, int distance)
{
    struct Player ret;
    int dx = floor(cos(player.direction) * distance);
    int dy = floor(sin(player.direction) * distance);
    if (Map_get(player.pos.x + dx, player.pos.y) <= 0) // make sure that the location is
	// free
	ret.pos.x = player.pos.x + dx;
    else
	ret.pos.x = player.pos.x;

    if (Map_get(player.pos.x, player.pos.y + dy) <= 0)
	ret.pos.y = player.pos.y + dy;
    else
	ret.pos.y = player.pos.y;
    return ret;
}

void populate_map(void)
{
    for (int i = 0; i < 64; ++i)
    {
	if (i == 0 || i == 63)
	{
	    memset(map, 1, 64);
	}
	else
	{
	    map[i][0] = map[i][63] = 1;
	}
    }
}

struct step
{
    struct vectorf pos;
    int length;
    int height;
    int distance;
};
