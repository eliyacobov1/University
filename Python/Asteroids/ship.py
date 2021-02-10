from screen import Screen
from math import cos,sin,radians

class Ship:
    def __init__(self,coord_x,speed_x,coord_y,speed_y,direction):
        self.coord_x = coord_x
        self.speed_x = speed_x
        self.coord_y = coord_y
        self.speed_y = speed_y
        self.direction = direction
        self.radius=1
        # an attribute that represents the ship's life
        self.life=3

    def move(self):
        # Moves the given object according to the given formula
        old_coord_x = self.coord_x
        self.coord_x = ((self.speed_x + old_coord_x - Screen.SCREEN_MIN_X) % (Screen.SCREEN_MAX_X
                                                                                  - Screen.SCREEN_MIN_X) + Screen.SCREEN_MIN_X)
        old_coord_y = self.coord_y
        self.coord_y = ((self.speed_y + old_coord_y - Screen.SCREEN_MIN_Y) % (Screen.SCREEN_MAX_Y
                                                                                  - Screen.SCREEN_MIN_Y) + Screen.SCREEN_MIN_Y)

    def user_movements(self,screen):
        if Screen.is_left_pressed(screen):
            self.direction+=7
        if Screen.is_right_pressed(screen):
            self.direction-=7
        if Screen.is_up_pressed(screen):
            current_speed_x=self.speed_x
            self.speed_x=current_speed_x+cos(radians(self.direction))
            current_speed_y = self.speed_y
            self.speed_y = current_speed_y + sin(radians(self.direction))


