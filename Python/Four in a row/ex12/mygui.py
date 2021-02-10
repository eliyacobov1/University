import tkinter as tk
from .game import Game
from .ai import AI
import os
import time

WELCOME_MSG = "FOUR IN A ROW"
PLAY_MSG = "%d it is your turn to play"

TIE_MESSAGE = "No one won, there is a tie"
WINNER = "THE WINNER IS PLAYER "

INSTRUCTIONS = "Press column button to add a disc"

HEIGHT = 6
WIDTH = 7
PLAYER_ONE = 1
PLAYER_TWO = 2
square_length = 60


def new_window(parent, function):
    """
    function that enters a new window and destroys the previous
    :param parent: root
    :param function: the number this functions gets after the user
    chose the type of the game he chose
    :return: nothing
    """
    root = tk.Tk()
    if function is 1:
        game1 = ConnectFour(root)
        game1.com_vs_com()
        auto_game_instance(game1, parent)

    if function is 2:
        game1 = ConnectFour(root)
        parent.destroy()

    if function is 3:
        game1 = ConnectFour(root)
        game1.player_vs_com()
        parent.destroy()

    if function is 4:
        game1 = ConnectFour(root)
        parent.destroy()
        game1.com_vs_player()


def main_menu(parent):
    """
    creating the main window
    :param parent: root
    :return: nothing
    """
    parent.configure(background='lavender')

    label_text = tk.Label(parent, text=WELCOME_MSG, bg="lavender",
                          fg="salmon4", font=("Helvetica", 35))
    label_text.pack()

    img = tk.PhotoImage(file=os.path.join(os.path.dirname
                                          (os.path.realpath
                                           (__file__)),
                                          "welcome.png"))
    label_img = tk.Label(parent, image=img, bg="lavender")
    label_img.image = img
    label_img.pack()

    com_vs_com = tk.Button(parent, bg="lavender", text=
    "Com VS Com",command=lambda function=1: new_window(parent,
                                                       function),
                           font=("Helvetica", 15), fg="salmon4")

    com_vs_com.pack(side=tk.BOTTOM)

    two_player_button = tk.Button(parent, bg="lavender", text=
    "Two Players", command=lambda function=2: new_window(parent,
                                                         function),
                                  font=("Helvetica", 15),
                                  fg="salmon4")

    two_player_button.pack(side=tk.BOTTOM)

    player_vs_com_button = tk.Button(parent, bg="lavender", text=
    "Player VS Com", command=lambda function=3: new_window
    (parent, function), font=("Helvetica", 15), fg="salmon4")

    player_vs_com_button.pack(side=tk.BOTTOM)

    com_vs_player_button = tk.Button(parent, bg="lavender", text=
    "Com VS Player", command=lambda function=4: new_window
    (parent, function), font=("Helvetica", 15), fg="salmon4")

    com_vs_player_button.pack(side=tk.BOTTOM)


def final_menu(parent, previous_parent, winner):
    """
    creates the final menu with the option to play again where we
    create a new game with a new parent using inner functions and
    an exit option which closes the game.
    :param parent: root to destroy
    :param previous_parent: new root for new game
    :return: nothing
    """
    def define_menu_command():
        """
        inner function that will start a new menu and close previous
        windows
        :return:nothing
        """
        clear()
        main_menu(parent)

    def define_exit_command():
        """
        defines inner function exits all windows
        :return:nothing
        """
        parent.destroy()

    def clear():
        """
        inner function to clear all widgets, if there are,and add
        the main menu widgets
        :return: nothing
        """
        play_again.destroy()
        exit.destroy()
        label_img.destroy()
        label_text.destroy()

    previous_parent.destroy()
    parent.configure(background='lavender')

    if winner == 1 or winner == 2:
        label_text = tk.Label(parent, text=WINNER + str(winner),
                              bg="lavender", fg="salmon4",
                              font=("Helvetica", 20))
        label_text.pack()

        img2 = tk.PhotoImage(file=os.path.join(os.path.dirname
                                               (os.path.realpath
                                                (__file__)),
                                               "winner %d.png" %
                                               winner))
        label_img = tk.Label(parent, image=img2, bg="lavender")
        label_img.image = img2
        label_img.pack()

    elif winner == TIE_MESSAGE:
        label_text = tk.Label(parent, text=TIE_MESSAGE,
                              bg="lavender", fg="salmon4",
                              font=("Helvetica", 20))
        label_text.pack()

        img3 = tk.PhotoImage(file=os.path.join(os.path.dirname
                                               (os.path.realpath
                                                (__file__)),
                                               "tie.png"))
        label_img = tk.Label(parent, image=img3, bg="lavender")
        label_img.image = img3
        label_img.pack()

    play_again = tk.Button(parent, text="PLAY AGAIN", command=
    lambda: define_menu_command(), font=("Helvetica", 15),
                           bg="lavender", fg="salmon4")

    play_again.pack(side=tk.BOTTOM)

    exit = tk.Button(parent, text = "EXIT GAME", command=lambda:
    define_exit_command(), font=("Helvetica", 15), bg="lavender",
                     fg="salmon4")

    exit.pack(side=tk.BOTTOM)


