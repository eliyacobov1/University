import math
import wave_helper
import numpy as np
import scipy

max_volume = 32767
min_volume = -32768
sample_rate = 2000
f_A = 440
f_B = 494
f_C = 523
f_D = 587
f_E = 659
f_F = 698
f_G = 784
Q = 0

MAIN_MENU = "Choose the desired action by entering its #number:\n#1" \
            " Change wav file \n#2 Combine two wav files\n#3 Compose" \
            " melody for wav format\n#4 Exit program\n\nEnter your input here:"

READ_ERROR = "Error while reading file, please re-enter file name:\n"

INVALID_NUM = "Invalid input!\n\nPlease enter a number between #1-#6:\n"

CHANGE_FILE = "Choose the desired action by entering its #number:\n#1" \
              " Reverse audio \n#2 Speed up audio\n #3 Slow down audio\n" \
              "#4 Volume up\n#5 Volume down\n#6 Dimming filter\nEnter your input here: "


class wav_file:
    """
    Class for a wave file representation
    """

    # create a class that represents a wav_file to access the data more easily
    def __int__(self, frame_rate, audio_data, name):
        self.frame_rate = frame_rate
        self.audio_data = audio_data
        self.name = name


def start_menu():
    """
    The main menu of the program
    """

    user_input = input("Welcome! " + MAIN_MENU)
    if user_input != '4':

        while user_input != '1' and user_input != '2' and user_input != '3' and user_input != '4':
            user_input = input("Invalid input!\n\nPlease enter a number between #1-#4:\n")

        if user_input == '1':
            change_file(get_file())

        if user_input == '2':
            combine_files()

        if user_input == '3':
            instructions_txt = input("Enter path of instruction file for melody composition:")
            compose_melody(instructions_txt)
    else:
        return


def get_file():
    """
    Creates a new wav_file object using the input data
    :return: The newly created wav_file object
    """

    file_name = input("Please enter the wav file name: ")
    while wave_helper.load_wave(file_name) == -1:
        file_name = input(READ_ERROR)
    frame_rate, audio_data = wave_helper.load_wave(file_name)
    file_name1 = wav_file()
    file_name1.frame_rate, file_name1.audio_data, file_name1.name = frame_rate, audio_data, file_name

    return file_name1


