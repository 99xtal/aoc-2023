#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define NUM_CARDS 205
#define NUM_WINNING 10
#define NUM_OWN 25

void read_string_into_num_array(int* dest, int length, char* string) {
    int i = 0;
    char* source;
    char *tok;
    char *saveptr;

    source = strdup(string);
    tok = strtok_r(source, " ", &saveptr);
    dest[i] = atoi(tok);
    for (i = 1; i < length; i++) {
        tok = strtok_r(NULL, " ", &saveptr);
        dest[i] = atoi(tok); 
    }
}

int get_num_matches(char* card) {
    char* winning_str;
    char* own_str;
    int winning_nums[NUM_WINNING];
    int own_nums[NUM_OWN];
    char *saveptr;
    int i, j;
    int num_matches = 0;

    winning_str = strtok_r(card, "|", &saveptr);
    own_str = strtok_r(NULL, "|", &saveptr);

    read_string_into_num_array(winning_nums, NUM_WINNING, winning_str);
    read_string_into_num_array(own_nums, NUM_OWN, own_str);

    for (i = 0; i < NUM_WINNING; i++) {
        for (j = 0; j < NUM_OWN; j++) {
            if (winning_nums[i] == own_nums[j]) {
                num_matches++;
            }
        }
    }

    return num_matches;
}

int main() {
    char line[MAX_LINE];
    int card_matches_t[NUM_CARDS + 1];
    int card_nums_t[NUM_CARDS + 1];
    char* saveptr;
    int points_sum = 0;

    while (fgets(line, MAX_LINE, stdin) != NULL) {
        int card_id = 0;
        int points;

        char* card_id_str = strtok_r(line, ":", &saveptr);
        if (card_id_str != NULL) {
            for (char* p = card_id_str; *p != '\0'; p++) {
                if (isdigit(*p)) {
                    card_id = (card_id * 10) + (*p - '0');
                }
            }
        }

        char* card = strtok_r(NULL, ":", &saveptr);
        int num_matches = get_num_matches(card);
        points = num_matches >= 2 ? pow(2, num_matches - 1) : num_matches;
        printf("%d:\tm:%d\tp:%d\n", card_id, num_matches, points);
        points_sum += points;

        card_matches_t[card_id] = num_matches;
    }

    for (int i=0; i <= NUM_CARDS; i++) {
        card_nums_t[i] = 1;
    } 

    for (int i = 1; i <= NUM_CARDS; i++) {
        int card_id = i;
        int num_matches = card_matches_t[card_id];
        for (int j = card_id + 1; j <= card_id + num_matches; j++) {
            card_nums_t[j] += card_nums_t[i];
        }
    }

    int won_cards = 0;
    for (int i = 1; i <= NUM_CARDS; i++) {
        won_cards += card_nums_t[i];
    }

    printf("%d\n", points_sum);
    printf("%d\n", won_cards);
    return 0;
}