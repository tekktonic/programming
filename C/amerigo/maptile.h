#ifndef MAPTILE_H
#define MAPTILE_H
enum TextureRenderEnum
{
    TR_MAIN,
    TR_EDIT
};


// maptile is a tile on the map being edited
struct MapTile
{
    struct Tile tile;
    int x;
    int y;
    bool exists;
};
#endif
