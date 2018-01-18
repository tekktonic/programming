#include "circle.h"

#include <math.h>
#include <stdio.h>

#include "line.h"

circle prompt_circle(void)
{
    circle ret;
    ret.center = prompt_point();
    scanf("%d", &ret.radius);
    return ret;
}

static double clamp_add(double value, double increment, double clamp)
{
    return (value + increment < clamp) ? (value + increment) : clamp;
}

void draw_circle(SDL_Renderer *r, circle c)
{
    double pi = 3.14159265358979323846264338327;
    for(double position = 0.0; position < pi;
        position = clamp_add(position, (pi / 150), pi))
    {
        point outer1 = {c.center.x + (cos(position) * c.radius),
                        c.center.y + (sin(position) * c.radius)};
        point outer2 = {c.center.x - (cos(position) * c.radius),
                        c.center.y - (sin(position) * c.radius)};
        draw_line(r, (line){outer1, outer2});
        SDL_RenderPresent(r);
        SDL_Delay(10);
    }
}
