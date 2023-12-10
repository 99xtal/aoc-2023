#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arith.h"

#define MAX_BUFFER 1028
// Decimal value of ZZZ
#define HASH_SIZE 17576

typedef struct netnode_t {
  char node[4];
  char left[4];
  char right[4];
} netnode_t;

/*
 *  Treating the node name like a base-26 number where A=0, Z=25,
 *  convert to a decimal number to generate a unique index in the
 *  network table.
 */
int hash(char* s) {
  return pow(26,2)*((int)s[0] - 'A') + pow(26,1)*((int)s[1] - 'A') + (int)s[2] - 'A';
}

int main(void) {
  char line[MAX_BUFFER];
  char* lr_instructions;
  int num_instructions;
  netnode_t* network_map[HASH_SIZE];

  // Get instructions
  fgets(line, MAX_BUFFER, stdin);
  lr_instructions = strdup(line);
  num_instructions = strlen(lr_instructions) - 1;

  // Read nodes into network table
  char* starting_nodes[6];
  int starting_counts[6];
  int starting_count = 0;
  while(fgets(line, MAX_BUFFER, stdin) != NULL) {
    netnode_t *n = (netnode_t*)malloc(sizeof(netnode_t));

    sscanf(line, "%3s = (%3s, %3s)", n->node, n->left, n->right);
    if (n->node[2] == 'A') {
      starting_nodes[starting_count] = n->node;
      starting_count++;
    }
    network_map[hash(n->node)] = n;
  }

  // Walk network starting at "AAA"
  int step = 0;
  char* current_node = "AAA"; 
  while (strcmp(current_node, "ZZZ") != 0) {
    char instruction = lr_instructions[step % num_instructions];
    netnode_t* n = network_map[hash(current_node)];

    if (instruction == 'L') {
      current_node = n->left;
    } else if (instruction == 'R') {
      current_node = n->right;
    }

    step++;
  }
  
  printf("%d\n", step);

  for (int i = 0; i < 6; i++) {
    step = 0;
    char* current_node = starting_nodes[i];
    while (current_node[2] != 'Z') {
      char instruction = lr_instructions[step % num_instructions];
      netnode_t* n = network_map[hash(current_node)];

      if (instruction == 'L') {
        current_node = n->left;
      } else if (instruction == 'R') {
        current_node = n->right;
      }
      step++;
    }
    starting_counts[i] = step;
  }

  printf("%llu\n", lcm_arr(starting_counts, 6));
  return 0;
}
