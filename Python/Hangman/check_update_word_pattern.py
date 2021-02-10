import hangman

def test():
    ##variable that stays true as long as tests pass
    status=True
    if(hangman.update_word_pattern("aaaa","_"*4,'a'))=="a"*4:
        status = True
    else:
        status=False

    if (hangman.update_word_pattern("a", "_" , 'a')) == "a":
        status = True
    else:
        status = False

    if (hangman.update_word_pattern("aaab", "_" * 4, 'a')) == "aaa_":
        status=True
    else:
        status = False

    if (hangman.update_word_pattern("aaaaaaaaaaaaaaaaaaaaaaaaa", "_" * 25, 'a')) == "a"*25:
        status=True
    else:
        status = False

    if status==True:
        print("Function ","update_word_pattern", " test success")
        return status
    else:
        print("Function ", "update_word_pattern", " test fail")
        return status

if __name__ == '__main__':
    test()


