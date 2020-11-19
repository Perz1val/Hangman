#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <iterator>

void hangman(const char secret[]);

int is_word_guessed(const char secret[], const char letters_guessed[]);

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]);

void get_available_letters(const char letters_guessed[], char available_letters[]);

void print_gessed_word(const char guessed_word[]);
bool is_enter_valid(const char enter);
bool is_in_array(const char array[], char el);


int main()
{
    hangman("suctioned");

    
}

void print_gessed_word(const char guessed_word[]) {
    for (int i = 0; i < strlen(guessed_word); i++) {
        printf("%c ", guessed_word[i]);
    }
    printf("\n");
}

int is_word_guessed(const char secret[], const char letters_guessed[]) {

    int secret_lenth = strlen(secret);

    for (int i = 0; i < secret_lenth; i++) {
        if ((!is_in_array(letters_guessed, secret[i])))
            return 0;
    }
    return 1;
}


void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    size_t i, j;
    size_t secret_size = strlen(secret);
    size_t guessed_size = strlen(letters_guessed);


    for (size_t i = 0; i < strlen(secret); i++) {
        guessed_word[i] = '_';
    }

    for (i = 0; i < guessed_size; i++) {
        for (j = 0; j < secret_size; j++) {
            if (letters_guessed[i] == secret[j]) {
                guessed_word[j] = secret[j];
            }
        }

    }
    guessed_word[secret_size] = '\0';
}

void get_available_letters(const char letters_guessed[], char available_letters[]) {
    size_t guessed_size = strlen(letters_guessed);
    int check = 1;
    int adder = 0;
    char alpha[26];

    for (int ch = 'a'; ch <= 'z'; ch++) {
        alpha[ch - 'a'] = ch;
    }

    for (int i = 0; i < 26; i++) {
        for (size_t j = 0; j < guessed_size; j++) {
            if (alpha[i] == letters_guessed[j]) {
                check = 0;
            }
        }

        if (check == 1) {
            available_letters[adder] = alpha[i];
            adder++;
        }
        else {
            check = 1;

        }

    }

    available_letters[26 - guessed_size] = '\0';

}

void hangman(const char secret[]) {
    int secret_len = strlen(secret);
    int guesses = 8;
    int adder = 0;

    bool loop = true;

    char letters_guessed[30]{ };
    char available_letters[30];
    char guessed_word[20];
    char enter;

    //Found this on Stackoverflow
    for (int ch = 'a'; ch <= 'z'; ch++) {
        available_letters[ch - 'a'] = ch;
    }
    //***************************
    printf("Welcome to the game, Hangman! \nI am thinking of a word that is %d letters long. \n------------- \n", secret_len);

    while (loop) {

        if (is_word_guessed(secret, letters_guessed) == 1) {
            printf("Congratulations, you won!");
            break;
        }

        if (guesses == 0) {
            printf("Sorry, you ran out of guesses. The word was %s.", secret);
            break;
        }

        printf("You have %d guesses left. \n", guesses);

        get_available_letters(letters_guessed, available_letters);
        printf("Available letters: ");
        printf("%s \n", available_letters);

        printf("Please guess a letter: ");

        scanf(" %c", &enter);
        enter = tolower(enter);
        if (is_enter_valid(enter)) {

            if (!is_in_array(letters_guessed, enter)) {
                letters_guessed[adder] = enter;
                adder++;
            }
            else {
                printf("Oops! You've already guessed that letter: ");
                get_guessed_word(secret, letters_guessed, guessed_word);
                print_gessed_word(guessed_word);
                printf("------------- \n");
                continue;
            }
        }
        else {
            printf("\nOops! '%c' is not a valid letter: ", enter);
            print_gessed_word(guessed_word);
            printf("------------- \n");
            continue;
        }

        get_guessed_word(secret, letters_guessed, guessed_word);

        if (is_in_array(secret, enter)) {
            printf("Good guess: ");
            print_gessed_word(guessed_word);
            printf("------------- \n");
        }
        else {
            guesses--;
            printf("Oops! That letter is not in my word: ");
            print_gessed_word(guessed_word);
            printf("------------- \n");
        }


    }

}

bool is_enter_valid(const char enter) {
    char available_letters[30];
    for (int ch = 'a'; ch <= 'z'; ch++) {
        available_letters[ch - 'a'] = ch;
    }

    for (int i = 0; i < 30; i++) {
        if (enter == available_letters[i]) {
            return true;
        }
    }

    return false;
}

bool is_in_array(const char array[], char el) {
    for (size_t i = 0; i < strlen(array); i++) {
        if (el == array[i]) {
            return true;
        }
    }

    return false;
}
