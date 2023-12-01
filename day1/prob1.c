#include <ctype.h>
#include <stdio.h>

#define MAXLINE 100

int ctoi(char c) {
    return c - '0';
}

int main() {
    int sum = 0;
    char line[MAXLINE];
    int first_digit = 0;
    int last_digit = 0;

    while(fgets(line, sizeof(line), stdin) != NULL) {
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
}