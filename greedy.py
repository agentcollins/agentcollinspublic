#!/usr/bin/env python3

import cs50

def main():
    #initialize float variable
    f = -0.1
    print("O hai!", end="")
    #loop asking for user input until postive value received
    while f < 0:
        f = cs50.get_float("How much change is owed? ")

    #intialize change variable to a whole number rounded
    change = round(f*100)
    #intitialize coin counting variable
    count = 0
    #iterative over change counting how many coints, starting at the largest, can be used
    while change > 0:
        while change >= 25:#check if a quarter can be used
            count += 1#if so, increase coin count
            change -= 25# and decrease overall value to check against
        while change >= 10:#repeat proces for dimes
            count += 1
            change -= 10
        while change >= 5:#repeat process for nickels
            count += 1
            change -= 5
        while change >=1:#repeat process for pennies
            count += 1
            change -= 1

    #display number of coins used
    print(count)


if __name__ == "__main__":
    main()