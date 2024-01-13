#include <stdlib.h>
#include "hangman.h"
#include "morse.h"
#include <stdio.h>
#include <ctype.h>

int main(void){
  /*printf("%d\n", is_word_guessed("secret", "aeiou")); // 0
    printf("%d\n", is_word_guessed("hello", "aeihoul")); // 1


    char result[30];
    get_guessed_word("container", "arpstxgoieyu", result);
    printf("%s\n", result);

    char result2[30];
    get_available_letters("arpstxgoieyu", result2);
    printf("%s\n", result2);

    char secret[16];
    get_word(secret);
    hangman(secret);

    char output[150];
    text_to_morse("Hello", output);
    printf("\n%s\n", output);*/

    char output2[150];
    morse_to_text(". -.-. .-. .- -- ", output2);
    printf("%s\n", output2);

    if( is_morse_code_valid(". -.-. .-. .- --") ){
        printf("Code is valid!\n");
    } else {
        printf("Code is invalid!\n");
    }

    if( is_morse_code_valid("-... .. -.-. ..- -.--") ){
        printf("Code is valid!\n");
    } else {
        printf("Code is invalid!\n");
    }

    return 0;
}
