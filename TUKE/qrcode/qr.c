#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// encode char to byte
void encode_char(const char character, bool bits[8]){
    int char_to_en = (int)character; // dec. number from ASCII
    for(int i=7; i>=0; i--){
        bits[i] = char_to_en % 2; // 1 or 0
        char_to_en = char_to_en / 2; // devide for next 1,0
    }
}

// decode byte to char
char decode_byte(const bool bits[8]){
    int table[8] = {1,2,4,8,16,32,64,128}; // table of numbers to change binary to dec.
    int char_to_get = 0; // dec. number to get from ASCII
    
    int count = 0;
    for(int i=7; i>=0; i--){ // logic of converting
        if( bits[i] ){
           char_to_get += table[count];  
        }
        count++;
    }
    return (char)char_to_get;
}

// string to bytes
void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
    bool bits[8];
    for(int row=0; row<strlen(string)+1; row++){
        encode_char(string[row], bits);
        for(int col=0; col<8; col++){
            bytes[row][col] = bits[col];
        }   
    }
}

// decode bytes to string
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]){
    for(int row=0; row<rows; row++){
        char d_char = decode_byte(bytes[row]); // decode byte to dec and then to char
        string[row] = d_char;
    }
}

// bytes to blocks -- horizontal to vertical
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int index_block = 0;
    int index_byte = 0;
    int counter = 0;
    for(int row=0; row<offset; row++){
        for(int col=0; col<cols; col++){
            counter++;
            for(int i=0; i<8; i++){
                if( rows < counter ){
                    blocks[index_block + i][col] = 0;
                    continue; // continue adding 0
                }
                blocks[index_block + i][col] = bytes[index_byte][i];
            }
            index_byte++;
        }
        index_block += 8;
    }
}

// blocks to bytes --  vertical to horizontal
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int index_block = 0;
    int index_byte = 0;
    int counter = 0;
    for(int row=0; row<offset; row++){
        for(int col=0; col<cols; col++){
            counter++;
            for(int i=0; i<8; i++){
                if( rows < counter ){
                    return; // end function
                }
                bytes[index_byte][i] = blocks[index_block + i][col];
            }
            index_byte++;
        }
        index_block += 8;
    }
}

// main function
int main(void){
    /*bool bits[8];
    encode_char('B', bits);
    for(int i=0; i<8; i++){
        printf("%d", bits[i]);
    }
    printf("\n");

    //bool bits2[8] = {0,1,0,0,0,0,0,1};
    printf("%c\n", decode_byte(bits) );

    char* text = "Hello, how are you?";
    const int len = strlen(text) + 1;
    bool bytes[len][8];
    encode_string(text, bytes);
    for(int j=0; j<= len; j++){
        printf("%c:", text[j]);
        for(int i=0; i<8; i++){
            printf("%d", bytes[j][i]);
        }
        printf("\n");
    }

    char string[len];
    decode_bytes(len, bytes, string);
    printf("%s\n", string);

    int length = 4+1, cols = 3, offset = 2;
    bool bytes[4+1][8] = { 
        {0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,0,0},
        {0,1,1,0,1,1,1,1},
        {0,1,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0}
       };
 
    bool blocks[offset*8][cols];
    bytes_to_blocks(cols, offset, blocks, length, bytes);

    for(int j=0; j<offset*8; j++){
        for(int i=0; i<cols; i++){
            printf("%d ", (blocks[j][i] == true) ? 1 : 0);
        }
        printf("\n");
        if( j % 8 == 7 ){
            printf("\n");
        }
    }
    printf("\n");

    bool bytes2[length][8];
    blocks_to_bytes(cols, offset, blocks, length, bytes2);
    for(int j=0; j<length; j++){
        for(int i=0; i<8; i++){
            printf("%d", bytes2[j][i]);
        }
        printf("\n");
    }*/
    
    return 0;
}
