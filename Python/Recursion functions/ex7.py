import math

def print_to_n(n):
    if n==1:
        print(n)
    else:
        print_to_n(n-1)
        print(n)

def print_reversed(n):
    if n==1:
        print (1)
    else:
        print(n)
        print_reversed(n-1)

def has_devisor_smaller_than(n,i):
    # recursive function that checks if a number has a lower
    # divisor than the given number to help us write the "is_prime" function
    if i-1== 1 or n==1:
        return False
    else:
        if (n%(i-1))==0:
            return True
        return(has_devisor_smaller_than(n,i-1))

def is_prime(n):
    if has_devisor_smaller_than(n,n)==True:
        return False
    else:
        return True

def factorial(n):
    # return the ! of a certain number
    if n==0:
        return 1
    else:
        return n*factorial(n-1)

def pow(x,n):
    # recursive function,returns x in the power of n
    if x==0:
        return 0
    if n==0:
        return 1
    else:
        return x*pow(x, n-1)

def exp_n_x(n,x):
    if n==1:
        return x
    else:
        return ((pow(x,n)/factorial(n))+exp_n_x(n-1,x))


def play_hanoi(hanoi,n,src,dest,temp):
    if n <= 0:
        return
    elif n == 1:
        hanoi.move(src, dest)
    elif n == 2:
        hanoi.move(src, temp)
        hanoi.move(src, dest)
        hanoi.move(temp, dest)
    else:
        play_hanoi(hanoi, n-1, src, temp, dest)
        hanoi.move(src, dest)
        play_hanoi(hanoi, n - 1, temp, dest, src)

def print_sequences(char_list,n):
    helper_print_sequences(char_list,"",n)

def helper_print_sequences(char_list,sub,n):
    # builds all possible combinations of characters from a
    # list in the length of the given number n
    if n==0:
        print(sub)
        return

    for m in range (len(char_list)):
        new_sub=sub+char_list[m]
        helper_print_sequences(char_list,new_sub,n-1)

def print_no_repetition_sequences(char_list,n):
    helper_no_repetition_sequences(char_list,"",n)

def helper_no_repetition_sequences(char_list,sub,n):
    # builds all possible combinations of characters from a
    # list in the length of the given number n with no repetition of characters
    if n==0:
        print(sub)
        return

    for m in range (len(char_list)):
        if sub.find(char_list[m])==-1:
            new_sub=sub+char_list[m]
            helper_no_repetition_sequences(char_list,new_sub,n-1)

def parentheses(n):
    return parentheses_helper("",0,0,n,[])

def parentheses_helper(sub,close,open,n,list):
    if close==n :
        list.append(sub)
        return

    if open<n:
        parentheses_helper(sub+'(',close,open+1,n,list)

    if close<open:
        parentheses_helper(sub+')',close+1,open,n,list)

    return list

def up_and_right(n,k):
    up_and_right_helper(n,k,"",0,0)

def up_and_right_helper(n,k,sub,counter1,counter2):
    if counter1==n and counter2==k:
        print(sub)
        return
    if counter1<n:
        up_and_right_helper(n , k, sub + "r",counter1+1,counter2)
    if counter2 < k:
        up_and_right_helper(n , k, sub + "u", counter1, counter2+1)

def flood_fill(image,start):
    if (image[start[0]+1][start[1]]=='*' and image[start[0]-1][start[1]]=='*' and
        image[start[0]][start[1]-1]=='*' and image[start[0]][start[1]+1]=='*'):
        return

    if image[start[0]][start[1]]=='.':
        image[start[0]][start[1]] ='*'

    if image[start[0]+1][start[1]]=='.':
        image[start[0] + 1][start[1]] = '*'
        flood_fill(image, [start[0]+1,start[1]+1])

    if image[start[0]-1][start[1]]=='.':
        image[start[0] - 1][start[1]] = '*'
        flood_fill(image, [start[0]-1,start[1]])

    if image[start[0]][start[1]+1]=='.':
        image[start[0]][start[1] + 1] = '*'
        flood_fill(image, [start[0],start[1]+1])

    if image[start[0]][start[1]-1]=='.':
        image[start[0]][start[1] - 1] = '*'
        flood_fill(image, [start[0],start[1]-1])

if __name__ == '__main__':
    list=['q','q']
    print_sequences(list,1)