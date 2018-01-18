#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <sys/stat.h>
#include <sys/wait.h>

#include <unistd.h>


#include <jansson.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "maptile.h"

#include "textinput.h"
#include "tile.h"
#include "file.h"

int numVTiles, numHTiles;

SDL_Texture *tileSets[64][2];
SDL_Rect selected;


TTF_Font *fnt;

json_t *map;
json_t *jsonTiles;

char *mapname;

SDL_Window *mainWindow;
SDL_Renderer *renderer;

void finishup()
{
    SDL_Quit();
    IMG_Quit();
    exit(0);
}

void fill(struct MapTile *tiles)
{
    for (int i = 0; i < numHTiles * numVTiles; i++)
    {
        if (!tiles[i].exists)
        {
            tiles[i] = (struct MapTile){.exists = true, .y = i / numHTiles, .x = i % numHTiles, .tile = {.x = selected.x, .y = selected.y}};

            SDL_Rect dr = {.x = tiles[i].x * tileSize, .y = tiles[i].y * tileSize, .w = tileSize, .h = tileSize};
            SDL_Rect sr = {.x = selected.x, .y = selected.y, .w = tileSize, .h = tileSize};
            
//            SDL_RenderCopy(editRenderer, tileSets[currentTileSet][TR_EDIT], &sr, &dr);

            json_t *jtmp = json_object();
            json_object_set_new(jtmp, "tileX", json_integer(selected.x / tileSize));
            json_object_set_new(jtmp, "tileY", json_integer(selected.y / tileSize));
            json_array_set_new(jsonTiles, tiles[i].y * numHTiles + tiles[i].x, jtmp);
        }
    }
}

void clear(struct MapTile *tiles)
{
    for (int i = 0; i < numHTiles * numVTiles; i++)
    {
        tiles[i].exists = false;
        json_array_set_new(jsonTiles, i, json_null());
    }
}

