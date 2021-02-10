
HEIGHT = 6
WIDTH = 7
UNDER_LINE = "_"

PLAYER_ONE = 1
PLAYER_TWO = 2
NO_ONE = None

ERROR_MESSAGE = "illegal move"
SUCCESS_MESSAGE = "disc moved, next player"

TIE_MESSAGE = "No one won, there is a tie"


class Game:

    def __init__(self):
        """
        the initial info of the game
        """
        self.board = [[UNDER_LINE for i in range(WIDTH)] for j in
                      range(HEIGHT)]

        self.win_coordinates = list()

    def make_move(self, column):
        """
        gets a column in which the user wants to put the disc.
        method has to assume who is the current player according
        to the games progress.also returns True when successful
        if the disc cant be put there we must raise an exception
        with the message : "illegal move"
        :param column: next column to put the disc in
        :return: failure or success message
        """
        player = self.get_current_player()

        if self.get_winner() is not None:
            raise Exception(ERROR_MESSAGE)

        try:
            # starts from the last row to the first and checks to
            # find the first empty one.
            for row_index in reversed(range(HEIGHT)):
                if self.board[0][column] != UNDER_LINE:
                    return ERROR_MESSAGE

                if self.board[row_index][column] == UNDER_LINE:
                    self.board[row_index][column] = player
                    return row_index

        except IndexError:
            return ERROR_MESSAGE

    def get_winner(self):
        """
        checks if someone won or not by using the helper functions.
        :return: if someone won it will return which player won 
        and the coordinates of the win.
        else it will returns tie or if no one won yet
        it will return none.
        """""
        in_row = self.four_in_row()
        in_col = self.four_in_col()
        in_cross = self.four_in_cross()
        complete_board = self.is_board_full()

        if in_row[0] == in_col[0] == in_cross[0] is None:
            if complete_board:
                return TIE_MESSAGE
            else:
                return None

        elif in_row[0] is not None:
            self.win_coordinates = in_row[1]
            return in_row[0]

        elif in_col[0] is not None:
            self.win_coordinates = in_col[1]
            return in_col[0]

        elif in_cross[0] is not None:
            self.win_coordinates = in_cross[1]
            return in_cross[0]

    def get_win_coordiantes(self):
        """
        returns the win coordiantes
        :return: winning strikes coordinates
        """
        return self.win_coordinates

    def four_in_row(self):
        """
        checks if there are four discs next
         to each other of the same player
        in the same row
        :return: the name of the player that won or None
        """
        who_won = (None, ())

        for x in range(HEIGHT):
            for y in range(WIDTH):
                if y + 3 < WIDTH and \
                    self.board[x][y] == self.board[x][y + 1] == \
                    self.board[x][y + 2] == self.board[x][y + 3] \
                        != UNDER_LINE:
                    who_won = (self.board[x][y], ((x, y), (x, y +
                                      1), (x, y + 2), (x, y + 3)))
                    break

        return who_won

    def four_in_col(self):
        """
        checks if there are four discs following each other
        on the same column
        :return: the name of the player that won or None
        """
        who_won = (None, ())

        for x in range(HEIGHT):
            for y in range(WIDTH):
                if (x + 3) < HEIGHT and \
                    self.board[x][y] == \
                    self.board[x + 1][y] == \
                    self.board[x + 2][y] == \
                    self.board[x + 3][y] \
                        != UNDER_LINE:
                    who_won = (self.board[x][y], ((x, y), (x + 1,
                                    y), (x + 2, y), (x + 3, y)))
                    break

        return who_won

    def four_in_cross(self):
        """
        checks if there are four discs following each other
        in a cross. turns crosses to lines ans searches in them
        :return: the name of the player that won or None
        """
        who_won = (None, ())

        for x in range(HEIGHT-3):
            for y in range(3, WIDTH):
                if self.board[x][y] == self.board[x + 1][y - 1] \
                        == self.board[x + 2][y - 2] == \
                        self.board[x + 3][y - 3] is not UNDER_LINE:
                    who_won = (self.board[x][y], ((x, y), (x + 1,
                        y - 1), (x + 2, y - 2), (x + 3, y - 3)))

        for x in range(HEIGHT-3):
            for y in range(WIDTH - 3):
                if self.board[x][y] == self.board[x + 1][y + 1] ==\
                    self.board[x + 2][y + 2] == \
                        self.board[x + 3][y + 3] is not UNDER_LINE:
                    who_won = (self.board[x][y], ((x, y), (x + 1,
                           y + 1), (x + 2, y + 2), (x + 3, y + 3)))

        return who_won

    def is_board_full(self):
        """
        checks if the board is full and there for the game ended
        :return: true if fall
        """
        for x in range(HEIGHT):
            for y in range(WIDTH):
                if self.board[x][y] == UNDER_LINE:
                    return False
        return True

    def get_player_at(self, row, col):
        """
        returns the disc of which player is on the given
        coordinates 1 for player one and 2 for player 2 or none if
        no one is there. if the location is not valid it will
        return an error message
        :param row: row in the game
        :param col: col in the game
        :return: who is in the given coordinates
        """
        try:
            if self.board[row][col] == "_":
                return None
            else:
                return self.board[row][col]

        except IndexError:
            return ERROR_MESSAGE

    def get_current_player(self):
        """
        checks which player has more discs in the board
        and decides accordingly who should make this current turn.
        :return: who is the current player
        """
        total_fills = {PLAYER_ONE: 0, PLAYER_TWO: 0, UNDER_LINE: 0}

        for row_index in range(HEIGHT):
            for col_index in range(WIDTH):
                key = self.board[row_index][col_index]
                total_fills[key] += 1

        if total_fills[PLAYER_ONE] > total_fills[PLAYER_TWO]:
            return PLAYER_TWO
        else:
            return PLAYER_ONE
