#include <stdio.h>
#include <string.h>


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

int first_digit_in_string(char* line) {
    int first_digit = -1;
    int first_digit_index = -1;

    // Find index of first occurance of one of the digit strings
    int arr_len = sizeof(digit_strings) / sizeof(char*);
    for (int i = 1; i < arr_len; i++) {
        char* substring = strstr(line, digit_strings[i]);

        if (substring != NULL) { 
            int index = substring - line;
            if (index < first_digit_index || first_digit_index == -1) {
                first_digit_index = index;
                first_digit = i;
            }
        }
    }
    
    // Find index of first occurance of one of the digit characters
    for (int i = 0; i <= 9; i++) {
        char num = '0' + i;
        char* first_char = strchr(line, num);
        if (first_char != NULL) {
            int index = first_char - line;
            if (index < first_digit_index || first_digit_index == -1) {
                first_digit_index = index;
                first_digit = i; 
            }
        }
    }

    return first_digit;
}

int last_digit_in_string(char *line) {
    int last_digit = -1;
    int last_digit_index = -1;

    // Find index of last occurance of one of the digit strings
    int arr_len = sizeof(digit_strings) / sizeof(char*);
    for (int i = 1; i < arr_len; i++) {
        char* substring = strstr_last(line, digit_strings[i]);

        if (substring != NULL) { 
            int index = substring - line;
            if (index > last_digit_index || last_digit_index == -1) {
                last_digit_index = index;
                last_digit = i; 
            }
        }
    }
    
    // Find index of last occurance of one of the digit characters
    for (int i = 0; i <= 9; i++) {
        char num = '0' + i;
        char* num_char = strrchr(line, num);
        if (num_char != NULL) {
            int index = num_char - line;
            if (index > last_digit_index || last_digit_index == -1) {
                last_digit_index = index;
                last_digit = i; 
            }
        }
    }

    return last_digit;
}

int main() {
    int sum = 0;
    char line[MAXLINE];
    int first_digit = 0;
    int last_digit = 0;

    while(fgets(line, sizeof(line) / sizeof(char), stdin) != NULL) {
        first_digit = first_digit_in_string(line);
        last_digit = last_digit_in_string(line);
        sum += (first_digit * 10) + last_digit;
    }

    printf("%d\n", sum);
}