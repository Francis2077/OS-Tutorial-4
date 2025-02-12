/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * Francis Chukwu (100877764)
 * Timi Ogunleye (100879117)
 * Osayonamen Abe (100860342)
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

question questions[NUM_QUESTIONS];  

// Initializes the array of questions for the game
void initialize_game(void)
{
    // Programming questions
    strcpy(questions[0].category, "programming");
    strcpy(questions[0].question, "What is the keyword to declare a function in C?");
    strcpy(questions[0].answer, "what is void");
    questions[0].value = 100;
    questions[0].answered = false;

    strcpy(questions[1].category, "programming");
    strcpy(questions[1].question, "Which language is known for running in a web browser?");
    strcpy(questions[1].answer, "what is JavaScript");
    questions[1].value = 200;
    questions[1].answered = false;

    strcpy(questions[2].category, "programming");
    strcpy(questions[2].question, "What is the name of the process that converts source code into machine code?");
    strcpy(questions[2].answer, "what is compilation");
    questions[2].value = 300;
    questions[2].answered = false;

    strcpy(questions[3].category, "programming");
    strcpy(questions[3].question, "Which programming language is known for its use in data science and machine learning?");
    strcpy(questions[3].answer, "what is Python");
    questions[3].value = 400;
    questions[3].answered = false;

    // Algorithms questions
    strcpy(questions[4].category, "algorithms");
    strcpy(questions[4].question, "What algorithm is used for sorting by repeatedly swapping adjacent elements?");
    strcpy(questions[4].answer, "what is bubble sort");
    questions[4].value = 100;
    questions[4].answered = false;

    strcpy(questions[5].category, "algorithms");
    strcpy(questions[5].question, "Which algorithm is commonly used to find the shortest path in a graph?");
    strcpy(questions[5].answer, "what is Dijkstra's algorithm");
    questions[5].value = 200;
    questions[5].answered = false;

    strcpy(questions[6].category, "algorithms");
    strcpy(questions[6].question, "What is the worst-case time complexity of QuickSort?");
    strcpy(questions[6].answer, "what is O(n^2)");
    questions[6].value = 300;
    questions[6].answered = false;

    strcpy(questions[7].category, "algorithms");
    strcpy(questions[7].question, "Which algorithm is used in Artificial Intelligence for decision-making in games?");
    strcpy(questions[7].answer, "what is Minimax");
    questions[7].value = 400;
    questions[7].answered = false;

    // Databases questions
    strcpy(questions[8].category, "databases");
    strcpy(questions[8].question, "Which database language is used to manage relational databases?");
    strcpy(questions[8].answer, "what is SQL");
    questions[8].value = 100;
    questions[8].answered = false;

    strcpy(questions[9].category, "databases");
    strcpy(questions[9].question, "What type of database does MongoDB use?");
    strcpy(questions[9].answer, "what is NoSQL");
    questions[9].value = 200;
    questions[9].answered = false;

    strcpy(questions[10].category, "databases");
    strcpy(questions[10].question, "Which SQL clause is used to filter results based on a condition?");
    strcpy(questions[10].answer, "what is WHERE");
    questions[10].value = 300;
    questions[10].answered = false;

    strcpy(questions[11].category, "databases");
    strcpy(questions[11].question, "What is the process of ensuring that data in a database is accurate and consistent?");
    strcpy(questions[11].answer, "what is normalization");
    questions[11].value = 400;
    questions[11].answered = false;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void) {
    printf("\nCategories and Available Questions:\n");

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("%s: ", categories[i]);
        for (int j = 0; j < NUM_QUESTIONS; j++) {
            if (strcmp(questions[j].category, categories[i]) == 0 && !questions[j].answered) {
                printf("$%d ", questions[j].value);
            }
        }
        printf("\n");
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            if (!questions[i].answered) {
                printf("\nQuestion for $%d in %s:\n%s\n", value, category, questions[i].question);
            } else {
                printf("This question has already been answered.\n");
            }
            return;
        }
    }
    printf("No question found for this category and value.\n");
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return (strcasecmp(answer, questions[i].answer) == 0);
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return questions[i].answered;
        }
    }
    return false;
}
