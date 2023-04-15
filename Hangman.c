#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 20
#define MAX_TRIES 6

void printHangman(int tries) {
    switch (tries) {
        case 0:
            printf("\n\n\n O\n");
            break;
        case 1:
            printf("\n\n\n\n|\n");
            break;
        case 2:
            printf("\n\n\n |\n|\n");
            break;
        case 3:
            printf("\n\n |\n |\n|\n");
            break;
        case 4:
            printf("\n\n |\n-|\n|\n");
            break;
        case 5:
            printf("\n |\n/|\\\n |\n|\n");
            break;
        case 6:
            printf("\n |\n/|\\\n |\n/ \\\n");
            break;
        default:
            printf("Error: Invalid number of tries.\n");
            break;
    }
}

void printWord(char *word, int len, int *guessedLetters) {
    for (int i = 0; i < len; i++) {
        if (guessedLetters[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int chooseWord(char *filename, char *word) {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int numWords = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file: %s\n", filename);
        return 0;
    }
    while (fgets(words[numWords], MAX_WORD_LEN, file) != NULL) {
        numWords++;
    }
    fclose(file);
    if (numWords == 0) {
        printf("No words found in file: %s\n", filename);
        return 0;
    }
    srand(time(NULL));
    int randIndex = rand() % numWords;
    strcpy(word, words[randIndex]);
    word[strcspn(word, "\r\n")] = '\0'; // Remove newline characters
    return 1;
}

int guessLetter(char *word, int len, int *guessedLetters, char letter) {
    int correct = 0;
    letter = tolower(letter);
    for (int i = 0; i < len; i++) {
        if (tolower(word[i]) == letter) {
            guessedLetters[i] = 1;
            correct = 1;
        }
    }
    return correct;
}

int main() {
	   system("color 2");
    printf("\t\t\t\tThe game was developed by Oliver Nikolajevic\n");
    char filename[] = "words.txt";
    char word[MAX_WORD_LEN];
    int len, guessedLetters[MAX_WORD_LEN] = {0}, tries = 0;
    
    if (!chooseWord(filename, word)) {
        return 1;
    }
    len = strlen(word);
    
    printf("Welcome to Hangman!\n");
    printf("The word has %d letters.\n", len);
    
    while (tries < MAX_TRIES) {
        printHangman(tries);
        printWord(word, len, guessedLetters);
        
        char input[2];
        printf("Enter a letter: ");
        fgets(input, 2, stdin);
        if (!isalpha(input[0])) {
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }
        if (guessLetter(word, len, guessedLetters, input[0])) {
     
        int allGuessed = 1;
        for (int i = 0; i < len; i++) {
            if (!guessedLetters[i]) {
                allGuessed = 0;
                break;
            }
        }
        if (allGuessed) {
            printf("You win!\n");
            printf("The word was: %s\n", word);
            return 0;
        }
    } else {
        printf("Incorrect.\n");
        tries++;
        printHangman(tries);
        if (tries == MAX_TRIES) {
            printf("You lose! The word was: %s\n", word);
            return 0;
        }
    }
//The game was developed by Oliver Nikolajevic
}}

/*
In the game Hangman you must have a file words.txt in which you will have words that the user will guess
The file words.txt must be in the same place where the game will be
Example
words.txt
apple
banana
cherry
grape
orange
pear
pineapple
strawberry
watermelon

*/


