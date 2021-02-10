import wordsearch

# I chose the function u_search that finds words from words_list
# in the direction up that are in the matrix


def check_u_search():
    a = True
    b = True
    matrix_identical_letter = []
    for n in range(5):
        matrix_identical_letter.append([])
        for m in range(5):
            matrix_identical_letter[n].append("A")
    lst_B = list(['A', 'A', 'A'])
    if wordsearch.u_search == ['A', 'A', 'A', 15]:
        a = True
    else:
        a = False

    empty_matrix = []
    lst_b = list(['B', 'B', 'B'])
    if not wordsearch.u_search(lst_b, empty_matrix):
        b = True
    else:
        b = False

    if a and b:
        return True
    else:
        return False


if __name__ == '__main__':
    check_u_search()




