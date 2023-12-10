#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINE 100

char* digit_strings[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

char* strstr_last(char *s, char *sub) {
    char* substring = strstr(s, sub);
    char* last = NULL;
    while (substring != NULL) {
        last = substring;
        substring = strstr(substring + 1, sub);
    }
    return last;
}

int main() {
    int sum = 0;
    char line[MAXLINE];

    clock_t start_t, end_t;
    start_t = clock();

    while(fgets(line, sizeof(line) / sizeof(char), stdin) != NULL) {
        int first_digit = 0;
        int first_digit_index = -1;
        int last_digit = 0;
        int last_digit_index = -1;
        
        // Check numeric substrings
        for (int i = 1; i < sizeof(digit_strings) / sizeof(char*); i++) {

            // Get first and last occurence of numeric strings in line
            char* first_substr = strstr(line, digit_strings[i]);
            if (first_substr != NULL) { 
                int index = first_substr - line;
                if (index < first_digit_index || first_digit_index == -1) {
                    first_digit_index = index;
                    first_digit = i;
                }
            }

            char* last_substr = strstr_last(line, digit_strings[i]);
            if (last_substr != NULL) { 
                int index = last_substr - line;
                if (index > last_digit_index || last_digit_index == -1) {
                    last_digit_index = index;
                    last_digit = i; 
                }
            }
        }

        // Check numeric characters
        for (int i = 0; i <= 9; i++) {
            char num_char = '0' + i;

           // Get first and last occurence of digit character in line
            char* first_num_substr = strchr(line, num_char);
            if (first_num_substr != NULL) {
                int index = first_num_substr - line;
                if (index < first_digit_index || first_digit_index == -1) {
                    first_digit_index = index;
                    first_digit = i;
                }
            }
            char* last_num_substr = strrchr(line, num_char);
            if (last_num_substr != NULL) {
                int index = last_num_substr - line;
                if (index > last_digit_index || last_digit_index == -1) {
                    last_digit_index = index;
                    last_digit = i; 
                }
            }
        }

        sum += (first_digit * 10) + last_digit;
    }

    printf("%d\n", sum);

    end_t = clock();
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC * 1000;
    printf("%.2fms\n", total_t);
}