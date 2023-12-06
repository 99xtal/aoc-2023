#include <stdio.h>
#include <math.h>

#define NUM_RACES 4

// Combined times from input (Part 2)
#define TIME_NUM 59707878L
// Combined distances from input (Part 2)
#define DISTANCE_NUM 430121812131276L

double lowest_quadratic_root(long a, long b, long c) {
    return ((b * -1) - sqrt(b*b - 4*a*c)) / 2*a;
}

/**
 * In order to get the distance traveled after time spent setting the speed:
 * distance = speed * (time - time_charging)    (where time_charging = speed)
 * 
 * Which can be written as a quadratic equation:
 * speed^2 - time*speed + distance = 0
 * 
 * Solving for the lowest value of speed will give the exact amount of time
 * needed to hold the button to meet the record distance.
 * 
 * To get the number of integer speeds between 0 and time (max speed), subtract
 * the first and last n=min_speed numbers from speed;
 */
unsigned long get_num_possible_record_breaks(unsigned long time, unsigned long rec_distance) {
    unsigned long min_speed = ceil(lowest_quadratic_root(1, time * -1, rec_distance));
    unsigned long num = time - (2 * min_speed) + 1;
    return num;
}

int main(void) {
    int race_times[NUM_RACES];
    int race_distances[NUM_RACES];
    
    fscanf(stdin, "%*s %d %d %d %d", &race_times[0], &race_times[1], &race_times[2], &race_times[3]);
    fscanf(stdin, "%*s %d %d %d %d", &race_distances[0], &race_distances[1], &race_distances[2], &race_distances[3]);

    // Part 1
    int num_product = 1;
    for (int i = 0; i < NUM_RACES; i++) {
        num_product *= get_num_possible_record_breaks(race_times[i], race_distances[i]);
    }

    printf("%d\n", num_product);

    // Part 2
    printf("%lu\n", get_num_possible_record_breaks(TIME_NUM, DISTANCE_NUM));
    return 0;
}
