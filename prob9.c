#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1000
#define NUM_HISTORY 21

void split_into_arr(int dest[], int dest_size, char* source, char* delim) {
    char* ptr;
    char* tok = strtok_r(source, delim, &ptr);
    dest[0] = atoi(tok);
    for (int i = 1; i < dest_size; i++) {
        dest[i] = atoi(strtok_r(NULL, delim, &ptr));
    }
}

int arr_sum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int extrapolate_value(int history[], int size) { 
    if (arr_sum(history, size) == 0) {
        return 0;
    }

    int diff_seq[size-1];
    for (int i = 0; i < size-1; i++) {
        diff_seq[i] = history[i+1] - history[i];
    }

    return history[size - 1] + extrapolate_value(diff_seq, size - 1);
}

int extrapolate_value_before(int history[], int size) {
    if (arr_sum(history, size) == 0) {
        return 0;
    }

    int diff_seq[size-1];
    for (int i = 0; i < size-1; i++) {
        diff_seq[i] = history[i+1] - history[i];
    }

    return history[0] - extrapolate_value_before(diff_seq, size - 1);
}

int main(void) {
    char line[MAX_BUFFER];
    int history[NUM_HISTORY];
    int extrapolated_sum = 0;
    int extrap_before_sum = 0;

    while (fgets(line, MAX_BUFFER, stdin) != NULL) {
        split_into_arr(history, NUM_HISTORY, line, " ");
        extrapolated_sum += extrapolate_value(history, NUM_HISTORY);
        extrap_before_sum += extrapolate_value_before(history, NUM_HISTORY);
    }

    printf("%d\n%d\n", extrapolated_sum, extrap_before_sum);
}