def change_file(wavfile):
    """
    The menu for the change file functionality
    :param wavfile: The file to be manipulated
    """

    action_num = input(CHANGE_FILE)
    while (action_num != '1' and action_num != '2' and action_num != '3' and action_num != '4'
           and action_num != '5' and action_num != '6'):
        action_num = input(INVALID_NUM)

    if action_num == '1':
        # reverse the audio
        copy_audio_data = wavfile.audio_data
        copy_audio_data.reverse()
        wavfile.audio_data = copy_audio_data

    if action_num == '2':
        # speeding up audio
        print(len(wavfile.audio_data))
        updated_audio_data = []
        for n in range(len(wavfile.audio_data)):
            if n % 2 == 0:
                updated_audio_data.append(wavfile.audio_data[n])
        wavfile.audio_data = updated_audio_data

    if action_num == '3':
        # slowing audio
        # create copy of audio data and compare each value in  the list in order to insert new
        # values only between the original values of the list
        copy_audio_data = wavfile.audio_data
        m = 0
        for n in range(len(wavfile.audio_data) - 1):
            if wav.audio_data[n] == copy_audio_data[m]:
                wavfile.audio_data.insert(n + 1, [int((wavfile.audio_data[n][0] +
                                                       wavfile.audio_data[n + 1][0]) / 2)
                    , int((wavfile.audio_data[n][1] +
                           wavfile.audio_data[n + 1][1]) / 2)])
                m += 1

    if action_num == '4':
        # powering up volume
        for _list in wavfile.audio_data:
            # updating the first value in each sub-list
            if _list[0] * 1.2 < min_volume:
                _list[0] = min_volume
            else:
                if _list[0] * 1.2 > max_volume:
                    _list[0] = max_volume
                else:
                    _list[0] = int(_list[0] * 1.2)

            # updating the second value in each sub-list
            if _list[1] * 1.2 < min_volume:
                _list[1] = min_volume
            else:
                if _list[1] * 1.2 > max_volume:
                    _list[1] = max_volume
                else:
                    _list[1] = int(_list[1] * 1.2)

    if action_num == '5':
        # lowering volume
        for _list in wavfile.audio_data:
            # updating the first value in each sub-list
            _list[0] = int(_list[0] / 1.2)
            # updating the second value in each sub-list
            _list[1] = int(_list[1] / 1.2)

    if action_num == '6':
        # dimming
        copy_audio_data = wavfile.audio_data
        for n in range(len(wavfile.audio_data)):
            # for the first value in the last
            if n == 0:
                wavfile.audio_data[n][0] = int((copy_audio_data[n][0] +
                                                copy_audio_data[n + 1][0]) / 2)

                wavfile.audio_data[n][1] = int((copy_audio_data[n][1] +
                                                copy_audio_data[n + 1][1]) / 2)

            # for the last value in the list
            if n == len(wavfile.audio_data) - 1:
                wavfile.audio_data[len(wav.audio_data) - 1][0] = \
                    int((copy_audio_data[len(wavfile.audio_data) - 1][0] +
                         copy_audio_data[len(wavfile.audio_data) - 2][0]) / 2)

                wavfile.audio_data[len(wavfile.audio_data) - 1][1] = \
                    int((copy_audio_data[len(wavfile.audio_data) - 1][1] +
                         copy_audio_data[len(wavfile.audio_data) - 2][1]) / 2)

            if n != 0 and n != len(wavfile.audio_data) - 1:
                # for every other value in the list
                wavfile.audio_data[n][0] = int(
                    (copy_audio_data[n - 1][0] + copy_audio_data[n][0] +
                     copy_audio_data[n + 1][0]) / 3)

                wavfile.audio_data[n][1] = int(
                    (copy_audio_data[n - 1][1] + copy_audio_data[n][1] +
                     copy_audio_data[n + 1][1]) / 3)

    transition_menu(wavfile)


def transition_menu(wav):
    """
    transition menu for option #4
    :param wav: The file which we manipulated
    """
    action_num = input(MAIN_MENU)
    while action_num != '1' and action_num != '2':
        action_num = input(INVALID_NUM)

    if action_num == '1':
        file_name = input("Please enter the wav file name in which the audio will be saved:\n")
        while wave_helper.save_wave(wav.frame_rate, wav.audio_data, file_name) != 0:
            file_name = input("Invalid input!\nPlease re-enter the file name (String type):\n ")
        if wave_helper.save_wave(wav.frame_rate, wav.audio_data, file_name) == 0:
            print("\n")
            start_menu()

    if action_num == '2':
        change_file(wav)


