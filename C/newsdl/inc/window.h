#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>
#include "sprite.h"
struct Window_s;
typedef struct Window_s *Window;
#define Window_kill(s) H_Window_kill(&s)

Window new_Window(const char *title, int w, int h, Uint32 flags);

void Window_blit(Window self, Sprite image);
void Window_resizedCB(Window self);
void Window_draw(Window self);
SDL_Renderer *Window_getRenderer(Window self);
#endif
