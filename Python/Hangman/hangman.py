import hangman_helper


def update_word_pattern(word, pattern, letter):
    """
     method receives the generated word, current pattern and a letter
     and returns the updated pattern (i.e if the letter is in the word and
     not in the pattern, the new pattern will include the letter)
    :param word: the word to compare the pattern against
    :param pattern: the current pattern, depends on the letters that were
     entered so far
    :param letter: the letter to be added to the pattern if included in the word
    :return: the updated pattern
    """

    lst = list(pattern)
    for n in range(len(word)):
        if word[n] == letter:
            lst[n] = letter
    return "".join(lst)


def run_single_game(words_list):
    """
    runs a single instance of the game
    :param words_list: list of words from which the game can
    choose in this instance
    """

    word = hangman_helper.get_random_word(words_list)
    pattern = ("_" * len(word))
    msg = hangman_helper.DEFAULT_MSG
    error_count = 0
    wrong_guess_lst = []
    # program starts a new,until the point when user reaches max errors or when he figures out the word
    while error_count < hangman_helper.MAX_ERRORS and pattern != word:
        hangman_helper.display_state(pattern, error_count, wrong_guess_lst, msg, ask_play=False)
        text = hangman_helper.get_input()

        if text[0] == hangman_helper.LETTER:
            if not text[1].islower() or len(text[1]) > 1:
                msg = hangman_helper.NON_VALID_MSG
                continue

            # checking if the letter was already chosen
            # (if it is in the wrong list or was already revealed in the word itself
            for n in range(len(wrong_guess_lst)):
                if text[1] == wrong_guess_lst[n]:
                    msg = hangman_helper.ALREADY_CHOSEN_MSG + text[1]
                    break

            if msg == hangman_helper.ALREADY_CHOSEN_MSG + text[1]:
                continue

            for n in range(len(pattern)):
                if pattern[n] == text[1]:
                    msg = hangman_helper.ALREADY_CHOSEN_MSG + text[1]
                    break

            if msg == hangman_helper.ALREADY_CHOSEN_MSG + text[1]:
                continue

            # check if letter is in the word and if so, use update word function on the letter
            for n in range(len(word)):
                if word[n] == text[1]:
                    pattern = update_word_pattern(word, pattern, text[1])
                    msg = hangman_helper.DEFAULT_MSG
                    break

            # else add word to wrong list and start again
            else:
                wrong_guess_lst.append(text[1])
                error_count += 1
                msg = hangman_helper.DEFAULT_MSG
        else:
            if text[0] == hangman_helper.HINT:
                msg = hangman_helper.HINT_MSG + \
                      choose_letter(filter_words_list(words_list, pattern, wrong_guess_lst),
                                    pattern)

    # end of game,user gets massage with win or loss depends on how he fared
    if word == pattern:
        msg = hangman_helper.WIN_MSG
        hangman_helper.display_state(pattern, error_count, wrong_guess_lst, msg, ask_play=True)
    else:
        msg = hangman_helper.LOSS_MSG + word
        hangman_helper.display_state(pattern, error_count, wrong_guess_lst, msg, ask_play=True)


def main():
    """
    runs the game (user can either choose to play again or exit
    after a single round)
    """
    words_list = hangman_helper.load_words(file='words.txt')
    run_single_game(words_list)
    text = hangman_helper.get_input()
    if text[1]:
        while text[1]:
            run_single_game(words_list)
            text = hangman_helper.get_input()


def filter_words_list(words, pattern, wrong_guess_lst):
    """
     method gets a pattern, a word list (words) and a list of wrong guesses
     and returns the words from the list that can match the current pattern
     considering the wrong guesses that were made
    :param words: the list of words
    :param pattern: the current pattern
    :param wrong_guess_lst:  list of wrong guesses
    :return: list of words that match the criteria described above
    """

    final_list = []
    # starts a concatenated loop,for each word in list it check the letters in the pattern
    #  and if a letter in in the wrong list
    for n in range(len(words)):

        # filters words that are not on the same length as the pattern
        if len(words[n]) == len(pattern):

            # create a variable that will turn false if there is
            # a mismatch with a certain letter between the word and the pattern
            check_if_not_matching_letter = True

            for m in range(len(pattern)):
                if pattern[m].islower:
                    if pattern[m] == (words[n])[m]:
                        continue
                    else:
                        check_if_not_matching_letter = False

            # if variable is true than we go on to next
            # check to see if word is in wrong list
            if check_if_not_matching_letter:

                # like before,we create a variable that will change to
                # false if the word is in the list
                check_if_in_wrong_lst = True
                for p in range(len(wrong_guess_lst)):
                    for l in range(len(words[n])):
                        if (words[n])[l] == wrong_guess_lst[p]:
                            check_if_in_wrong_lst = False
                            break
                    if not check_if_in_wrong_lst:
                        break

                # if the word got this far and passed all tests,
                # it is eligible to enter the final list
                if check_if_in_wrong_lst:
                    final_list.append(words[n])
    return final_list


def choose_letter(words, pattern):
    """
    method that gets a pattern and a list of words that could match that pattern
    (using the filter_words_list method), and returns the letter that appears the most
    times in the words list and also dose'nt already appear in the pattern
    letter which does not
    :param words: the list of words
    :param pattern: the pattern of letters
    :return: the letter with most appearances. if multiple letters have the same
    number of appearances, returns the first letter in the abs order.
    """

    abc_list = []
    # create abc list,the index number will represent each letter in the abc
    for n in range(26):
        abc_list.append(0)

    # create a concatenated loop to go count each
    # letter in each word in the list
    for n in range(len(words)):
        for m in range(len(words[n])):

            # i didn't manage to define letter to index function,
            # so instead,ord-97 dives the same result
            abc_list[ord((words[n])[m]) - 97] += 1

    # A variable to check which letter was most frequent,
    # and another to set the letter that will be returned
    max_letter = 0
    returned_letter = str

    for n in range(26):
        if abc_list[n] > max_letter:

            # create new variable to check if letter is in pattern
            letter_not_in_pattern = True
            for m in range(len(pattern)):
                if chr(n + 97) == pattern[m]:
                    letter_not_in_pattern = False
                    break

            # if letter is not in pattern,sets its number of times as max
            # letter and sets it as the letter that we return to the user
            if letter_not_in_pattern:
                max_letter = abc_list[n]
                returned_letter = chr(n + 97)
    return returned_letter


if __name__ == '__main__':
    hangman_helper.start_gui_and_call_main(main)
    hangman_helper.close_gui()