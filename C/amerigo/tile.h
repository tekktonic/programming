#ifndef TILE_H
#define TILE_H
// tile is a tile in the tileset
struct Tile
{
    int x;
    int y;
};
extern int tileSize;
extern int currentTileSet;

extern struct Tile currentTile;

#endif
