#include <sys/stat.h>
#include "morse.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// arrays for easier interact
void arrays(char output_abcd[], char output_morse[][5]){
    char abcd[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
    for(int i=0; abcd[i] != '\0'; i++){
        output_abcd[i] = abcd[i];
    }
    output_abcd[strlen(abcd)] = '\0';

    char morse[26][5] = { {'.','-','\0'},{'-','.','.','.','\0'},{'-','.','-','.','\0'},{'-','.','.','\0'},{'.','\0'},{'.','.','-','.','\0'},{'-','-','.','\0'},
                         {'.','.','.','.','\0'},{'.','.','\0'},{'.','-','-','-','\0'},{'-','.','-','\0'},{'.','-','.','.','\0'},{'-','-','\0'},{'-','.','\0'},
                         {'-','-','-','\0'},{'.','-','-','.','\0'},{'-','-','.','-','\0'},{'.','-','.','\0'},{'.','.','.','\0'},{'-','\0'},{'.','.','-','\0'},
                         {'.','.','.','-','\0'},{'.','-','-','\0'},{'-','.','.','-','\0'},{'-','.','-','-','\0'},{'-','-','.','.','\0'} };
   for(int i=0; i<27; i++){
       for(int j=0; morse[i][j] != '\0'; j++){
           output_morse[i][j] = morse[i][j];
       }
       output_morse[i][strlen(morse[i])] = '\0';
   }
}

// text to more code - HELLO -> "....-.." morse encrypt
void text_to_morse(const char text[], char output[]){
    char text_upper[30];
    char abcd[27];
    char morse[26][5];
    arrays(abcd, morse); // fill arrays

    int index = 0;
    while( text[index] ){
        text_upper[index] = toupper((unsigned char)text[index]);
        index++;
    }
    text_upper[index] = '\0';
    
    int size_of_output = 0;

    for(int i=0; text_upper[i] != '\0'; i++){ // through text
        for(int j=0; abcd[j] != '\0'; j++){ // through abcd
	        if( text_upper[i] == abcd[j] ){ // try to find letter
                for(int k=0; morse[j][k] != '\0'; k++){
                    output[size_of_output] = morse[j][k];
                    size_of_output++;
                }
                if( text_upper[i+1] ){
                    output[size_of_output] = ' ';
                    size_of_output++;
                }
                break;
            }
        }
    }
    output[size_of_output] = '\0';
}

// morse code to text decrypt 
void morse_to_text(const char morse[], char output[]){
    char abcd[27];
    char morse_array[26][5];
    arrays(abcd, morse_array); // fill arrays
    
    char deli[] = " "; // delimiter
    char morseCpy[150];
    strcpy(morseCpy, morse); // cpy set morse to morseCpy array

    char *token = strtok(morseCpy, deli); // splited
    
    int counter = 0;
    while( token != NULL ){
        //printf("'%s'\n", token);
        for(int i=0; i<26; i++){
            if( !strcmp(token, morse_array[i]) ){
                output[counter] = abcd[i];
                counter++;
                break;
            }
        }
        token = strtok(NULL, deli);
    }
    output[counter] = '\0';
}

// check if set morse code is valid or not
int is_morse_code_valid(const char morse[]){
    char abcd[27];
    char morse_array[26][5];
    arrays(abcd, morse_array);

    char deli[] = " ";
    char morseCpy[150];
    strcpy(morseCpy, morse);

    char *token = strtok(morseCpy, deli);

    int founded;
    while( token != NULL ){
        founded = 0;
        for(int i=0; i<26; i++){
            if( !strcmp(token, morse_array[i]) ){
                founded = 1;
                break;
            }
        }
        if( !founded ){
            return 0;
        }
        token = strtok(NULL, deli);
    }
    return 1;
}
