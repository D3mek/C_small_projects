#include "c4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initialize_board(int rows, int cols, char board[rows][cols]){
    if( rows < 4 && cols < 4 ){
        rows = 4;
        cols = 4;
        printf("BOARD IS SET 4X4 CAUSE INITIALIZATION WAS SMALLER THEN 4X4\n");
    }
    for(int row=0; row<rows; row++){
        for(int col=0; col<cols; col++){
            board[row][col] = '.'; 
        }
    }
}

void print_board(int rows, int cols, const char board[rows][cols]){
    for(int i=0; i<rows; i++){
        printf(" |");
        for(int j=0; j<cols; j++){
            if( board[i][j] == 'X' ){
                printf("\e[1;96m %c \e[0m", board[i][j]);
            } else if ( board[i][j] == 'O' ){
                printf("\e[1;95m %c \e[0m", board[i][j]);
            } else {
                printf("\e[1;92m %c \e[0m", board[i][j]);
            }
            printf("|");
        }
        printf("\n");
    }
    printf(" ");
    for(int i=0; i<cols; i++){
        printf(" ---");
    }
    printf("\n");
    for(int i=0; i<cols; i++){
        printf("   %d", i+1);
    }
    printf("\n");
}

int is_valid_move(int rows, int cols, const char board[rows][cols], int col){
    int c = col - 1;
    for(int row=0; row<rows; row++){
        if( board[row][c] == '.' ){
            return 1;
        }
    }
    return 0;
}

int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece){
    int c = col - 1;
    int counter = 0;
    for(int i=0; i<rows; i++){
        if( board[i][c] != '.' ){
            if( i != 0 ){
                board[i-1][c] = player_piece;
                return i-1; // return row where piece is droped
            } else {
               return -1;
            }
        } else {
            counter++;
            if( counter == rows ){
                board[i][c] = player_piece;
                return i;
                break;
            }
        }
    }
    return -1;
}

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece){
   int char_checker = 0;
   // vertical check
   for(int y=0; y<rows; y++){
       if( board[y][col] == player_piece ){
           char_checker++;
           if( char_checker == 4 ){
              return 1; // win
           }
       } else {
           char_checker = 0;
       }
   }
   // get checker back to 0
   char_checker = 0;

   // horizontal check
   for(int x=0; x<cols; x++){
       if( board[row][x] == player_piece ){
           char_checker++;
           if( char_checker == 4 ){
               return 1; // win
           }
       } else {
           char_checker = 0;
       }
   }
   char_checker = 0; // checker back

   // diagonals check

   // anti diagonal
   int size_row = row;
   int size_col = cols - (col + 1);
   int size = (size_row < size_col) ? size_row : size_col;
   int y = row - size;
   int x = col + size;
   for(int i=0;  i<rows && i<cols; i++){
       if( y+i > rows || x-i < 0 ){
          break;
       }
       if( board[y+i][x-i] == player_piece ){
           char_checker++;
           if( char_checker == 4 ){
               return 1;
           }
       } else {
           char_checker = 0;
       }
   }
   char_checker = 0;
   
   // main diagonal
   size_row = rows - (row + 1);
   size_col = cols - (col + 1);
   size = (size_row < size_col) ? size_row : size_col;
   y = row + size;
   x = col + size;
   for(int i=0; i<rows && i<cols; i++){
        if( y-i < 0 || x-i < 0 ){
            break;
        }
        if( board[y-i][x-i] == player_piece ){
            char_checker++;
            if( char_checker == 4 ){
                return 1;
            }
        } else {
            char_checker = 0;
        }
   }

   return 0; // not connected 4
}

// check if board is full
int is_board_full(int rows, int cols, const char board[rows][cols]){
    for(int row=0; row<rows; row++){
        for(int col=0; col<cols; col++){
            if( board[row][col] == '.' ){
                return 0; // if its there some '.' then board is not full
            }
        }
    }
    return 1;
}

void connect_four(){
    int rows = 4;
    int cols = 7;
    char board[rows][cols];
    initialize_board(rows, cols, board);

    int player_turn = 1;
    int row;
    int column;
    printf("\e[0;94m +--------------------+\e[0m\n");
    printf("\e[0;94m |\e[0;93mWelcome in this game\e[0;94m|\e[0m\n");
	printf("\e[0;94m +--------------------+\e[0m\n");
    while(1){
        print_board(rows, cols, board);
        printf("\n");
        printf("Player %d, enter your move (1-%d): ", player_turn, cols);
        scanf("%d", &column);
        printf("\n");

        if( is_valid_move(rows, cols, board, column) ){
            row = drop_piece(rows, cols, board, column, (player_turn == 1) ?'X' : 'O');
        } else {
            printf("\e[0;91mYou cant place char on column %d!!!\e[0m\n", column);
            printf("\e[0;95mTry again!\e[0m\n");
            printf("\n");
            continue; // move again
        }
        
        if( check_win(rows, cols, board, row, column - 1, (player_turn == 1) ? 'X' : 'O') ){
            print_board(rows, cols, board);
            printf("\n");
            printf("\e[0;92mPlayer %d wins!\e[0m\n", player_turn);
            break;
        }
        if( is_board_full(rows, cols, board) ){
            print_board(rows, cols, board);
            printf("\n");
            printf("\e[0;92mIt's a draw!\e[0m\n");
            break;
        }
        player_turn = (player_turn == 1) ? 2 : 1;
    }
}
