#include "file.h"

char *edit()
{
    char *editor = getenv("EDITOR");
    char *tempfile;
    FILE *fp;
    char *ret;
    struct stat s;
    if (!editor)
    {fprintf(stderr, "No editor set\n"); exit(1);}
    tempfile = mktemp("/tmp/amerigo.XXXXXXXX");
    if (fork() == 0)
        execlp(editor, editor, tempfile, NULL);
    wait(NULL);

    stat(tempfile, &s);
    ret = malloc(s.st_size + 1);
    fp = fopen(tempfile, "r");
    fread(ret, sizeof(char), s.st_size, fp);
    ret[s.st_size] = '\0';
    
    return ret;
}

int save(const char *mapname)
{
    if (!mapname)
    {
        mapname = textinput_string(renderer);
    }
    printf("%d\n", json_array_size(jsonTiles));
    json_object_set(map, "map", jsonTiles);

    printf("%s\n", mapname);
    json_dump_file(map, mapname, JSON_INDENT(4));
//    return 1;
    return json_dump_file(map, mapname, JSON_INDENT(4));
}

void loadTileSet(const char *name, SDL_Texture ***tileSets, int tileSetRows, int tileSetCols,
    json_t *map)
{
    SDL_Window *editWindow = SDL_CreateWindow("Edit", SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED, 769, 768, 0);
    SDL_Renderer *editRenderer = SDL_CreateRenderer(editWindow,
                                                    -1, 0);

    fnt = TTF_OpenFont("font.ttf", 10);
    SDL_SetRenderDrawColor(editRenderer, 255, 255, 0, 255);


    while (!tileSets[currentTileSet][TR_MAIN] || !tileSets[currentTileSet][TR_EDIT])
    {
        
        tileSetName = textinput_string(renderer);
        
        tileSets[currentTileSet][TR_MAIN] = IMG_LoadTexture(renderer, tileSetName);
        if (!tileSets[currentTileSet][TR_MAIN])
        {
            fprintf(stderr, "Something went wrong: %s\n", SDL_GetError());
            exit(1);
        }
        tileSets[currentTileSet][TR_EDIT] = IMG_LoadTexture(editRenderer, tileSetName);
        json_object_set_new(map, "tileset", json_string(tileSetName));
    }
}

void load(const char *mapname, SDL_Texture ***tileSets, int tileSetsRows, int tileSetsCols,
          json_t *mapout, json_t *jsonTilesOut)
{
    
}
