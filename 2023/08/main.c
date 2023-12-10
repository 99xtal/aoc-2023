#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  while(fgets(line, MAX_BUFFER, stdin) != NULL) {
    netnode_t *n = (netnode_t*)malloc(sizeof(netnode_t));

    sscanf(line, "%3s = (%3s, %3s)", n->node, n->left, n->right);
    network_map[hash(n->node)] = n;
  }

  // Walk network starting at "AAA"
  int step = 0;
  netnode_t* current_node = network_map[hash("AAA")];
  while (strcmp(current_node->node, "ZZZ") != 0) {
    char instruction = lr_instructions[step % num_instructions-1];

    if (instruction == 'L') {
      current_node = network_map[hash(current_node->left)];
    } else if (instruction == 'R') {
      current_node = network_map[hash(current_node->right)];
    }

    step++;
  }
  
  printf("%d\n", step);
  return 0;
}
