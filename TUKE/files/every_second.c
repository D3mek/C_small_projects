#include <stdio.h>

#define MAX_LENGTH 100

int main(int argc, char *argv[]){

    if (argc != 3) {
        printf("ERROR: usage: %s\n", argv[0]);
        return 1;
    }

    // open files
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if ( input == NULL ) {
        printf("ERROR, couldn't open file %s.\n", argv[1]);
        return 1;
    }

    char c;
    char word[MAX_LENGTH];
    int index = 0;
    int count_word = 0;

    int found_start = 0;
    int found_stop = 0;

    printf("\n");

    int i = 0;
    while( (c = fgetc(input)) != EOF ){
        if( !found_start ){
            if( c == "START"[i] ){
                i++;
                if( i == 5 ){
                found_start = 1;
                }
                continue;
            } else {
                i = 0;
            }
        }

        if( found_start ){
            if( c == "STOP"[i] && !found_stop ){
                break;
            } else {
                i = 0;
            }
        }

        if( found_start && !found_stop ){
            if( c == ' ' ){
                word[index] = '\0';
                if( index > 0 ){
                    count_word++;
                    if( count_word % 2 == 0 ){
                        for(int i=0; word[i] != '\0'; i++){
                            fputc(word[i], output);
                        }
                        fputc(' ', output);
                    }
                    index = 0;
                    word[index] = '\0';
                }
            } else {
                if( index < MAX_LENGTH - 1 ){
                    word[index] = c;
                    index++; 
                }
            }
        }
    }

    fclose(input);
    fclose(output);

    output = fopen(argv[2], "r");
    char words_array[10000];
    i = 0;
    while( (c = fgetc(output)) != EOF ){
        words_array[i] = c;
        i++;
    }
    words_array[i] = '\0';
    fclose(output);

    output = fopen(argv[2], "w");
    i--;
    for(int j=0; j<i; j++){
        fputc(words_array[j], output);
    }
    fclose(output);

    return 0;
}