def combine_files():
    """
    Function that combines files by loading the
    data into two wav_file type objects
    """

    wav1 = wav_file()
    wav2 = wav_file()
    files_names = input("Type the paths of the files that you would like to merge. "
                        "\nEnter your input here:")
    wav1.name, wav2.name = files_names.split(" ")
    if wave_helper.load_wave(wav1.name) == -1 or wave_helper.load_wave(wav2.name) == -1:
        while wave_helper.load_wave(wav1.name) == -1 or wave_helper.load_wave(wav2.name) == -1:
            files_names = input("There was a problem,try again:")
            wav1.name, wav2.name = files_names.split(" ")

    wav1.frame_rate, wav1.audio_data = wave_helper.load_wave(wav1.name)
    wav2.frame_rate, wav2.audio_data = wave_helper.load_wave(wav2.name)
    return_audio_list = []

    if wav1.frame_rate != wav2.frame_rate:
        if wav1.frame_rate < wav2.frame_rate:
            wav_max = wav2
            wav_min = wav1
        else:
            wav_max = wav1
            wav_min = wav2
        x = int(wav_min.frame_rate / (math.gcd(wav_min.frame_rate, wav_max.frame_rate)))
        y = int(wav_max.frame_rate / (math.gcd(wav_min.frame_rate, wav_max.frame_rate)))
        counter = 0

        if len(wav_max.audio_data) >= len(wav_min.audio_data):
            for n, m in wav_max.audio_data:
                if counter == y:
                    counter = 0
                if counter < x and n < len(wav_min.audio_data):
                    return_audio_list.append([int((wav_min.audio_data[n][0] + wav_max.audio_data[m][0]) / 2),
                                              int((wav_min.audio_data[n][1] + wav_max.audio_data[m][1]) / 2)])
                else:
                    if counter < x:
                        return_audio_list.append([wav_max.audio_data[m][0], wav_max.audio_data[m][1]])
                if x <= counter:
                    while counter < y:
                        m += 1
                        counter += 1
                if counter != y:
                    counter += 1

        else:
            for n, m in wav_min.audio_data:
                if counter == y:
                    counter = 0
                if counter < x and m < len(wav_max.audio_data):
                    return_audio_list.append([int((wav_min.audio_data[n][0] + wav_max.audio_data[m][0]) / 2),
                                              int((wav_min.audio_data[n][1] + wav_max.audio_data[m][1]) / 2)])
                else:
                    return_audio_list.append([wav_min.audio_data[m][0], wav_min.audio_data[m][1]])
                if x <= counter:
                    while counter < y:
                        m += 1
                        counter += 1
                if counter != y:
                    counter += 1
                # if the frame rates are equal
    else:
        if len(wav1.audio_data) != len(wav2.audio_data):
            if len(wav1.audio_data) < len(wav2.audio_data):
                wav_max = wav2
                wav_min = wav1
            else:
                wav_max = wav1
                wav_min = wav2
        else:
            wav_max = wav1
            wav_min = wav2
        for n in range(len(wav_max.audio_data)):
            if n < len(wav_min.audio_data):
                return_audio_list.append([int((wav_min.audio_data[n][0] + wav_max.audio_data[n][0]) / 2),
                                          int((wav_min.audio_data[n][1] + wav_max.audio_data[n][1]) / 2)])
            else:
                return_audio_list.append([wav_max.audio_data[n][0], wav_max.audio_data[n][1]])

    return_wav = wav_file()
    return_wav.audio_data, return_wav.frame_rate = return_audio_list, min(wav1.frame_rate, wav2.frame_rate)
    print(return_audio_list)
    transition_menu(return_wav)


def compose_melody(instructions_txt):
    """
    Function for melody composition that uses
    the provided instructions text
    :param instructions_txt: Includes instructions
    on exactly how to manipulate the melody
    """
    _str = ""
    frequency = int()
    return_wav = wav_file()
    return_list = []
    return_wav.frame_rate = sample_rate
    with open(instructions_txt) as f:
        _str = f.read()
    for n in range(len(_str)):
        if str[n] == ('A' or 'B' or 'C' or 'D' or 'E' or 'F' or 'G'):
            if _str[n] == 'A':
                frequency = f_A
            if _str[n] == 'A':
                frequency = f_B
            if _str[n] == 'B':
                frequency = f_C
            if _str[n] == 'C':
                frequency = f_D
            if _str[n] == 'D':
                frequency = f_E
            if _str[n] == 'E':
                frequency = f_E
            if _str[n] == 'F':
                frequency = f_F
            if _str[n] == 'G':
                frequency = f_G
            for m in range(int(_str[n + 2]) * 125):
                return_list.append([int(max_volume * math.sin(math.pi * 2 * m * (frequency / sample_rate)))
                                       , int(max_volume * math.sin(math.pi * 2 * m * (frequency / sample_rate)))])

    return_wav.audio_data = return_list
    transition_menu(return_wav)


if __name__ == '__main__':
    start_menu()
