#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "circle.h"
#include "triangle.h"
int main(void)
{
    SDL_Window *w;
    SDL_Renderer *r;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640, 480, 0, &w, &r);
    SDL_RenderClear(r);

/*    triangle t = prompt_triangle();

    draw_triangle_filled(r, t);
*/
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    draw_circle(r, (circle){(point){320, 240}, 32});

    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    draw_triangle_filled(r, (triangle){(point){320, 0}, (point){0,479}, (point){640,479}});
    SDL_SetRenderDrawColor(r, 255, 0, 0, 100);
    draw_triangle_filled(r, (triangle){(point){320, 120}, (point){0,360}, (point){480,450}});
    SDL_RenderPresent(r);
    SDL_SetRenderDrawColor(r, 0, 255, 0, 5);
    draw_triangle_filled_rect(r, (point){0, 480},(point){0,0},(point){640,480},(point){640,0});
    SDL_RenderPresent(r);
    SDL_Delay(3000);
}
