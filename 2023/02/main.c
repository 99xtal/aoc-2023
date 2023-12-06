#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define NUM_GAMES 100

typedef struct round {
    int r_num;
    int g_num;
    int b_num;
} round;

typedef struct round_node {
    round* data;
    struct round_node* next;
} round_node;

char* get_game_str(char* line) {
    char* game_str = malloc(256 * sizeof(char));
    char* token = strtok(line, ":\n");
    while (token != NULL) {
        strcpy(game_str, token);
        token = strtok(NULL, ":\n");
    }
    return game_str;
}

round* get_round_data(char* round_str) {
    round* new_round = (round*)malloc(sizeof(round));
    char* color;
    char *a, *b;
    int color_num;

    char* pch = strtok_r(strdup(round_str), ",", &a);
    while (pch != NULL) {
        char* color_num_str = strtok_r(pch, " ", &b);
        color_num = atoi(color_num_str);
        color = strtok_r(NULL, " ", &b);
        if (!strcmp(color,"red")) {
            new_round->r_num = color_num;
        } else if(!strcmp(color,"green")) {
            new_round->g_num = color_num;
        } else if(!strcmp(color, "blue")) {
            new_round->b_num = color_num;
        }
        pch = strtok_r(NULL, ",", &a);
    }

    return new_round;
}

// Part 1
int calculate_valid_game_sum(round_node* games[NUM_GAMES]) {
    int game_id_sum = 0;
    int r_max = 12;
    int g_max = 13;
    int b_max = 14;

    for (int i = 0; i < NUM_GAMES; i++) {
        round_node* game_rounds = games[i];
        int is_valid = 1;
        for (round_node* round = game_rounds; round != NULL; round = round->next) {
            if (
                round->data->r_num > r_max ||
                round->data->g_num > g_max ||
                round->data->b_num > b_max
            ) {
                is_valid = 0;
                break;
            }
        }
        if (is_valid) {
            int game_id = i + 1;
            game_id_sum += game_id;
        }
    }

    return game_id_sum;
}

round* get_min_set(round_node* game_rounds) {
    int r_min, g_min, b_min;
    r_min = game_rounds->data->r_num;
    g_min = game_rounds->data->g_num;
    b_min = game_rounds->data->b_num;

    for (round_node* round = game_rounds; round != NULL; round = round->next) {
        if (round->data->r_num > r_min) {
            r_min = round->data->r_num;
        }
        if (round->data->g_num > g_min) {
            g_min = round->data->g_num;
        }
        if (round->data->b_num > b_min) {
            b_min = round->data->b_num;
        }
    }

    round* min_data = (round*)malloc(sizeof(round));
    min_data->r_num = r_min;
    min_data->g_num = g_min;
    min_data->b_num = b_min;
    return min_data;
}

int round_powers(round* round) {
    return round->r_num * round->g_num * round->b_num;
}

// Part 2
int get_min_set_powers_sum(round_node* games[NUM_GAMES]) {
    int power_sum = 0;

    for (int i = 0; i < NUM_GAMES; i++) {
        round_node* rounds = games[i];
        round* min_set = get_min_set(rounds);
        power_sum += round_powers(min_set);
    }

    return power_sum;
}

int main() {
    char line[MAX_LINE];
    round_node* games[NUM_GAMES];
    int i = 0;
    char *saveptr;

    // Load game data into array
    while(fgets(line, MAX_LINE, stdin)) {
        char *game_str = get_game_str(line);
        round_node* game_rounds = NULL;

        char *round_str = strtok_r(game_str, ";", &saveptr);
        while (round_str != NULL) {
            round* round_data = get_round_data(round_str);

            round_node* new_round_node = (round_node*)malloc(sizeof(round_node));
            new_round_node->data = round_data;

            round_node* temp = game_rounds;
            new_round_node->next = temp;
            game_rounds = new_round_node;

            round_str = strtok_r(NULL, ";", &saveptr);
        }

        games[i] = game_rounds;
        i++;
    }

    printf("%d\n", calculate_valid_game_sum(games));
    printf("%d\n", get_min_set_powers_sum(games));
    return 0;
}