int main(void)
{
    char *tileSetName;
    map = json_object();
    jsonTiles = json_array();
    

    printf("%d\n", json_array_size(jsonTiles));
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);
    TTF_Init();
    mainWindow = SDL_CreateWindow("Tileset?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 128, 0);
    renderer = SDL_CreateRenderer(mainWindow, -1, 0);
    if (!renderer)
        printf("renderer: %s\n", SDL_GetError());
    


    
    SDL_SetWindowTitle(mainWindow, tileSetName);
    int tileSetW, tileSetH;
    SDL_QueryTexture(tileSets[currentTileSet][TR_MAIN], NULL, NULL, &tileSetW, &tileSetH);
    
    SDL_SetWindowSize(mainWindow, tileSetW, tileSetH);

    tileSize  = textinput_int(renderer);
    json_object_set_new(map, "tilewidth", json_integer(tileSize));
    json_object_set_new(map, "tileheight", json_integer(tileSize));
//    if (SDL_RenderCopy(renderer, tileSet, &tr, NULL))
//        printf("%s\n", SDL_GetError());
    SDL_RenderPresent(renderer);

    selected = (SDL_Rect){.x = 0, .y = 0, .w = tileSize, .h = tileSize};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

    numHTiles = ceil((768 / tileSize));
    numVTiles = ceil((768 / tileSize));

    struct MapTile tiles[numHTiles * numVTiles];

    
    for (int i = 0; i < numHTiles * numVTiles; i++)
    {
        tiles[i] = (struct MapTile){.exists = false};
        json_array_append_new(jsonTiles, json_null());
    }
    printf("tiles: %d, %d\n", json_array_size(jsonTiles), numHTiles * numVTiles);

    json_object_set_new(map, "width", json_integer(numHTiles));
    json_object_set_new(map, "height", json_integer(numVTiles));
    
    SDL_Event event;
    while (true)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, tileSets[currentTileSet][TR_MAIN], NULL, NULL);
        SDL_RenderFillRect(renderer, &selected);

        SDL_RenderClear(editRenderer);
        for (int i = 0; i < numVTiles * numHTiles; i++)
        {
            if (tiles[i].exists)
            {
                SDL_Rect dr = {.x = tiles[i].x * tileSize, .y = tiles[i].y * tileSize, .w = tileSize, .h = tileSize};
                SDL_Rect sr = {.x = tiles[i].tile.x, .y = tiles[i].tile.y, .w = tileSize, .h = tileSize};

                SDL_RenderCopy(editRenderer, tileSets[currentTileSet][TR_EDIT], &sr, &dr);
            }
        }
        
        if (SDL_PollEvent(&event))
        {
//            printf("Got an event\n");
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    printf("quitting\n");
                    finishup();
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("mouse clicked\n");
                if (SDL_GetWindowFromID(event.button.windowID) == mainWindow)
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        selected.x = (event.button.x / tileSize) * tileSize;
                        selected.y = (event.button.y / tileSize) * tileSize;
                        printf("Selected: %d %d\n", selected.x, selected.y);
                    }
                }
                else
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        int xt = event.button.x / tileSize;
                        int yt = event.button.y / tileSize;
                        struct MapTile tmp = {.x = xt, .y = yt, .tile = {.x = selected.x, .y = selected.y}, .exists = true};
                        int possiblePlace = -1;
                        for (int i = 0; i < numHTiles * numVTiles; i++)
                        {

                            if (possiblePlace == -1 && !tiles[i].exists)
                                possiblePlace = i;
                            
                            if ((tiles[i].x == tmp.x && tiles[i].y == tmp.y))
                            {
                                printf("Inserting tile at %d\n", i);
                                printf("position: %d %d\n", tmp.x, tmp.y);
                                possiblePlace = i;

                                break;
                            }
                        }
                        json_t *tileAt = json_array_get(jsonTiles, yt * numHTiles + xt);
                        json_t *jtmp = json_object();
                        json_object_set_new(jtmp, "tileX", json_integer(selected.x / tileSize));
                        json_object_set_new(jtmp, "tileY", json_integer(selected.y / tileSize));
                        printf("sy, sx: %d %d\nxt, yt: %d, %d\n", selected.y, selected.x, xt, yt);
                        json_array_set_new(jsonTiles, yt * numHTiles + xt, jtmp);
                        
                        tiles[possiblePlace] = tmp;
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        int xt = event.motion.x / tileSize;
                        int yt = event.motion.y / tileSize;
                        for (int i = 0; i < numHTiles * numVTiles; i++)
                        {
                            if ((tiles[i].x == xt && tiles[i].y == yt))
                            {
                                tiles[i].exists = false;

                                break;
                            }
                        }
                        if (json_array_get(jsonTiles, yt * numHTiles + xt) != json_null())
                        {
                            json_array_set_new(jsonTiles, yt * numHTiles + xt, json_null());
                        }
                    }         
                }
                break;

            case SDL_MOUSEMOTION:
                if (SDL_GetWindowFromID(event.button.windowID) == editWindow)
                {
                    if ((event.motion.state | (~SDL_BUTTON_LMASK)) ^ (~SDL_BUTTON_LMASK))
                    {
                        int xt = event.motion.x / tileSize;
                        int yt = event.motion.y / tileSize;
                        struct MapTile tmp = {.x = xt, .y = yt, .tile = {.x = selected.x, .y = selected.y}, .exists = true};
                        int possiblePlace = -1;
                        for (int i = 0; i < numHTiles * numVTiles; i++)
                        {

                            if (possiblePlace == -1 && !tiles[i].exists)
                                possiblePlace = i;
                            
                            if ((tiles[i].x == tmp.x && tiles[i].y == tmp.y))
                            {
                                printf("Inserting tile at %d\n", i);
                                printf("position: %d %d\n", tmp.x, tmp.y);
                                possiblePlace = i;

                                break;
                            }
                        }
                        json_t *jtmp = json_object();
                        json_object_set_new(jtmp, "tileX", json_integer(selected.x / tileSize));
                        json_object_set_new(jtmp, "tileY", json_integer(selected.y / tileSize));
                        printf("sy, sx: %d %d\nxt, yt: %d, %d\n", selected.y, selected.x, xt, yt);
                        json_array_set_new(jsonTiles, yt * numHTiles + xt, jtmp);
                        tiles[possiblePlace] = tmp;
                    }
                    else if ((event.motion.state | (~SDL_BUTTON_RMASK)) ^ (~SDL_BUTTON_RMASK))
                    {
                        int xt = event.motion.x / tileSize;
                        int yt = event.motion.y / tileSize;
                        for (int i = 0; i < numHTiles * numVTiles; i++)
                        {
                            if ((tiles[i].x == xt && tiles[i].y == yt))
                            {
                                tiles[i].exists = false;

                                break;
                            }
                        }
                        if (json_array_get(jsonTiles, yt * numHTiles + xt) != json_null())
                        {
                            json_array_set_new(jsonTiles, yt * numHTiles + xt, json_null());
                        }
                    }
                }
                break;                                        
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_s)
                    save();
                else if (event.key.keysym.sym == SDLK_f)
                {
                    fill(tiles);
                }
                else if (event.key.keysym.sym == SDLK_c)
                {
                    clear(tiles);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_RenderPresent(editRenderer);
    }

}

