#include "textinput.h"

#include <SDL_ttf.h>
#include <stdbool.h>

int textinput_int(SDL_Renderer *r)
{
    size_t bufsiz = 1024;
    size_t bufused = 0;
    char *buffer = malloc(bufsiz);
    int ret = 0;

    buffer[0] = '\0';
    
    SDL_StartTextInput();

    SDL_Rect rt = {0, 0, 500, 100};
    
    while(true)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                // breaks out of loop.
                finishup();
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN)
                    goto done;
                else if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (bufused > 0)
                    {
                        buffer[bufused - 1] = '\0';
                        bufused--;
                    }
                    else
                        buffer[bufused] = '\0';
                        
                }
                break;
                    
            case SDL_TEXTINPUT:
                if (bufused + strlen(event.text.text) >= bufsiz)
                {
                    bufsiz *= 2;
                    buffer = realloc(buffer, bufsiz);
                }
                for (char *txt = event.text.text; *txt; txt++)
                {
                    if (isdigit(*txt))
                        buffer[bufused++] = *txt;
                }
//                strncat(buffer, event.text.text, bufsiz - 1);
//                bufused += strlen(event.text.text);
                buffer[bufsiz - 1] = '\0';
                break;
            }
        }
    }
done:
    SDL_StopTextInput();
    sscanf(buffer, "%d", &ret);

    return ret;
}

char *textinput_string(SDL_Renderer *target)
{
    size_t bufsiz = 1024;
    size_t bufused = 0;
    char *buffer = malloc(bufsiz);
    buffer[0] = '\0';
    
    SDL_StartTextInput();
    SDL_Rect ir = {.x = 0, .y = 0, .w = 500, .h = 100};
    
    while(true)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                // breaks out of loop.
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                    finishup();
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN)
                    goto done;
                else if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (bufused > 0)
                    {
                        buffer[bufused - 1] = '\0';
                        bufused--;
                    }
                    else
                        buffer[bufused] = '\0';
                        
                }
                break;
                    
            case SDL_TEXTINPUT:
                if (bufused + strlen(event.text.text) > bufsiz)
                {
                    bufsiz *= 2;
                    buffer = realloc(buffer, bufsiz);
                }
                strncat(buffer, event.text.text, bufsiz - 1);
                bufused += strlen(event.text.text);

                buffer[bufsiz - 1] = '\0';
                break;
            }
            SDL_Surface *tmpsurf = TTF_RenderUTF8_Blended(fnt, buffer, (SDL_Color){.r = 255, .g = 255, .b = 255, .a = 255});
            SDL_Texture *tmptex = SDL_CreateTextureFromSurface(target, tmpsurf);
            SDL_FreeSurface(tmpsurf);
            SDL_RenderClear(target);
            SDL_QueryTexture(tmptex, NULL, NULL, &ir.w, &ir.h);
            SDL_RenderCopy(target, tmptex, NULL, &ir);
            SDL_RenderPresent(target);
        }
    }
done:
    SDL_StopTextInput();
    return buffer;
}
