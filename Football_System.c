/*
This is a program in  C that allows the user to input the names of football teams and record their match results. 
The program uses a struct called "Team" to store the team's name, wins, losses, and draws. The program allows the 
user to input the home team index, away team index, home team score, and away team score. Based on the scores, 
the program updates the number of wins, losses, and draws for the home and away teams.
The program has three functions:
    updateResults: This function updates the number of wins, losses, and draws for the home and away teams based on the scores inputted by the user.
    displayResults: This function displays the results of all the teams entered by the user.
    exportResults: This function exports the results to a CSV file named "Football_results.csv".
The program uses a while loop to allow the user to input as many teams and match results as they want. 
The program also includes a maximum number of teams that can be entered, which is set to 20.
At the end of the program, the results are displayed on the console and exported to a CSV file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAMS 20
#define MAX_NAME_LENGTH 50

struct Team {
    char name[MAX_NAME_LENGTH];
    int wins;
    int losses;
    int draws;
};

void updateResults(struct Team teams[], int home, int away, int homeScore, int awayScore) {
    if (homeScore > awayScore) {
        teams[home].wins++;
        teams[away].losses++;
    } else if (homeScore < awayScore) {
        teams[home].losses++;
        teams[away].wins++;
    } else {
        teams[home].draws++;
        teams[away].draws++;
    }
}

void displayResults(struct Team teams[], int n) {
    printf("\n\t\tClub\tWins\tLosses\tDraws\n");
    for (int i = 0; i < n; i++) {
        printf("\n\t\t%s\t%d\t%d\t%d\n", teams[i].name, teams[i].wins, teams[i].losses, teams[i].draws);
    }
}

void exportResults(struct Team teams[], int n) {
    FILE *fp = fopen("Football_results.csv", "w");
    fprintf(fp, "Club,Wins,Losses,Draws\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s,%d,%d,%d\n", teams[i].name, teams[i].wins, teams[i].losses, teams[i].draws);
    }
    fclose(fp);
    printf("\n\t\tResults exported to Football_results.csv\n");
}

int main() {
    struct Team teams[MAX_TEAMS];
    int n = 0;
    int home, away, homeScore, awayScore;
    char teamName[MAX_NAME_LENGTH];
        system("color 2");
    printf("\t\t\t\t\t\t\t\t\tThe code was developed by Oliver Nikolajevic");
    while (1) {
        printf("\n\t\tEnter home team name (or 'q' to quit): ");
        fgets(teamName, MAX_NAME_LENGTH, stdin);
        if (strcmp(teamName, "q\n") == 0) {
            break;
        }
        if (n == MAX_TEAMS) {
            printf("\n\t\tMaximum number of teams reached\n");
            break;
        }
        teamName[strcspn(teamName, "\n")] = 0; // remove newline character
        strncpy(teams[n].name, teamName, MAX_NAME_LENGTH);
        teams[n].wins = 0;
        teams[n].losses = 0;
        teams[n].draws = 0;
        n++;
    }
    printf("\n\t\tEnter Football match results:\n");
    while (1) {
        printf("\n\t\tHome team index (-1 to quit): ");
        scanf("%d", &home);
        if (home == -1) {
            break;
        }
        printf("\n\t\tAway team index: ");
        scanf("%d", &away);
        printf("\n\t\tHome team score: ");
        scanf("%d", &homeScore);
        printf("\n\t\tAway team score: ");
        scanf("%d", &awayScore);
        updateResults(teams, home, away, homeScore, awayScore);
    }
    displayResults(teams, n);
    exportResults(teams, n);
    //The code was developed by Oliver Nikolajevic
    return 0;
}
