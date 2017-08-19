#!/usr/bin/env python3

import cs50

#define function to print out z number of hash symbols
def print_hash(z):
    for h in range(z):
        print("#", end="")

def main():
    #initiliaze variable to capture desired height
    i = -1
    #ask for user input until it is within desired range of 0-23 inclusive
    while i < 0 or i > 23:
        i = cs50.get_int("Height: ")
    #store user input in tempory variable that can be changed
    temp = i
    #based on desired height, print leading spaces, hashes, spaces, and final hashes
    for x in range(i):
        counter = 0
        for y in range(temp - 1):#print leading spaces
            print(" ", end="")
            #keep track of how many spaces and thus support calculating how many hashes
            counter += 1
        #calculate needed number of hashes
        dif = i - counter
        #print left side of pyramid
        print_hash(dif)
        #print gap between sides of pyramid
        print("  ", end="")
        #print right side of pyramid
        print_hash(dif)
        #print newline
        print("")
        #decriment line counter
        temp -= 1

if __name__ == "__main__":
    main()