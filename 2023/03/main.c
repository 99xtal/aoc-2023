#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Dimensions of schematic
#define SCHEM_H 140
#define SCHEM_W 140

#define MAX_LINE 150

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

typedef struct position {
    int x;
    int y;
} position;

typedef struct position_node {
    position *pos;
    struct position_node *next;
} position_node;

typedef struct num_node {
    int num;
    struct num_node *next;
} num_node;

bool is_near_symbol(int num_x, int num_y, int num_len, char** schem) {
    int y_start = max(num_y - 1, 0);
    int y_end = min(num_y + 1, SCHEM_H - 1);
    int x_start = max(num_x - 1, 0);
    int x_end = min(num_x + num_len, SCHEM_W - 1);

    for (int y = y_start; y <= y_end; y++) {
        for (int x = x_start; x <= x_end; x++) {
            if (!isdigit(schem[y][x]) && schem[y][x] != '.') {
                return true;
            }
        }
    }
    return false;
}

num_node* get_adjacent_nums(position* source, char** schem) {
    int x_min = max(source->x - 1, 0);
    int x_max = min(source->x + 1, SCHEM_W - 1);
    int y_min = max(source->y - 1, 0);
    int y_max = min(source->y + 1, SCHEM_H - 1);
    char cursor;
    position_node* num_positions = NULL;

    int x, y;
    for (y = y_min; y <= y_max; y++) {
        for (x = x_min; x <= x_max; x++) {
            cursor = schem[y][x];
            if (isdigit(cursor)) {
                int i = x;
                while(isdigit(schem[y][max(i-1,0)]) && i > 0) {
                    i--;
                }

                position* num_i = (position*)malloc(sizeof(position));
                num_i->x = i;
                num_i->y = y;

                int dupes_n = 0;
                for (position_node* p = num_positions; p != NULL; p = p->next) {
                    if (p->pos->x == num_i->x && p->pos->y == num_i->y) {
                        dupes_n++;
                    }
                }

                if (dupes_n == 0) {
                    position_node* new_pos = (position_node*)malloc(sizeof(position_node));
                    new_pos->pos = num_i;
                    new_pos->next = num_positions;
                    num_positions = new_pos;
                }
            }
        }
    }

    num_node* nums = NULL;
    for (position_node* p = num_positions; p != NULL; p = p->next) {
        int num = 0;
        int x = p->pos->x;
        int y = p->pos->y;
        char cursor = schem[y][x];
        while(isdigit(cursor)) {
            num = (num * 10) + (cursor - '0');
            x++;
            cursor = schem[y][x];
        }
        num_node* new_node = (num_node*)malloc(sizeof(num_node));
        new_node->num = num;
        new_node->next = nums;
        nums = new_node;
    }

    return nums;
}

int main() {
    // Parse input data into 2D array
    char *schem[SCHEM_H];
    for (int i=0; i<SCHEM_H; i++) {
        char* schem_row = (char*)malloc(sizeof(char) * SCHEM_W);
        schem[i] = schem_row;
    }

    char line[MAX_LINE];
    int i = 0;
    while(fgets(line, MAX_LINE, stdin) != NULL) {
        for (int j=0; j<SCHEM_W; j++) {
            schem[i][j] = line[j];
        }
        i++;
    }

    // Part 1 solution
    char cursor;
    int num_index = -1;
    int num_length;
    int num_value;
    int parts_sum = 0;

    for (int i = 0; i < SCHEM_H; i++) {
        for (int j = 0; j < SCHEM_W; j++) {
            cursor = schem[i][j];

            // At end of number
            if (num_index != -1 && (!isdigit(cursor) || j < num_index)) {
                if (is_near_symbol(num_index, i, num_length, schem)) {
                    parts_sum += num_value;
                }

                num_index = -1;
                num_length = 0;
                num_value = 0; 
            }

            // At start of number
            if (num_index == -1 && isdigit(cursor)) {
                num_index = j;
                num_length = 1;
                num_value = cursor - '0';
            } else if (num_index != -1 && isdigit(cursor)) {
                num_length++;
                num_value = (num_value * 10) + (cursor - '0');
            }
        }
    }

    // Part 2 solution
    int gear_ratio_sum = 0;
    for (int i = 0; i < SCHEM_H; i++) {
        for (int j = 0; j < SCHEM_W; j++) {
            cursor = schem[i][j];
            num_node* nums;

            if (cursor == '*') {
                position p;
                p.x = j;
                p.y = i;
                nums = get_adjacent_nums(&p, schem);

                int gear_ratio = 1;
                int num_part_nums = 0;
                for (num_node* p = nums; p != NULL; p = p->next) {
                    gear_ratio *= p->num;
                    num_part_nums++;
                }
                
                if (num_part_nums == 2) {
                    gear_ratio_sum += gear_ratio;
                }
            }
        }
    }

    printf("Part number sum: %d\n", parts_sum);
    printf("Gear ratio sum: %d\n", gear_ratio_sum);
    return 0;
}