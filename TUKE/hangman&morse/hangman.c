#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <string.h>
#include <ctype.h>

int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

// check if word is guessed or not
int is_word_guessed(const char secret[], const char letters_guessed[]){
    int secret_size = strlen(secret);
    int letters_size = strlen(letters_guessed);
    int founded;

    for(int i=0; i<secret_size; i++){
        founded = 0;
        for(int j=0; j<letters_size; j++){
            if( secret[i] == letters_guessed[j] ){
                founded = 1;
                break; 
            }
        }
        if( !founded ){
            return 0;
        }
    }
    return 1;
}

// get word from guessed words but for hangman
void get_guessed_word2(const char secret[], const char letters_guessed[], char guessed_word[]){
    int secret_size = strlen(secret);
    int letters_size = strlen(letters_guessed);
    int founded;
    int counter = 0;

    for(int i=0; i<secret_size; i++){
        founded = 0;
        for(int j=0; j<letters_size; j++){  
            if( secret[i] == letters_guessed[j] ){
                founded = 1;
                guessed_word[counter] = letters_guessed[j];
                counter++;
                guessed_word[counter] = ' ';
                counter++;
                break;
            }
        }
        if( !founded ){
            guessed_word[counter] = '_';
            counter++;
            guessed_word[counter] = ' ';
            counter++;
        }
    }
    guessed_word[counter-1] = '\0';
}

// get word from guessed words
void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
    int secret_size = strlen(secret);
    int letters_size = strlen(letters_guessed);  
    int founded;

    for(int i=0; i<secret_size; i++){
        founded = 0;
        for(int j=0; j<letters_size; j++){
            if( secret[i] == letters_guessed[j] ){
               founded = 1;
               guessed_word[i] = letters_guessed[j];
               break;
            }
        }
        if( !founded ){
           guessed_word[i] = '_';
        }
    }
    guessed_word[strlen(secret)] = '\0';
}

// available letter ( abcd - guessed_letters )
void get_available_letters(const char letters_guessed[], char available_letters[]){
    char abcd[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};
    int letters_size = strlen(letters_guessed);
    int abcd_size = strlen(abcd);
    int counter = 0;
    int founded;

    for(int i=0; i<abcd_size; i++){
        founded = 0;
        for(int j=0; j<letters_size; j++){
            if( abcd[i] == letters_guessed[j] ){
                founded = 1;
                break;
            }
        }
        if( !founded ){
            available_letters[counter] = abcd[i];
            counter++;
        }
    }
    available_letters[counter] = '\0';
}

// valid letter check '?','/'.. -> not valid
int valid_letter(const char guess[]){
    char abcd[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};
    for(int i=0; i<strlen(abcd); i++){
        if( abcd[i] == guess[0] ){
            return 1;
        }
    }
    return 0;
}

// if letter was already guessed
int guessed(const char letters_guessed[], const char guess[]){
    for(int i=0; i<strlen(letters_guessed); i++){
        if( letters_guessed[i] == guess[0]){
            return 1;
        }
    }
    return 0;
}

// letter in word
int in_word(const char secret[], const char guess[]){
    for(int i=0; i<strlen(secret); i++){
        if( secret[i] == guess[0] ){
           return 1;
        }
    }
    return 0;
}

// main func. for game
void hangman(const char secret[]){
    int guesses = 8;
    char letters_guessed[30];
    int secret_size = strlen(secret);
    char guessed_word[30];
    int counter = 0;
    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n", secret_size);

    while( guesses > 0 ){
        char available_letters[30];
        char guess[30];

        printf("-------------\n");
        printf("You have %d guesses left.\n", guesses);

        get_available_letters(letters_guessed, available_letters);
        printf("Available letters: %s\n", available_letters);
        
        printf("Please guess a letter: ");
        scanf("%s", guess);
        int size_guess = strlen(guess);
        
        if( size_guess == 1 ){ // one char
            guess[0] = tolower(guess[0]);

            if( valid_letter(guess) ){ // valid letter

               if( !guessed(letters_guessed, guess) ){ // not guessed
                  letters_guessed[counter] = guess[0];
                  counter++;

                  if( in_word(secret, guess) ){ // letter in word
                     get_guessed_word2(secret, letters_guessed, guessed_word);
                     printf("Good guess: %s\n", guessed_word);
                     if( is_word_guessed(secret, letters_guessed) ){ // check if word is guessed
                        printf("-------------\nCongratulations, you won!\n");
                        return;
                     }
                  } else { // letter not in word
                      get_guessed_word2(secret, letters_guessed, guessed_word);
                      printf("Oops! That letter is not in my word: %s\n", guessed_word);
                      guesses--;
                      continue;
                  }

               } else { // already guessed
                   get_guessed_word2(secret, letters_guessed, guessed_word);
                   printf("Oops! You've already guessed that letter: %s\n", guessed_word);
                   continue;
               }

            } else { // not valid letter
                get_guessed_word2(secret, letters_guessed, guessed_word);
                printf("Oops! '%c' is not a valid letter: %s\n", guess[0], guessed_word);
                continue;
            }


        } else { // more then one char
            int i=0;
            while(guess[i]){ // to lower case
                 guess[i] = tolower(guess[i]);
                 i++;
            }
            if( strcmp(guess, secret) ){
                printf("Sorry, bad guess. The word was %s.\n", secret);
                return;
            } else {
                printf("Congratulations, you won!\n");
                return;
            }
        }
    }
    printf("-------------\nSorry, you ran out of guesses. The word was %s.\n", secret);
}
