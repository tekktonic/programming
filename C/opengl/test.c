#include <GL/gl.h>
#include <SDL2/SDL.h>

int main(void)
{
    SDL_Window *win;
    SDL_GLContext ctx;
    SDL_Init(SDL_INIT_EVERYTHING);

    win = SDL_CreateWindow("Troll", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

    SDL_GLContext = SDL_GL_CreateContext(win);
    
}
