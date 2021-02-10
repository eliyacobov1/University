from math import cos,sin,radians
from screen import Screen


class Torpedo:
    def __init__(self,coord_x,speed_x,coord_y,speed_y,direction):
        self.coord_x = coord_x
        self.speed_x = speed_x
        self.coord_y = coord_y
        self.speed_y = speed_y
        self.direction = direction
        self.count=0
        self.radius=4

    def move(self):
        # Moves the given object according to the given formula
        old_coord_x = self.coord_x
        self.coord_x = ((self.speed_x + old_coord_x - Screen.SCREEN_MIN_X) % (Screen.SCREEN_MAX_X
                                                                                  - Screen.SCREEN_MIN_X) + Screen.SCREEN_MIN_X)
        old_coord_y = self.coord_y
        self.coord_y = ((self.speed_y + old_coord_y - Screen.SCREEN_MIN_Y) % (Screen.SCREEN_MAX_Y
                                                                                  - Screen.SCREEN_MIN_Y) + Screen.SCREEN_MIN_Y)

