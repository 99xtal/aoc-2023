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

    printf("%d\n", parts_sum);
    return 0;
}