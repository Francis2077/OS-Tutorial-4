/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * Francis Chukwu (100877764)
 * Osayonamen Abe (100860342)
 * Timi Ogunleye (100879117)
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens) {
    char *delimiters = " ";
    char *word = strtok(input, delimiters);
    int index = 0;

    while (word != NULL) {
        tokens[index++] = word;
        word = strtok(NULL, delimiters);
    }
    tokens[index] = NULL;  // Null-terminate the token array
}


// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players) {
    // Sort players by score in descending order
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = i + 1; j < num_players; j++) {
            if (players[j].score > players[i].score) {
                player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    printf("\nFinal Results:\n");
    for (int i = 0; i < num_players; i++) {
        printf("%d. %s - $%d\n", i + 1, players[i].name, players[i].score);
    }
}


int main(void) {  
    // Array of players
    player players[NUM_PLAYERS];

    // Input buffer for user commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction
    printf("Welcome to Jeopardy!\n");

    // Initialize the questions
    initialize_game();

    // Prompt for player names
    printf("Enter the names of the four players:\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = '\0';  
        players[i].score = 0;  // Initialize score to 0
    }

    printf("\nGame Starting! Here are the categories:\n");
    display_categories();

    // Game loop: continue until all questions are answered
    while (1) {
        int allAnswered = 1;
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (!questions[i].answered) {
                allAnswered = 0;
                break;
            }
        }
        if (allAnswered) break;  // Exit loop if all questions are answered

        // Ask the player to choose a question
        char player_name[MAX_LEN];
        char category[MAX_LEN];
        int value;

        printf("\nEnter the name of the player choosing a question: ");
        fgets(player_name, MAX_LEN, stdin);
        player_name[strcspn(player_name, "\n")] = '\0';  // Remove newline

        // Validate player exists
        if (!player_exists(players, NUM_PLAYERS, player_name)) {
            printf("Invalid player name. Try again.\n");
            continue;
        }

        // Ask for category and value
        printf("Enter a category: ");
        fgets(category, MAX_LEN, stdin);
        category[strcspn(category, "\n")] = '\0';

        printf("Enter the dollar value: ");
        scanf("%d", &value);
        getchar();  // Consume newline left in the input buffer

        // Check if the question is already answered
        if (already_answered(category, value)) {
            printf("This question has already been answered. Choose another.\n");
            continue;
        }

        // Display the selected question
        display_question(category, value);

        // Get player's answer
        printf("Enter your answer (start with 'what is' or 'who is'): ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        // Validate answer
        if (valid_answer(category, value, buffer)) {
            printf("Correct!\n");
            update_score(players, NUM_PLAYERS, player_name, value);
        } else {
            printf("Incorrect! The correct answer was: %s\n", questions[value].answer);
        }

        // Mark question as answered
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
                questions[i].answered = true;
                break;
            }
        }

        // Display remaining categories and questions
        display_categories();
    }

    // Show final results
    show_results(players, NUM_PLAYERS);
    
    printf("\nGame Over! Thanks for playing Jeopardy!\n");
    return EXIT_SUCCESS;
}
