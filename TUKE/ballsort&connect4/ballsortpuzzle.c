#include <stdio.h>
#include <stdlib.h> 
#include "ballsortpuzzle.h"
#include <time.h>
#include <string.h>
#include <stdbool.h>

void generator(const int rows, const int columns, char field[rows][columns]) {
    srand(time(NULL));
    
    // generate 2 indexs for ran. empty columns
    int empty1 = rand() % columns;
    int empty2 = rand() % columns;
    while(empty1 == empty2){
   	 empty2 = rand() % columns;
    }

    int numChars = columns - 2;
    // prepare first random char
    const int min = 33;
    const int max = 44;
    const int range = max - min + 1;
    int random_index = rand() % range;
    char random_char = (char)(min + random_index);
    
    // prepare another ran. chars and fill array with them
    int counter = 0;
    char chars_to_use[rows * numChars];
    for(int i=0; i < numChars; i++){
        char r_char = (char)((int)random_char + i);
        for(int j=0; j<rows; j++){
            chars_to_use[counter] = r_char;
            counter++;
        }
    }
    chars_to_use[counter] = '\0';

    // fill field array with chars from chars_to_use array
    for(int col = 0; col < columns; col++){
        for(int row = 0; row < rows; row++){
            if( col == empty1 || col == empty2 ) {
               field[row][col] = ' ';
               continue;
            }
            // add char to col.
            int r_index = rand() % strlen(chars_to_use);
            field[row][col] = chars_to_use[r_index];

            // remove char from array by his index
            for(int i=r_index; i<strlen(chars_to_use); i++){
                chars_to_use[i] = chars_to_use[i+1];
            }
        }
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y){
    char char_to_move;
    int i_char;
    x--; // in. 3 = 2 ex.
    y--; // in. 4 = 3 ex.
    if( x != y ){
        if( x <= columns && y <= columns ){
            // find char which we want move
            for(int i=0; i<rows; i++){
                if( field[i][x] != ' ' ){
                    char_to_move = field[i][x];
                    i_char = i;
                    break;
                }
            }

            // move char
            int s_counter = 0;
            for(int i=0; i<rows ; i++){
                // find first char in col.
                if( field[i][y] != ' ' ){
                    if( i != 0 ){ // check if first char == char_to_move
                        if( field[i][y] == char_to_move ){ // check if col. is full
                            field[i_char][x] = ' '; // remove char
                            field[i-1][y] = char_to_move; // add char
                            break;
                        } else {
                            printf("\e[0;91m   MUST BE SAME\e[0m\n");
                            break;
                        }
                    } else {
                        printf("\e[0;91m   COLUMN IS FULL! : %d\e[0m\n", y+1);
                        break;
                    }
                } else {
                    s_counter++; // counter for col. if its empty  
                    // check end of column
                    if( s_counter == rows ){
                        // prevent move from emp(ty col.
                        if( (int)char_to_move != 0 ){
                            field[i_char][x] = ' '; // remove char
                            field[i][y] = char_to_move; // add char
                            break;
                        } else {
                            printf("\e[0;91m   CANT MOVE FROM EMPTY COLUMN!\e[0m\n");
                            break;
                        }
                    }
                }
            }
        } else {
            printf("\e[0;91m   INPUTS OVERFLOW COLUMNS!\e[0m\n");
        }
    } else {
        printf("\e[0;91m   COLUMNS CANT BE SAME!\e[0m\n");
    }
}

// check column layout
bool check(const int rows, const int columns, char field[rows][columns]){
    char to_check;
    for(int col=0; col<columns; col++){
        to_check = field[0][col];
        for(int row=0; row<rows; row++){
            if( field[row][col] != to_check ){
                return false;
            }
        }
    }
    return true;
}

// print field
void game_field(const int rows, const int columns, char field[rows][columns]){
    for(int i = 0; i < rows; i++) {
    	printf("  %d ", i+1);
    	printf("|");
    	for(int j = 0; j < columns; j++) {
            printf(" %c ", field[i][j]);
            printf("|");
    	}
        printf("\n");
    }
    printf("    ");
    printf("+---");
    for(int i=0; i<columns-1; i++){
    	printf("+---");
    }
    printf("+");
    printf("\n");
    printf("   ");
    for(int i=0; i<columns; i++){
    	printf("   %d", i+1);
    }
    printf("\n");
}

// PLAY
void ball_sort_puzzle(){
   int rows = 6;
   int columns = 5;
   char field[rows][columns];
   generator(rows, columns, field);
   
   int x;
   int y;
   printf("\e[1;96m---------------------------\e[0m\n");
   printf("\e[1;95mWelcome in this puzzle game\e[0m\n");
   printf("\e[1;96m---------------------------\e[0m\n");
   while( true ){
        if( !check(rows, columns, field) ){
            game_field(rows, columns, field);
            printf("Enter what: ");
            scanf("%d", &x);
            printf("Enter where: ");
            scanf("%d", &y);
            down_possible(rows, columns, field, x, y);
        } else {
            game_field(rows, columns, field);
            printf("\e[1;92m      ->>YOU WON<<-\e[0m\n");
            break;
        }
   }
}
