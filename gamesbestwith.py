#!/usr/bin/env python3

import os
import sys

def main():

    # ensure proper usage
    if len(sys.argv) != 3:
        sys.exit("Usage: ./gamesbestwith playercount game_collection")

    playercount = sys.argv[1]

    # absolute path to file
    user_collection = os.path.join(sys.path[0], sys.argv[2])

    # verify file can be found
    if not os.path.isfile(user_collection):
        raise sys.exit("Invalid game_collection!")

    # setup container for input file
    games = []

    # read in lines from input file
    with open(user_collection) as collection:
        for line in collection:
            games.append(line)

    # initialize counter for games matching criteria
    count = 0

    # get each line/game into normalized state and then find matches
    for game in games:
        game_data = game.split('\t')
        game_data = [item.strip('"\n') for item in game_data]
        if len(game_data) < 14:
            #print(game_data)
            dif = 14 - len(game_data)
            for i in range(0, dif):
                game_data.append("")
            #print(game_data)
        best_player_count = game_data[13].split(",")

        if playercount in best_player_count:
            print("Name: {}\nBest with {} players\nSupports {}-{} players\nPlaying time: {}".format(
                game_data[0],
                game_data[13],
                game_data[6],
                game_data[7],
                game_data[8]))
            print("For more information see: https://boardgamegeek.com/boardgame/{}".format(game_data[1]))
            print("**********************************************")
            count += 1

    if count == 1:
        print("{} game matches your player count.".format(count))
    else:
        print("{} games match your player count.".format(count))

if __name__ == "__main__":
    main()
