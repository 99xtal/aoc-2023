#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SEEDS 20

enum MapType {
    SEED_TO_SOIL,
    SOIL_TO_FERT,
    FERT_TO_WATER,
    WATER_TO_LIGHT,
    LIGHT_TO_TEMP,
    TEMP_TO_HUM,
    HUM_TO_LOC,
};

typedef struct node {
    void *data;
    struct node *next;
} node;

typedef struct map {
    uint64_t source_range_st;
    uint64_t dest_range_st;
    uint64_t range_length;
} map;

uint64_t get_dest_from_map(uint64_t source, node* maps) {
    for (node* p = maps; p != NULL; p = p->next) {
        map* data = (map*)p->data;
        if (source >= data->source_range_st && source < data->source_range_st + data->range_length) {
            return (source - data->source_range_st) + data->dest_range_st;
        }
    }
    return source;
}

int main(void) {
    char line[1000];
    uint64_t seeds[NUM_SEEDS];
    int current_map_type = SEED_TO_SOIL;
    node* seed_to_soil_maps = NULL;
    node* soil_to_fert_maps = NULL;
    node* fert_to_water_maps = NULL;
    node* water_to_light_maps = NULL;
    node* light_to_temp_maps = NULL;
    node* temp_to_hum_maps = NULL;
    node* hum_to_loc_maps = NULL;

    while(fgets(line, 1000, stdin) != NULL) {
        if (strstr(line, "seeds") != NULL) {
            int i = 0;
            char *saveptr1, *saveptr2;
            strtok_r(line, ":", &saveptr1);
            char* seeds_str = strtok_r(NULL, ":", &saveptr1);
            
            char* num_str = strtok_r(strdup(seeds_str), " ", &saveptr2);
            seeds[i++] = atoi(num_str);
            while((num_str = strtok_r(NULL, " ", &saveptr2)) != NULL) {
                seeds[i++] = atoi(num_str);
            }
        } else if (strstr(line, "seed-to-soil") != NULL) {
            current_map_type = SEED_TO_SOIL;
        } else if (strstr(line, "soil-to-fertilizer") != NULL) {
            current_map_type = SOIL_TO_FERT;
        } else if (strstr(line, "fertilizer-to-water") != NULL) {
            current_map_type = FERT_TO_WATER;
        } else if (strstr(line, "water-to-light") != NULL) {
            current_map_type = WATER_TO_LIGHT;
        } else if (strstr(line, "light-to-temperature") != NULL) {
            current_map_type = LIGHT_TO_TEMP;
        } else if (strstr(line, "temperature-to-humidity") != NULL) {
            current_map_type = TEMP_TO_HUM;
        } else if (strstr(line, "humidity-to-location") != NULL) {
            current_map_type = HUM_TO_LOC;
        } else if (isdigit(line[0])) {
            map* new_map = malloc(sizeof(map));
            sscanf(line, "%llu %llu %llu", &new_map->dest_range_st, &new_map->source_range_st, &new_map->range_length);

            node* map_node = malloc(sizeof(node));
            map_node->data = new_map;

            switch (current_map_type) {
            case SEED_TO_SOIL:
                map_node->next = seed_to_soil_maps;
                seed_to_soil_maps = map_node;
                break;
            case SOIL_TO_FERT:
                map_node->next = soil_to_fert_maps;
                soil_to_fert_maps = map_node;
                break;
            case FERT_TO_WATER:
                map_node->next = fert_to_water_maps;
                fert_to_water_maps = map_node;
                break;
            case WATER_TO_LIGHT:
                map_node->next = water_to_light_maps;
                water_to_light_maps = map_node;
                break;
            case LIGHT_TO_TEMP:
                map_node->next = light_to_temp_maps;
                light_to_temp_maps = map_node;
                break;
            case TEMP_TO_HUM:
                map_node->next = temp_to_hum_maps;
                temp_to_hum_maps = map_node;
                break;
            case HUM_TO_LOC:
                map_node->next = hum_to_loc_maps;
                hum_to_loc_maps = map_node;
            default:
                break;
            }
        }
    }

    uint64_t lowest = 0;
    for (int i = 0; i < NUM_SEEDS; i++) {
        uint64_t soil = get_dest_from_map(seeds[i], seed_to_soil_maps);
        uint64_t fert = get_dest_from_map(soil, soil_to_fert_maps);
        uint64_t water = get_dest_from_map(fert, fert_to_water_maps);
        uint64_t light = get_dest_from_map(water, water_to_light_maps);
        uint64_t temp = get_dest_from_map(light, light_to_temp_maps);
        uint64_t hum = get_dest_from_map(temp, temp_to_hum_maps);
        uint64_t loc = get_dest_from_map(hum, hum_to_loc_maps);
        if (loc < lowest || lowest == 0) {
            lowest = loc;
        }
    }

    printf("%llu\n", lowest);

    printf("Part 2\n");

    uint64_t seed, range;
    uint64_t new_lowest = 0;
    for (int i = 0; i < NUM_SEEDS; i += 2) {
        seed = seeds[i];
        range = seeds[i+1];
        printf("Seed %d: start: %llu\t end:%llu\n", i+1, seed, seed + range - 1);
        for (u_int64_t j = seed; j < seed + range; j++) {
            uint64_t soil = get_dest_from_map(j, seed_to_soil_maps);
            uint64_t fert = get_dest_from_map(soil, soil_to_fert_maps);
            uint64_t water = get_dest_from_map(fert, fert_to_water_maps);
            uint64_t light = get_dest_from_map(water, water_to_light_maps);
            uint64_t temp = get_dest_from_map(light, light_to_temp_maps);
            uint64_t hum = get_dest_from_map(temp, temp_to_hum_maps);
            uint64_t loc = get_dest_from_map(hum, hum_to_loc_maps);
            if (loc < new_lowest || new_lowest == 0) {
                new_lowest = loc;
                printf("New lowest: seed: %llu, loc: %llu\n", j, new_lowest);
            }
        }
    }

    printf("%llu\n", new_lowest);
    return 0;
}
