import sdl2
import sdl2.ext

import level
import player

def main():
    sdl2.ext.init()

    window = sdl2.ext.Window("Masa", size=(800, 600))

    window.show()

    running = True
    levelnum = 1
    l = level.Level("resources/level" + str(levelnum) + ".tmx", window)

    while running:
        events = sdl2.ext.get_events()
        
        for event in events:
            if event.type == sdl2.SDL_QUIT:
                running = False
                break
        keystate = sdl2.SDL_GetKeyboardState(None)

        if keystate[sdl2.SDL_SCANCODE_RIGHT]:
            l.player.xSpeed = 10

        elif keystate[sdl2.SDL_SCANCODE_LEFT]:
            l.player.xSpeed = -10
        else:
            l.player.xSpeed = 0

        if keystate[sdl2.SDL_SCANCODE_Z]:
            if (l.player.g == True):
                l.player.ySpeed = -15
                l.player.g = False
            # fun stuff goes here
        l.draw()
        l.update()


        window.refresh()
        sdl2.SDL_Delay(int(1000 / 30))

    return 0


main()
