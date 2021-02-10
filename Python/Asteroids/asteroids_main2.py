from screen import Screen
import sys
from ship import Ship
from torpedo import Torpedo
from asteroid import Asteroid
from math import cos,sin,radians
import random

DEFAULT_ASTEROIDS_NUM = 5
asteroid_over_title = "No asteroid left"
asteroid_over_message = "Congratulations,you beat the game!"
quit_pressed_title = "Quit"
quit_pressed_message = "Bye bye!"


class GameRunner:

    def __init__(self, asteroids_amount):
        self.__screen = Screen()
        self.asteroid_list=[]
        # keeps track of score
        self.score=0
        # counts number of torpedoes that are in-game
        self.counter=0
        self.special_counter = 0
        self.torpedo_list=[]
        self.special_list = []
        self.__screen_max_x = Screen.SCREEN_MAX_X
        self.__screen_max_y = Screen.SCREEN_MAX_Y
        self.__screen_min_x = Screen.SCREEN_MIN_X
        self.__screen_min_y = Screen.SCREEN_MIN_Y
        # sets up speed and coordinates for the ship
        coord_x = random.randrange(Screen.SCREEN_MIN_X,Screen.SCREEN_MAX_X)
        speed_x = 0
        coord_y  = random.randrange(Screen.SCREEN_MIN_Y,Screen.SCREEN_MAX_Y)
        speed_y = 0
        direction=0
        self.ship = Ship(coord_x,speed_x,coord_y,speed_y,direction)
        size=3
        for add in range(asteroids_amount):
            # sets up speed and coordinates for each asteroid on each iteration of the loop
            coord_x = random.randrange(Screen.SCREEN_MIN_X, Screen.SCREEN_MAX_X)
            speed_x = random.randrange(1,4)
            coord_y = random.randrange(Screen.SCREEN_MIN_Y, Screen.SCREEN_MAX_Y)
            speed_y = random.randrange(1,4)
            # if the asteroid location is identical the the ship's location,puts new values in the variables
            # and then appends the asteroid to the asteroid list of game
            while coord_x==self.ship.coord_x and coord_y==self.ship.coord_y:
                coord_x = random.randrange(Screen.SCREEN_MIN_X, Screen.SCREEN_MAX_X)
                coord_y = random.randrange(Screen.SCREEN_MIN_Y, Screen.SCREEN_MAX_Y)
            asteroid=Asteroid(coord_x,speed_x,coord_y,speed_y,size)
            self.asteroid_list.append(asteroid)
            Screen.register_asteroid(self.__screen, asteroid, size)

    def run(self):
        self._do_loop()
        self.__screen.start_screen()

    def _do_loop(self):
        # You don't need to change this method!
        self._game_loop()

        # Set the timer to  go off again
        self.__screen.update()
        self.__screen.ontimer(self._do_loop, 5)

    def _game_loop(self):
        # Draws and moves the ship,torpedoes and the asteroids
        Screen.draw_ship(self.__screen,self.ship.coord_x,self.ship.coord_y,self.ship.direction)
        Ship.move(self.ship)
        if Screen.is_space_pressed(self.__screen):
            # adds a torpedo only kf there are less than 10
            if self.counter < 10:
                self.add_torpedo()
        if Screen.is_special_pressed(self.__screen):
            # adds a torpedo only kf there are less than 10
            if self.special_counter < 5:
                self.add_special()
        for Torpedo in self.torpedo_list:
            Torpedo.count+=1
            if Torpedo.count>=200:
                # if a torpedo has gone over the lifespan of 200 iterations,remove it
                self.torpedo_list.remove(Torpedo)
                Screen.unregister_torpedo(self.__screen,Torpedo)
                self.counter-=1
                continue
            Screen.draw_torpedo(self.__screen, Torpedo, Torpedo.coord_x, Torpedo.coord_y, Torpedo.direction)
            Torpedo.move()
        for Asteroid in self.asteroid_list:
            Screen.draw_asteroid(self.__screen,Asteroid,Asteroid.coord_x,Asteroid.coord_y)
            Asteroid.move()
            # check for collisions with any of the asteroids.if there any,removes one life if the collision
            # if it is a ship that is involved,Also removes the asteroid that was hit from the game.
            Asteroid.has_intersection(self.ship,self.__screen,self)
            # for each of the torpedoes in the game,checks if there is a collision with an asteroid.
            # if so,initiates a function which will remove and split the asteroid and torpedo depending on the case
            for Torpedo in self.torpedo_list:
                    Asteroid.has_intersection(Torpedo, self.__screen, self)
        # checks if user presses any buttons,if so,acts accordingly
        Ship.user_movements(self.ship,self.__screen)
        self.teleport()
        self.end_condition()

    def add_torpedo(self):
        # adds a torpedo to a game and screen,also arranges the values of the torpedo according
        # to the instructions.location is ship's location,speed is according to the given formula
        coord_x = self.ship.coord_x
        coord_y = self.ship.coord_y
        direction = self.ship.direction
        speed_x = self.ship.speed_x + 2 * cos(radians(self.ship.direction))
        speed_y = self.ship.speed_y + 2 * sin(radians(self.ship.direction))
        Screen.register_torpedo(self.__screen, Torpedo(coord_x,speed_x,coord_y,speed_y,direction))
        self.counter += 1
        self.torpedo_list.append(Torpedo(coord_x,speed_x,coord_y,speed_y,direction))

    def add_special(self):
        # adds a special shot to a game and screen,also arranges the values of the torpedo according
        # to the instructions.location is ship's location,speed is according to the given formula
        coord_x = self.ship.coord_x
        coord_y = self.ship.coord_y
        direction = self.ship.direction
        speed_x = self.ship.speed_x + 2 * cos(radians(self.ship.direction))
        speed_y = self.ship.speed_y + 2 * sin(radians(self.ship.direction))
        Screen.register_torpedo(self.__screen, Torpedo(coord_x,speed_x,coord_y,speed_y,direction))
        self.special_counter += 1
        self.special_list.append(Torpedo(coord_x,speed_x,coord_y,speed_y,direction).color)

    def end_condition(self):
        # checks if one of the two conditions for ending the game is met.if so,ends game.
        # the case of no life left for the ship is checked upon each asteroid collision
        if len(self.asteroid_list) == 0:
            Screen.show_message(self.__screen, asteroid_over_title, asteroid_over_message)
            Screen.end_game(self.__screen)
            sys.exit()
        if Screen.should_end(self.__screen):
            Screen.show_message(self.__screen, quit_pressed_title, quit_pressed_message)
            Screen.end_game(self.__screen)
            sys.exit()

    def teleport(self):
        # teleport the ship when the user press's t by using recursive helper function
        if Screen.is_teleport_pressed(self.__screen):
            x = random.randrange(Screen.SCREEN_MIN_X, Screen.SCREEN_MAX_X)
            y = random.randrange(Screen.SCREEN_MIN_Y, Screen.SCREEN_MAX_Y)
            self.ship.coord_x,self.ship.coord_y=self.teleport_helper(x,y)

    def teleport_helper(self,x,y):
        # helper function that will check if there is a collision with the coordinates of one
        # of the asteroids.if so,will put new values and will compare with all of the asteroid all over again.
        # returns x and y coordinates for the ship to teleport to.
        for Asteroid in self.asteroid_list:
            if Asteroid.coord_x == x and Asteroid.coord_y == y:
                x = random.randrange(Screen.SCREEN_MIN_X, Screen.SCREEN_MAX_X)
                y = random.randrange(Screen.SCREEN_MIN_Y, Screen.SCREEN_MAX_Y)
                self.teleport_helper(x,y)
        return (x,y)

    def

def main(amount):
    runner = GameRunner(amount)
    runner.run()


if __name__ == "__main__":
    if len(sys.argv) > 1:
        main(int(sys.argv[1]))
    else:
        main(DEFAULT_ASTEROIDS_NUM)
