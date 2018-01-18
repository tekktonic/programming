from pygame import *;

class CEntity:
    "A component for any object that has a position in the room"
    def __init__(self, x = 0, y = 0, w = 0 , h = 0):
        self.x = x 
        self.y = y 
        self.w = w 
        self.h = h 

class CMoving:
    def __init__(self):
        self.xSpeed = 0
        self.ySpeed = 0

class CVisible:
    "A component for any visible object"
    def __init__(self, image):
        self.change_image(self)

    def change_image(image):
        self.image = image.load(image)

    def draw(s, pos):
        s.blit(self.image, (pos.x, pos.y))

class Player:
    def __init__(self):
        self.entity = CEntity()
        self.vis = CVisible()
        self.mov = CMoving()

    def update(self):
        self.entity.x += self.mov.xSpeed
        self.entity.y += self.mov.ySpeed
        self.vis.draw(self.entity)
