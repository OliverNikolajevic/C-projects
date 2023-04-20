/*
The code is a simple poker game program in C, where the user can input the number of players, player's name, and money. 
Then, the players can bet on 5 randomly selected numbers between 0 and 31. The program then selects 5 winning numbers 
and compares them with the players' selected numbers. If there is a match, the player wins the bet amount multiplied 
by a power of 2 based on the number of matches. The game continues until only one player is left with money or until the user chooses to quit.
The program includes the following functions:
    number_already_selected: checks if a number has already been selected by a player.
    get_int_input: gets an integer input from the user and validates it to ensure it's within a certain range.
    get_bets: prompts the players to enter their bets and selected numbers.
    select_numbers: selects 5 random winning numbers.
    count_matches: counts the number of matches between a player's selected numbers and the winning numbers.
    pay_out: calculates the winnings for each player and adds it to their money if they win.
    get_player_info: prompts the user to enter the name and money of a player.
In the main function, the program first prompts the user to enter the number of players and the name and money of each player.
Then, it enters a loop that runs until only one player is left with money or the user chooses to quit. In each iteration of
the loop, it prompts the players to enter their bets, selects the winning numbers, and calculates the winnings for each player.
It also checks if any players have run out of money and updates the number of remaining players. Finally, it asks the user 
if they want to continue playing or quit. If there is only one player remaining or the user chooses to quit, the program terminates.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_PLAYERS_MAX 10
#define NAME_LENGTH_MAX 20
#define BET_AMOUNT_MIN 1
#define BET_AMOUNT_MAX 100
#define NUMBER_CHOICES 32
#define NUM_NUMBERS_SELECTED 5

typedef struct {
    char name[NAME_LENGTH_MAX];
    int money;
    int bet;
    int numbers[NUM_NUMBERS_SELECTED];
} PokerPlayer;
int number_already_selected(int number, int *numbers, int num_numbers_selected) {
    for (int i = 0; i < num_numbers_selected; i++) {
        if (numbers[i] == number) {
            return 1;
        }
    }
    return 0;
}
int get_int_input(int min_value, int max_value) {
    int value;
    int num_read;
    do {
        num_read = scanf("%d", &value);
        if (num_read != 1 || value < min_value || value > max_value) {
            printf("\n\t\tInvalid input. Please enter a number between %d and %d: ", min_value, max_value);
            while (getchar() != '\n') {}
        }
    } while (value < min_value || value > max_value);
    return value;
}

void get_bets(PokerPlayer *players, int num_players) {
    for (int i = 0; i < num_players; i++) {
        printf("\n\t\t%s's turn:\n", players[i].name);
        printf("\n\t\tEnter bet amount (%d-%d): ", BET_AMOUNT_MIN, BET_AMOUNT_MAX);
        players[i].bet = get_int_input(BET_AMOUNT_MIN, BET_AMOUNT_MAX);
        printf("\n\t\tEnter %d numbers (0-31):", NUM_NUMBERS_SELECTED);
        for (int j = 0; j < NUM_NUMBERS_SELECTED; j++) {
            players[i].numbers[j] = get_int_input(0, NUMBER_CHOICES-1);
        }
    }
}
void select_numbers(int *numbers) {
    printf("\n\t\tWinning numbers:\n");
    for (int i = 0; i < NUM_NUMBERS_SELECTED; i++) {
        int number;
        do {
            number = rand() % NUMBER_CHOICES;
        } while (number_already_selected(number, numbers, i));
        numbers[i] = number;
        printf("\n\t\t%d ", number);
    }
    printf("\n");
}

int count_matches(int *numbers1, int *numbers2) {
    int count = 0;
    for (int i = 0; i < NUM_NUMBERS_SELECTED; i++) {
        if (numbers1[i] == numbers2[i]) {
            count++;
        }
    }
    return count;
}

void pay_out(PokerPlayer *players, int num_players, int *winning_numbers) {
    for (int i = 0; i < num_players; i++) {
        int num_matches = count_matches(players[i].numbers, winning_numbers);
        if (num_matches > 0) {
            int winnings = players[i].bet * (1 << (num_matches - 1));
            printf("\n\t\t%s wins %d with %d matches!\n", players[i].name, winnings, num_matches);
            players[i].money += winnings;
        } else {
            printf("\n\t\t%s didn't match any numbers.\n", players[i].name);
        }
        printf("\n\t\t%s now has %d.\n", players[i].name, players[i].money);
    }
}





void get_player_info(PokerPlayer *player) {
    printf("\n\t\tName: ");
    scanf("%s", player->name);
    printf("\n\t\tMoney: ");
    player->money = get_int_input(0, INT_MAX);
}


int main(void) {
    srand(time(NULL));
    system("color 2");
    printf("\t\t\t\t\t\t\t\t\tThe code was developed by Oliver Nikolajevic");
    printf("\n\t\tWelcome to the POKER GAME!\n\n");
    printf("\n\t\tHow many players? (1-%d): ", NUM_PLAYERS_MAX);
 
    int num_players = get_int_input(1, NUM_PLAYERS_MAX);


    PokerPlayer *players = (PokerPlayer*) malloc(num_players * sizeof(PokerPlayer));

    for (int i = 0; i < num_players; i++) {
        printf("\n\t\tPlayer %d:\n", i+1);
        get_player_info(&players[i]);
    }

    int continue_playing = 1;
    while (continue_playing) {
        get_bets(players, num_players);

        int winning_numbers[NUM_NUMBERS_SELECTED];
        select_numbers(winning_numbers);

        pay_out(players, num_players, winning_numbers);

        for (int i = 0; i < num_players; i++) {
            if (players[i].money <= 0) {
                printf("\n\t\t%s is out of money!\n", players[i].name);
            }
        }

        int num_players_remaining = 0;
        for (int i = 0; i < num_players; i++) {
            if (players[i].money > 0) {
                num_players_remaining++;
            }
        }
        if (num_players_remaining < 2) {
            printf("\n\t\tGame over!\n");
            continue_playing = 0;
        } else {
            printf("\n\t\tContinue playing? (y/n): ");
            char choice;
            do {
                scanf("%c", &choice);
            } while (choice != 'y' && choice != 'n');
            if (choice == 'n') {
                continue_playing = 0;
            }
        }
    }
//The code was developed by Oliver Nikolajevic
    free(players);
    return 0;
}




