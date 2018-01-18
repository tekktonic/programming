#include <math.h>

#include "point.h"

void draw_point(SDL_Renderer *r, point p)
{
    SDL_RenderDrawPoint(r, p.x, p.y);
}

point prompt_point(void)
{
    point ret;
    scanf("%d %d", &ret.x, &ret.y);
    return ret;
}


int point_distance(point p1, point p2)
{
    // a^2 + b^2 = c^2
    int x1 = p1.x > p2.x ? p1.x : p2.x;
    int x2 = p1.x < p2.x ? p1.x : p2.x;
    int y1 = p1.y > p2.y ? p1.y : p2.y;
    int y2 = p1.y < p2.y ? p1.y : p2.y;

    #ifdef BUGGY_DISTANCE
    return (int)sqrt(x1 - x2 + y1 - y2) - 1;
    #else
    return (int)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) - 1;
    #endif
}

point point_mid(point p1, point p2)
{
    point ret = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    return ret;
}
