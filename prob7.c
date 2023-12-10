#include <stdio.h>
#include <stdlib.h>

#define NUM_HANDS 1000 

char cards[] = { 'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A' };

enum HandType {
  High,
  OnePair,
  TwoPair,
  ThreeOfAKind,
  FullHouse,
  FourOfAKind,
  FiveOfAKind,
};

typedef struct hand_t {
  char hand[6];
  int bid;
} hand_t;

int index_of(char *haystack, int h_size, char needle) {
  for(int i = 0; i < h_size; i++) {
    if (haystack[i] == needle) {
      return i;
    }
  }
  return -1;
}

int get_hand_type(char hand[6]) {
  char card_freq[255];
  for (int i = '2'; i <= 'T'; i++) {
    card_freq[i] = 0;
  }

  for(int i = 0; i < 5; i++) {
    card_freq[(int)hand[i]] += 1;
  }

  int highest = 0;
  int second_highest = 0;
  for(int i = '2'; i <= 'T'; i++) {
    if (i == 'J') continue;
    if (card_freq[i] > highest) {
      second_highest = highest;
      highest = card_freq[i];
    } else if (card_freq[i] >= second_highest) {
      second_highest = card_freq[i];
    }
  }

  highest += card_freq['J'];

  switch(highest) {
    case 5:
      return FiveOfAKind;
    case 4:
      return FourOfAKind;
    case 3:
      switch(second_highest) {
        case 2:
          return FullHouse;
        default:
          return ThreeOfAKind;
      }
    case 2:
      switch(second_highest) {
        case 2:
          return TwoPair;
        default:
          return OnePair;
      }
    default:
      return High;
  }
}

int compare_hands(const void* a, const void* b) {
  char* hand_a = ((hand_t*)a)->hand;
  char* hand_b = ((hand_t*)b)->hand;
  int a_type = get_hand_type(hand_a);
  int b_type = get_hand_type(hand_b);

  if (a_type != b_type) {
    return a_type - b_type;
  }

  for (int i = 0; i < 6; i++) {
    int card_a = index_of(cards, 14, hand_a[i]);
    int card_b = index_of(cards, 14, hand_b[i]);
    if(card_a != card_b) {
        return card_a - card_b;
    }
  }

  return 0;
}

int main(void) {
  hand_t hands[NUM_HANDS];

  for(int i = 0; i < NUM_HANDS; i++) {
    hand_t hand;
    fscanf(stdin, "%5s %d", &hand.hand, &hand.bid);
    hands[i] = hand;
  }

  qsort(hands, NUM_HANDS, sizeof(hand_t), &compare_hands);

  int total_winnings = 0;
  for(int i = 0; i < NUM_HANDS; i++) {
    int rank = i + 1;
    int win = rank * hands[i].bid;
    total_winnings += win;
  }

  printf("%d\n", total_winnings);
  return 0;
}