class ConnectFour:
    """
    a class of the moves of the game in the gui
    """
    def __init__(self, parent):
        """
        first creates new frame and canvas for the game instance
        and than the board and buttons with the column number for
        the user to press when playing
        :param parent: root
        """
        self.parent = parent
        self.frame = tk.Frame(parent)
        self.frame.grid(columnspan=7)
        self.game = Game()
        self.player1 = None
        self.player2 = None

        self.label1 = tk.Label(parent, width=30, height=1, text=
        "CONNECT FOUR", font=("Helvetica", 30), fg="salmon4",
                              bg="lavender")

        self.label1.place(x=-60, y=15)

        self.label2 = tk.Label(parent, width=30, height=1, text=
        INSTRUCTIONS, font=("Helvetica", 9), fg="#a1dbcd",
                              bg="#383a39")

        self.label2.place(x=170, y=60)

        self.canvas = tk.Canvas(self.frame, width=square_length *
        WIDTH+square_length*2, height=square_length * HEIGHT +
        square_length*2, borderwidth=5, highlightthickness=5,
                                bg='lavender')

        self.canvas.grid(columnspan=7)

        # then draw grid and create buttons which will add circles
        # to the game board
        for y in range(HEIGHT):
            for x in range(WIDTH):
                x1 = x * square_length+60
                y1 = y * square_length+90
                x2 = x1 + square_length
                y2 = y1 + square_length
                self.canvas.create_rectangle(x1, y1, x2, y2,
                                             fill="lightblue",
                                             width=2)

        column_buttons = []
        for i in range(WIDTH):
            column_buttons.append(tk.Button(self.frame, text=
            "Col %d" % int(i+1), fg="#a1dbcd", bg="#383a39",
            command=lambda col=i: self.single_turn(col)))

            column_buttons[i].grid(row=2, column="%d" % i)

    def single_turn(self, col):
        """
        checks if pc vs pc game,if so wont allow to press button
        checks if player 1 is ai,if so, makes a move
        checks if player 2 is ai,if so, makes a move
        prints win message
        :param col: column to insert disk to
        checks if there is a tie,is so,prints tie message
        :return: nothing
        """
        # checks if pc vs pc game,if so wont allow to press button
        if (type(self.player1) is AI and type(self.player2) is AI)\
                or self.game.get_winner() is not None:
            self.label.configure(text="Not eligible to make a move")
            return
        if self.game.get_current_player() == 1:
            color = 'deeppink'
        else:
            color = 'gold'

        return_value = Game.make_move(self.game, col)

        if type(return_value) is int:
            self.create_oval(col, return_value+1, color)

        # checks if player 1 is ai,if so, makes a move
        if self.game.get_current_player() == 1 and type \
                    (self.player1) is AI and \
                self.game.get_winner() is None:
            col = self.player1.find_legal_move()
            return_value = self.game.make_move(col)

            color = 'deeppink'
            self.create_oval(col, return_value+1, color)

        # checks if player 2 is ai,if so, makes a move
        if self.game.get_current_player() == 2 and type \
                    (self.player2) is AI and \
                self.game.get_winner() is None:
            col = self.player2.find_legal_move()
            return_value = self.game.make_move(col)

            color = 'gold'
            self.create_oval(col, return_value+1, color)

        if self.game.get_winner() is not None:
            # checks if there is a tie,is so,prints tie message
            if self.game.get_winner() != TIE_MESSAGE:
                # prints win message
                coordinates = self.game.get_win_coordiantes()
                self.mark_win(coordinates)

            time.sleep(1.5)
            root = tk.Tk()
            final_menu(root, self.parent, self.game.get_winner())

    def com_vs_com(self):
        """
        defines the type of the players as computer vs computer
        :return: nothing
        """
        player1 = AI(self.game, 1)
        self.player1 = player1
        player2 = AI(self.game, 2)
        self.player2 = player2

    def player_vs_com(self):
        """
        defines the type of the players as player vs computer
        :return: nothing
        """
        player2 = AI(self.game, 2)
        self.player2 = player2

    def com_vs_player(self):
        """
        defines the type of the players as computer vs player
        :return:
        """
        player1 = AI(self.game, 1)
        self.player1 = player1
        self.single_turn(self.player1.find_legal_move())

    def mark_win(self, coordinates):
        """
        adds 1-4 digits in order to mark the winning strike
        in the canvas of the board created in the gui
        :param coordinates: the winning strikes coordiantes
        according to the board in the class game
        :return: nothing
        """
        new_coordiantes = list()

        for coor in coordinates:
            new_coor = self.mark_win_helper(coor)
            new_coordiantes.append(new_coor)

        self.canvas.create_text(new_coordiantes[0], text="1",
                                font="Helvetica", fill="black")
        self.canvas.create_text(new_coordiantes[1], fill="black",
                                text="2", font="Helvetica")
        self.canvas.create_text(new_coordiantes[2], fill="black",
                                text="3", font="Helvetica")
        self.canvas.create_text(new_coordiantes[3], fill="black",
                                text="4", font="Helvetica")

        self.canvas.update()

    def mark_win_helper(self, coor):
        """
        creates the exact coordinates of the winning strike
        according to the given coordiante
        :param coor: a coordinate of the winning strike as
        in the board of the class game
        :return: the coordinate in the board
        acoording to the given ones
        """
        x1 = coor[1] * square_length + 60
        y1 = coor[0] * square_length + 90
        x2 = x1 + square_length
        y2 = y1 + square_length

        return ((x1 + x2) / 2, (y1 + y2) / 2)

    def create_oval(self,col,row,color):
        """
        creates a circle in a given coordinate and in a given color
        :param col: col number to inser disk
        :param row: row number to enter disk
        :param color: color of the disk to be created
        :return: nothing
        """
        self.canvas.create_oval(col * square_length + 60, row *
                                square_length + 90,
                                        (col * square_length + 60)
                                + square_length,
                                        (row * square_length - 30)
                                + square_length
                                        , fill=color)

        time.sleep(0.5)
        self.parent.update()


def auto_game_instance(connect_four, parent):
    """
    runs a game between two AIs
    :param connect_four: object of class ConnectFour
    :param parent: root
    :return:
    """
    parent.destroy()
    while connect_four.game.get_winner() is None:
        num = connect_four.game.get_current_player()
        if num == 1:
            player = connect_four.player1

        else:
            player = connect_four.player2

        col = player.find_legal_move()
        return_value = connect_four.game.make_move(col)+1

        if num == 1:
            color = 'deeppink'
            time.sleep(0.5)
            connect_four.parent.update()

            connect_four.create_oval(col, return_value, color)
            time.sleep(0.5)
            connect_four.parent.update()

        if num == 2:
            color = 'gold'

            connect_four.create_oval(col, return_value, color)

    if connect_four.game.get_winner() != TIE_MESSAGE:
        coordinates = connect_four.game.get_win_coordiantes()
        connect_four.mark_win(coordinates)

    time.sleep(1.5)
    root = tk.Tk()
    final_menu(root, connect_four.parent,
               connect_four.game.get_winner())
