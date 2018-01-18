import os
import pytmx
import sdl2
import sdl2.ext
import itertools

import player

def bg_build(m): # get around some weird bug in subclassing TiledMap
    m.bg_image = sdl2.SDL_CreateRGBSurface(0, m.width * m.tilewidth, m.height * m.tileheight, 32, 0, 0, 0, 0)

    for tile in m.get_layer_by_name("level"):
        (x, y, img) = tile
        sdl2.SDL_BlitSurface(m.images[img], None, m.bg_image, sdl2.SDL_Rect(x * 24, y * 24, 24, 24))



class Level(pytmx.TiledMap):
    def __init__(self, name, window):
        self.window = window
        pytmx.TiledMap.__init__(self, name)

        self._load_images()
        self.lava = self.get_layer_by_name("lava")
        self.flag = self.get_layer_by_name("flag")
        self.walls = self.get_layer_by_name("wall")
        self.saws = self.get_layer_by_name("saw")

        playerTile = (self.get_layer_by_name("player"))[0]
        
        x, y = playerTile.x, playerTile.y
        self.player = player.Player(x, y, self.window)
        bg_build(self)

    def _load_images(self):
        self.images = [None] * self.maxgid

        for s in self.tilesets:
            if s.source is None:
                continue

            path = os.path.join(os.path.dirname(self.filename), s.source)
            image = sdl2.ext.load_image(path)
            w, h = image.w, image.h
            tw = s.tilewidth
            th = s.tileheight

            p = itertools.product(range(0, h, th), range(0, w, tw))
            for real_gid, (y, x) in enumerate(p, s.firstgid):
                rect = sdl2.SDL_Rect(x, y, tw, th)
                gids = self.map_gid(real_gid) # the following madness is to make sure that the pytmx image array matches its gids with the tiled one. Why this can't be hidden in the
                #library is beyond me...

                if gids is None:
                    gids = [self.register_gid(real_gid)]

                for gid, flags in gids:
                    self.register_gid(gid)
                    self.images.append(None)
                    print(gid)
                    self.images[gid] = sdl2.SDL_CreateRGBSurface(0, tw, th,
                                                                 32,
                                                                 0, 0, 0, 0)
                    sdl2.SDL_BlitSurface(image, rect, self.images[gid], None)

    def update(self):
        self.player.update(self.lava, self.flag, self.walls)
    def draw(self):
        sdl2.SDL_BlitSurface(self.bg_image, None, self.window.get_surface(), None)
        self.player.draw()



if (__name__ == "__main__"):
    sdl2.ext.init()
    window = sdl2.ext.Window("test", size=(1600, 600))


    window.show()

    m = GameMap("resources/level1.tmx", window)

    sdl2.SDL_BlitSurface(m.bg_image, None, window.get_surface(), None)
    m.player.draw()
    window.refresh()

    sdl2.SDL_Delay(3000)


