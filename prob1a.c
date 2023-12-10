#include <ctype.h>
#include <stdio.h>
#include <time.h>

#define MAXLINE 100

int ctoi(char c) {
    return c - '0';
}

int main() {
    int sum = 0;
    char line[MAXLINE];
    int first_digit = 0;
    int last_digit = 0;

    clock_t start_t, end_t;
    start_t = clock();

    while(fgets(line, sizeof(line) / sizeof(char), stdin) != NULL) {
        int i = 0;
        do {
            if (isdigit(line[i])) {
                if (!first_digit) {
                    first_digit = ctoi(line[i]);
                } 
                last_digit = ctoi(line[i]);
            }
        } while(line[i++] != '\0');

        sum += (first_digit * 10) + last_digit;
        first_digit = 0;
        last_digit = 0;
    }

    printf("%d\n", sum);

    end_t = clock();
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC * 1000;
    printf("%.2fms\n", total_t);
}