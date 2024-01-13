#include <stdio.h>

int main(int argc, char *argv[]){
    // check correct number of arguments
    if (argc != 2) {
        printf("ERROR: usage: %s\n", argv[0]);
        return 1;
    }

    // open file in read mode
    FILE *file = fopen(argv[1], "r");

    // check if open was successful or not
    if (file == NULL) {
        printf("ERROR, couldn't open file %s.\n", argv[1]);
        return 1;
    }

    // variable for count chars
    int count = 0;
    // variable for store character from file
    int c;
    // check if word ananas is found
    int found = 0;
    // indexing for ananas string
    int i = 0;

    while ((c = fgetc(file)) != EOF) { // while not end of file
        if ('A' <= c && c <= 'Z') { // if char is uppercase
            c += 'a' - 'A'; // to lowercase
        }

        if (c == "ananas"[i]) {
            i++;
            if (i == 6) { // Found the whole "ananas" string
                found = 1;
                i = 0;
            }
            continue;
        } else {
            i = 0;
        }

        if (found) {
            count++;
            found = 0;
        }
    }


    fclose(file); // close read file

    // open file for write and cleare file
    file = fopen(argv[1], "w");

    // write number of found sequnces of ananas
    if( count > 9 && count < 100 ){
        char number1 = (char)((count / 10) + 48);
        fputc(number1, file);
        char number2 = (char)((count % 10) + 48);
        fputc(number2, file); 
    }
    if( count < 10 ){
        char number = (char)(count + 48);
        fputc(number, file);
    }

    fclose(file); // close file

    return 0;
}

