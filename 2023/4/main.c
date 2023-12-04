#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
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

int get_card_points(char* card) {
    char* winning_str;
    char* own_str;
    int winning_nums[NUM_WINNING];
    int own_nums[NUM_OWN];
    char *saveptr;
    int i, j;
    int points = 0;

    winning_str = strtok_r(card, "|", &saveptr);
    own_str = strtok_r(NULL, "|", &saveptr);

    read_string_into_num_array(winning_nums, NUM_WINNING, winning_str);
    read_string_into_num_array(own_nums, NUM_OWN, own_str);

    for (i = 0; i < NUM_WINNING; i++) {
        for (j = 0; j < NUM_OWN; j++) {
            if (winning_nums[i] == own_nums[j]) {
                if (points == 0) {
                    points = 1;
                } else {
                    points *= 2;
                }
            }
        }
    }

    return points;
}

int main() {
    char line[MAX_LINE];
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
        points = get_card_points(card);
        points_sum += points;
    }

    printf("%d\n", points_sum);
    return 0;
}