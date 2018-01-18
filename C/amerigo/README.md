# Amerigo

## Basic info
Amerigo is just about the simplest map editor that you can make. It has only a handful of dependencies (SDL2, its image, and ttf libraries, and Jansson),
and exports maps in a custom JSON format. There is essentially no user interface yet, and this serves as the only documentation

## Using
When amerigo is first run, type in the name of the tileset, then hit enter. The palette window will resize to the tileset's size. Next, type in the tile size
and hit enter; in the interface tilesets with non-square tiles aren't yet supported, but the format allows for it. After this the windows will start drawing, the
palette of tiles in one window, the map being edited in the other, the map is currently hardcoded to 768 x 768 (48x48 for 16 bit tiles, 24x24 for 32) but there's
no reason for that to always be the case. You select a tile by clicking on it in the palette, and the tile will be highlighted. Clicking in the editor window will
place the tile. Right clicking on a tile will erase the tile. Hitting s will save the map; if you haven't saved before this session, type the name of the map and
hit return, otherwise it will save to the location you've given it. Hitting f will fill every blank space with the currently selected tile; I suggest doing this at
the start of the project with whatever base tile you're using. Hitting c will clear all tiles.

## TODO/Bugs:
This is just a list of things that I think I'll want to see; they'll be added as I find that I actually need them. They're listed in no particular order.
* Input windows should pop to the top
* Support tile layers (and layer naming?)
* Support opening maps to continue editing
* Flexible map sizes (and map size > window size)
* Support non-square tiles
* Add properties to tiles (requires a new text area widget)
* Code cleanup (seriously needed, but refactoring as I go to an extent.)
* Entities, objects not bound to the grid, nor to being made of a single tile.
* Render the map to a single image file to avoid overhead. Involves extracting tiles with properties into entities, which in turn means entities need to exist.
