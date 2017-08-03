/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// blank tile coordinates. Row of blank (rb) and column of blank (cb).
int rb, cb;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();
        
        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(250000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    //initialize highest number to be on the board
    int high = (d * d) - 1;
    
    //iterate through all spaces of board and set the value in descending order
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            //set tile's value
            board[i][j] = high;
            high--;
        }
    }
    
    //check if baord dimemsions are even (odd number of tiles)
    if (d % 2 == 0)
    {
        //switch values 1 and 2
        board[d-1][d-3] = 1;
        board[d-1][d-2] = 2;
        
    }
    
    rb = d - 1;
    cb = d - 1; 
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    //iterate over array and print the board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            //if blank tile, print '_'.  Otherwise, print tile's value
            if(board[i][j] == 0)
            {
                printf(" _ ");
            }
            else
            {
                printf("%2i ", board[i][j]);
            }
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    //setup variables to hold coordinates for tile. Row of tile (rt) and column of tile (ct).
    int rt, ct;
    //find value of tile in board.
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            //check for location of tile
            if(board[i][j] == tile)
            {
                rt = i;
                ct = j;
                break;
            }
        }
    }
    //check to see if it is valid to move.  If so, swap tile and blank.
    if ((rb == rt  && (cb == ct - 1 || cb == ct + 1)) || (cb == ct && (rb == rt - 1 || rb == rt + 1)))
    {
        board[rb][cb] = board[rt][ct];
        board[rt][ct] = 0;
        
        //update blank location
        rb = rt;
        cb = ct;
        
        return true;
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    //initialize value counter to check against
    int value = 1;
    //iterate over board and check for any values still in the wrong place
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if(i != d - 1 || j != d - 1)//make sure not last spot in board, since it should be 0 instead of d * d
            {
                if(board[i][j] != value)
                {
                    return false;
                }
            }
            value++;
        }
    }
    
    return true;
}
