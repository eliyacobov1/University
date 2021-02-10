import random

PLAYER_ONE = 1
PLAYER_TWO = 2
UNDER_LINE = "_"

HEIGHT = 6
WIDTH = 7

ERROR_MESSAGE = "No possible AI moves"
WRONG_PLAYER = "Wrong player"


class AI:

    def __init__(self, game, player):
        """
        initial info
        :param game: game from class Game
        :param player: the number of the player the
        # computer is playing for.
        """
        self.game = game
        self.player = player

    def find_legal_move(self):
        """
        checks for a column with an empty disc and returns it
        if game is over - returns error message
        :return: column number
        """
        game_over = self.game.get_winner()
        if game_over is not None:
            raise Exception(ERROR_MESSAGE)

        cur_player = self.game.get_current_player()

        if cur_player != self.player:
            raise Exception(WRONG_PLAYER)

        if cur_player == PLAYER_ONE:
            next_player = PLAYER_TWO
        else:
            next_player = PLAYER_ONE

        # checks if current player can make a move that might
        # help him win
        if self.three_in_col(cur_player) < 7:
            return self.three_in_col(cur_player)

        elif self.three_in_row(cur_player) < 7:
            return self.three_in_row(cur_player)

        elif self.three_in_cross(cur_player) < 7:
            return self.three_in_cross(cur_player)

        # if couldn't find a way to win, checks if it might be
        # able to prevent the next player from winning:
        elif self.three_in_col(next_player) < 7:
            return self.three_in_col(next_player)

        elif self.three_in_row(next_player) < 7:
            return self.three_in_row(next_player)

        elif self.three_in_cross(next_player) < 7:
            return self.three_in_cross(next_player)

        # else moves randomly:
        else:
            return self.legal_helper()

    def legal_helper(self):
        """
        uses random for a possible col number and checks if that
        column is not full. if the column is full
        the function calls itself it finds a possible column
        :return: possible column
        """
        col = random.randint(0, WIDTH - 1)

        if self.game.get_player_at(0, col) is None:
            return col
        else:
            return self.legal_helper()

    def three_in_col(self, player):
        """
        checks if there is a possible win in the board.
        if so, returns where for the player to put a disc there
        and win or prevent the other player from winning.
        :param player: current player or rival player
        :return: possible column
        """
        column = 7
        for x in range(HEIGHT):
            for y in range(WIDTH):
                if (x + 3) < HEIGHT:
                    if self.game.get_player_at(x + 1, y) == \
                        self.game.get_player_at(x + 2, y) == \
                        self.game.get_player_at(x + 3, y) == player\
                        and self.game.get_player_at(x, y) \
                            is None:
                        column = y
                        break

        return column

    def three_in_row(self, player):
        """
        checks if there is a possible win in the board.
        if so, returns where for the player to put a disc there
        and win or prevent the other player from winning.
        :param player: current player or rival player
        :return: possible column
        """
        column = 7
        for x in range(HEIGHT):
            for y in range(WIDTH):
                if (y + 3) < WIDTH:
                    if self.game.get_player_at(x, y + 1) == \
                        self.game.get_player_at(x, y + 2) == \
                        self.game.get_player_at(x, y) == player\
                        and self.game.get_player_at(x, y + 3) \
                            is None and self.game.get_player_at\
                                (x + 1, y + 3) is not None:
                        column = y + 3
                        break

                    elif self.game.get_player_at(x, y) == \
                        self.game.get_player_at(x, y + 1) == \
                        self.game.get_player_at(x, y + 3) == player\
                            and self.game.get_player_at(x, y + 2) \
                            is None and self.game.get_player_at \
                                (x + 1, y + 2) is not None:
                        column = y + 2
                        break

                    elif self.game.get_player_at(x, y) == \
                        self.game.get_player_at(x, y + 2) == \
                        self.game.get_player_at(x, y + 3) == player\
                            and self.game.get_player_at(x, y + 1) \
                            is None and self.game.get_player_at \
                                (x + 1, y + 1) is not None:
                        column = y + 1
                        break

                    elif self.game.get_player_at(x, y + 1) == \
                        self.game.get_player_at(x, y + 2) == \
                        self.game.get_player_at(x, y + 3) == player \
                            and self.game.get_player_at(x, y) \
                            is None and self.game.get_player_at \
                                (x + 1, y) is not None:
                        column = y
                        break

        return column

    def three_in_cross(self, player):
        """
        checks if there is a possible win in the board.
        if so, returns where for the player to put a disc there
        and win or prevent the other player from winning.
        :param player: current player or rival player
        :return: possible column
        """
        column = 7
        for x in range(HEIGHT-3):
            for y in range(3, WIDTH):
                if self.game.get_player_at(x, y) == \
                    self.game.get_player_at(x + 1, y - 1) == \
                    self.game.get_player_at(x + 2, y - 2) == player \
                    and self.game.get_player_at(x + 3, y - 3)\
                        is None and self.game.get_player_at\
                            (x + 4, y - 3) is not None:
                    column = y - 3
                    break

                elif self.game.get_player_at(x, y) == \
                    self.game.get_player_at(x + 1, y - 1) == \
                    self.game.get_player_at(x + 3, y - 3) == player \
                    and self.game.get_player_at(x + 2, y - 2)\
                        is None and self.game.get_player_at\
                            (x + 3, y - 2) is not None:
                    column = y - 2
                    break

                elif self.game.get_player_at(x, y) == \
                    self.game.get_player_at(x + 2, y - 2) == \
                    self.game.get_player_at(x + 3, y - 3) == player \
                    and self.game.get_player_at(x + 1, y - 1)\
                        is None and self.game.get_player_at\
                            (x + 2, y - 1) is not None:
                    column = y - 1
                    break

                elif self.game.get_player_at(x + 1, y - 1) == \
                    self.game.get_player_at(x + 2, y - 2) == \
                    self.game.get_player_at(x + 3, y - 3) == player \
                    and self.game.get_player_at(x, y)\
                        is None and self.game.get_player_at\
                            (x + 1, y) is not None:
                    column = y
                    break
            return column

        for x in range(HEIGHT-3):
            for y in range(WIDTH - 3):
                if self.game.get_player_at(x, y) == \
                    self.game.get_player_at(x + 1, y + 1) == \
                    self.game.get_player_at(x + 2, y + 2) == player \
                    and self.game.get_player_at(x + 3, y + 3)\
                        is None and self.game.get_player_at\
                            (x + 4, y + 4) is not None:
                    column = y + 3
                    break

                elif self.game.get_player_at(x, y) == \
                    self.game.get_player_at(x + 1, y + 1) == \
                    self.game.get_player_at(x + 3, y + 3) == player \
                    and self.game.get_player_at(x + 2, y + 2)\
                        is None and self.game.get_player_at\
                            (x + 3, y + 2) is not None:
                    column = y + 2
                    break

                elif self.game.get_player_at(x, y) == \
                    self.game.get_player_at(x + 3, y + 3) == \
                    self.game.get_player_at(x + 2, y + 2) == player \
                    and self.game.get_player_at(x + 1, y + 1)\
                        is None and self.game.get_player_at\
                            (x + 2, y + 1) is not None:
                    column = y + 1
                    break

                elif self.game.get_player_at(x + 1, y + 1) == \
                    self.game.get_player_at(x + 3, y + 3) == \
                    self.game.get_player_at(x + 2, y + 2) == player \
                    and self.game.get_player_at(x, y)\
                        is None and self.game.get_player_at\
                            (x + 1, y) is not None:
                    column = y
                    break

        return column

    def get_last_found_move(self):
        pass
