import sdl2
import sdl2.ext
import math

def next_level():
    print("YOU WON YAY")
    exit(0)

class Player(object):
    def __init__(self, x, y, window):
        self.x = int(x)

        self.y = int(y)

        self.g = False

        self.window = window
        self.xSpeed = 0
        self.ySpeed = 0

        self.image = sdl2.ext.load_image("resources/player.png")
        self.w = int(self.image.w)
        self.h = int(self.image.h)
        self.health = 100

    def collision_check(self, ls):
        return [obj for obj in ls if (self.x + self.xSpeed <= obj.x + obj.width and self.x + self.w  + self.xSpeed >= obj.x) and (self.y + self.ySpeed <= obj.y + obj.height and self.y + self.h  + self.ySpeed >= obj.y)]


    def collision_at(self, rect, obj):
        x, y, w, h = rect
        w -= 1 # make it actual width, not additional width
        h -= 1

        if x >= obj.x + obj.width:
            return False
        if x + w <= obj.x:
            return False
        if y >= obj.y + obj.height:
            return False
        if y + h < obj.y:
            return False

        return True

    def update(self, lava, flag, walls):

#        health -= 0.1

        if self.health == 0:
            exit(0)

        if (self.ySpeed < 10 and not self.g):
            self.ySpeed += 2



        print(self.x, self.y, self.w, self.h, self.xSpeed, self.ySpeed, self.g)
        if self.collision_check(flag):
            next_level()


        for wall in walls:
            if self.collision_at((self.x + 1, self.y + self.h + 2, self.w - 1, self.ySpeed), wall):
                self.g = True
                break
            else:
                self.g = False

        wall_collisions = self.collision_check(walls)
        wall_collisions = self.collision_check(walls)

        for collision in wall_collisions:
            if self.collision_at((self.x + 2, self.y + self.h, self.w - 2, self.ySpeed), collision): # bottom side
                self.g = True
                self.ySpeed = 0
                self.y = collision.y - self.h - 1

            if self.collision_at((self.x + 1, self.y + self.ySpeed, self.w - 1, abs(self.ySpeed)), collision): # top side
                self.ySpeed = 0
                self.y = collision.y + collision.height + 1

            if self.collision_at((self.x + self.xSpeed, self.y + 1, abs(self.xSpeed) - 1, self.h), collision): # left side
                self.xSpeed = 0
                self.x = collision.x + collision.width + 1

            if self.collision_at((self.x + self.w, self.y + 1, self.xSpeed - 1, self.h), collision): # right side
                self.xSpeed = 0
                self.x = collision.x - self.w - 1

        for collision in saw_collisions:
            if self.collision_at((self.x + 2, self.y + self.h, self.w - 2, self.ySpeed), collision): # bottom side
                self.g = True
                self.ySpeed = 0
                self.y = collision.y - self.h - 1

            if self.collision_at((self.x + 1, self.y + self.ySpeed, self.w - 1, abs(self.ySpeed)), collision): # top side
                self.ySpeed = 0
                self.y = collision.y + collision.height + 1

            if self.collision_at((self.x + self.xSpeed, self.y + 1, abs(self.xSpeed) - 1, self.h), collision): # left side
                self.xSpeed = 0
                self.x = collision.x + collision.width + 1

            if self.collision_at((self.x + self.w, self.y + 1, self.xSpeed - 1, self.h), collision): # right side
                self.xSpeed = 0
                self.x = collision.x - self.w - 1

        lava_collisions = self.collision_check(lava)
        for collision in lava_collisions:
            self.ySpeed = -20
            self.health += 10




        print(self.xSpeed, self.ySpeed)
        self.x += self.xSpeed
        self.y += self.ySpeed




    def draw(self):
        rect = sdl2.SDL_Rect(int(self.x), int(self.y), int(self.w), int(self.h))

        sdl2.SDL_BlitSurface(self.image, None, self.window.get_surface(), rect)
