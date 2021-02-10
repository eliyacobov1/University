from screen import Screen
from math import sqrt,pow,factorial
from ship import Ship
from torpedo import Torpedo
import sys

collision_title = "Alert"
collision_message = "Your spaceship has been hit!"
life_over_title = "Game over"
life_over_message = "You ran out of chances,game over!"

class Asteroid:
    def __init__(self, coord_x, speed_x, coord_y, speed_y, size):
        self.coord_x = coord_x
        self.speed_x = speed_x
        self.coord_y = coord_y
        self.speed_y = speed_y
        self.size = size
        self.radius = size*10-5

    def move(self):
        # Moves the given object according to the given formula
        old_coord_x = self.coord_x
        self.coord_x = ((self.speed_x + old_coord_x - Screen.SCREEN_MIN_X) % (Screen.SCREEN_MAX_X
                                                                                  - Screen.SCREEN_MIN_X) + Screen.SCREEN_MIN_X)
        old_coord_y = self.coord_y
        self.coord_y = ((self.speed_y + old_coord_y - Screen.SCREEN_MIN_Y) % (Screen.SCREEN_MAX_Y
                                                                                  - Screen.SCREEN_MIN_Y) + Screen.SCREEN_MIN_Y)

    def has_intersection(self,obj,screen,gamerunner):
        # return True if there is a collision
        distance=sqrt(pow(obj.coord_x-self.coord_x,2)+pow(obj.coord_y-self.coord_y,2))
        if distance<=self.radius+obj.radius:
            if type(obj) is Ship:
                # checks if the object that was involved is the ship,if so,removes one life
                # and prints message
                Screen.show_message(screen,collision_title,collision_message)
                Screen.remove_life(screen)
                gamerunner.ship.life-=1
                # also removes the asteroid that was hit
                Screen.unregister_asteroid(screen,self)
                gamerunner.asteroid_list.remove(self)
                if gamerunner.ship.life==0:
                    # if ship has no more life left,ends game with the appropriate message
                    Screen.show_message(screen, life_over_title, life_over_message)
                    Screen.end_game(screen)
                    sys.exit()
            if type(obj) is Torpedo:
                Asteroid.colide_with_torpedo(self,obj,screen,gamerunner)

    def colide_with_torpedo(self,torpedo,screen,gamerunner):
        # upon a collision with a torpedo,adds score on screen
        # and makes the asteroid to split depending on its size
        if self.size==1:
            # if size is 1,only removes the asteroid and torpedo from the game
            gamerunner.score += 100
            Screen.set_score(screen,gamerunner.score)
            Screen.unregister_torpedo(screen, torpedo)
            gamerunner.counter -= 1
            gamerunner.torpedo_list.remove(torpedo)
            Screen.unregister_asteroid(screen, self)
            gamerunner.asteroid_list.remove(self)
            return
        if self.size==3:
            gamerunner.score += 20
            Screen.set_score(screen,gamerunner.score)
            size=2
        else:
            gamerunner.score += 50
            Screen.set_score(screen,gamerunner.score)
            size=1
        # removes the original asteroid and torpedo from the game
        Screen.unregister_torpedo(screen,torpedo)
        gamerunner.torpedo_list.remove(torpedo)
        gamerunner.counter-=1
        Screen.unregister_asteroid(screen,self)
        gamerunner.asteroid_list.remove(self)
        # defines the values for the new asteroid that will be added,on the second asteroid the
        # speed will be multiplied by -1
        coord_x=self.coord_x
        coord_y = self.coord_y
        speed_x=(torpedo.speed_x+self.speed_x)/sqrt(pow(self.speed_x,2)+pow(self.speed_y,2))
        speed_y = (torpedo.speed_y + self.speed_y) / sqrt(pow(self.speed_x, 2) + pow(self.speed_y, 2))
        asteroid_1=Asteroid(coord_x,speed_x,coord_y,speed_y,size)
        asteroid_2= Asteroid(coord_x, -1*speed_x, coord_y, -1*speed_y, size)
        # add the new asteroids to the game
        gamerunner.asteroid_list.append(asteroid_1)
        gamerunner.asteroid_list.append(asteroid_2)
        Screen.register_asteroid(screen, asteroid_1, asteroid_1.size)
        Screen.register_asteroid(screen, asteroid_2, asteroid_2.size)

