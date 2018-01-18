#include "line.h"
#include "triangle.h"

triangle prompt_triangle(void)
{
    triangle ret = {prompt_point(), prompt_point(), prompt_point()};

    return ret;
}

void draw_triangle_unfilled(SDL_Renderer *r, triangle t)
{
    draw_line(r, (struct line){t.p1, t.p2});
    draw_line(r, (struct line){t.p2, t.p3});
    draw_line(r, (struct line){t.p3, t.p1});
}

void draw_triangle_filled_rect(SDL_Renderer *r, point tp1, point bp1, point tp2, point bp2)
{
    if (point_distance(tp1, bp1) <= 0 && point_distance(tp2, bp2) <= 0)
        return;

    point mp1 = point_mid(tp1, bp1);
    point mp2 = point_mid(tp2, bp2);
    draw_line(r, (struct line){mp1, mp2});
    SDL_RenderPresent(r);
    SDL_Delay(10);
    draw_triangle_filled_rect(r, tp1, mp1, tp2, mp2);
    SDL_RenderPresent(r);
            SDL_Delay(10);
    draw_triangle_filled_rect(r, mp1, bp1, mp2, bp2);
    SDL_RenderPresent(r);
            SDL_Delay(10);
}

void draw_triangle_filled(SDL_Renderer *r, triangle t)
{
    if (point_distance(t.p1, t.p2) <= 0 || point_distance(t.p1, t.p3) <= 0 ||
        point_distance(t.p2, t.p3) <= 0 )
    {
        return;
    }
    point mp1 = point_mid(t.p1, t.p2);
    point mp2 = point_mid(t.p1, t.p3);


    draw_triangle_filled(r, (struct triangle){t.p1, mp1, mp2});
    SDL_RenderPresent(r);
            SDL_Delay(10);
    draw_triangle_filled_rect(r, mp1, t.p2, mp2, t.p3);
}

