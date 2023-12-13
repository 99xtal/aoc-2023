#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1000
#define GRID_W 140
#define GRID_H 140

#define START_CH 'S'
#define NS_CH '|'
#define EW_CH '-'
#define NE_CH 'L'
#define NW_CH 'J'
#define SW_CH '7'
#define SE_CH 'F'

typedef enum { N, S, E, W } direction_t;

direction_t get_next_direction(direction_t current_dir, char current_char) {
    direction_t dir = current_dir;
    switch (current_char) {
        case NE_CH:
            if (current_dir == S) {
                dir = E;
            } else if (current_dir == W) {
                dir = N;
            }
            break;
        case NW_CH:
            if (current_dir == S) {
                dir = W;
            } else if (current_dir == E) {
                dir = N;
            }
            break;
        case SW_CH:
            if (current_dir == N) {
                dir = W;
            } else if (current_dir == E) {
                dir = S;
            }
            break;
        case SE_CH:
            if (current_dir == N) {
                dir = E;
            } else if (current_dir == W) {
                dir = S;
            }
            break;
        case NS_CH:
        case EW_CH:
        default:
            break;
    }
    return dir;
}

int main(void) {
    char line[MAX_BUFFER];
    char grid[GRID_W][GRID_H];
    int start_x, start_y;

    // Read grid into 2D array and find start location
    for (int y = 0; y < GRID_H; y++) {
        fgets(line, MAX_BUFFER, stdin);
        for (int x = 0; x < GRID_W; x++) {
            grid[x][y] = line[x];

            if (line[x] == START_CH) {
                start_x = x;
                start_y = y;
            }
        }
    }

    // Get starting position and direction
    int dir, c_x, c_y;
    c_x = start_x;
    c_y = start_y;
    int step = 1;
    if (grid[start_x][start_y - 1] == NS_CH || 
        grid[start_x][start_y - 1] == SE_CH ||
        grid[start_x][start_y - 1] == SW_CH
    ) {
        dir = N;
        c_y -= 1;
    } else if (
        grid[start_x + 1][start_y] == EW_CH ||
        grid[start_x + 1][start_y] == NW_CH ||
        grid[start_x + 1][start_y] == SW_CH
    ) {
        dir = E;
        c_x += 1;
    } else if (
        grid[start_x][start_y + 1] == NS_CH ||
        grid[start_x][start_y + 1] == NE_CH ||
        grid[start_x][start_y + 1] == NW_CH
    ) {
        dir = S;
        c_y += 1;
    } else {
        dir = W;
        c_x -= 1;
    }

    // Walk loop until back at starting position
    while (grid[c_x][c_y] != START_CH) {
        printf("Step %d\tchar@(%d,%d): %c, dir: %d\n", step, c_x, c_y, grid[c_x][c_y], dir);
        // Get next direction
        dir = get_next_direction(dir, grid[c_x][c_y]);

        // move cursor
        switch (dir) {
            case N:
                c_y -= 1;
                break;
            case E:
                c_x += 1;
                break;
            case S:
                c_y += 1;
                break;
            case W:
                c_x -= 1;
                break;
            default:
                break;
        }
        step++;
    } 

    printf("%d\n", step / 2);
}
