#include "line.h"
#include "math.h"

line prompt_line(void)
{
    line ret;
    ret.start = prompt_point();
    ret.end = prompt_point();
    return ret;
}

void draw_line(SDL_Renderer *r, line line)
{

    if (point_distance(line.start, line.end) <= 0)
    {
        draw_point(r, line.end);
        draw_point(r, line.start);
        return;
    }

    point mid = {.x = (line.start.x + line.end.x) / 2, .y = (line.start.y + line.end.y) / 2};
    draw_line(r, (struct line){.start = line.start, .end = mid});
    draw_line(r, (struct line){.start = mid, .end = line.end});
}
