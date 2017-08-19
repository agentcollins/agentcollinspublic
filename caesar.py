#!/usr/bin/env python3

import cs50

from sys import argv

#define function to shift characters in the alphabet by a given number of places
def alpha_shift(c, i):
    #intialize for lower case
    x = 97
    #check for uppercase and adjust as needed
    if c.isupper():
        x = 65
    #get the unicode value of the character
    co = ord(c)
    #shift the unicode value by the number of places desired and change it back to a char
    c = chr(x + ((co - x + i) % 26))
    return c

def main():
    #validate proper number of arguments are passed in storing the cipher shift value if it is passed in
    if len(argv) != 2:
        print("Usage: ./caesar k")
        return 1
    else:
        k = int(argv[1])

    #get string from user
    text = cs50.get_string("plaintext: ")
    #setup new cipher version of the string
    cipher_text = ""
    #iterate over each char
    for char in text:
        #check for alpha characters
        if char.isalpha():
            #then shift only alpha chars based on cipher argument
            cipher_text += alpha_shift(char, k)
        else:
            #if not alpha char, then pass to cipher text unchanged
            cipher_text += char
    #print cipher text
    print("ciphertext: {}".format(cipher_text))

if __name__ == "__main__":
    main()