#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define HAND_SIZE 5
#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_HAND_TYPES 14
#define TRUE 1
#define FALSE 0
#define BOOLEAN int

// card types

// rank of cards Ace - King (though Ace can go low or high in a poker hand)
typedef enum {
  ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
} Rank;

const char* rank_names[NUM_RANKS] =
{ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", 
  "TEN", "JACK", "QUEEN", "KING"  };

typedef enum {
  CLUBS, DIAMONDS, HEARTS, SPADES
} Suit;

const char* suit_names[NUM_SUITS] =
{ "CLUBS", "DIAMONDS", "HEARTS", "SPADES" };

typedef enum {
  STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, 
  THREE_OF_A_KIND, TWO_PAIR, ONE_PAIR, FOUR_FLUSH, THREE_FLUSH, 
  FOUR_STRAIGHT, THREE_STRAIGHT, BUPKISS, NO_TYPE
} HandType;

const char* type_names[NUM_HAND_TYPES] =
{ 
  "STRAIGHT_FLUSH", "FOUR_OF_A_KIND", "FULL_HOUSE", "FLUSH", "STRAIGHT", 
  "THREE_OF_A_KIND", "TWO_PAIR", "ONE_PAIR", "FOUR_FLUSH", "THREE_FLUSH", 
  "FOUR_STRAIGHT", "THREE_STRAIGHT", "NADA", "NO_TYPE"
};

// deck/card types

// Playing card = (suit, rank)
typedef struct {
  Suit suit;
  Rank rank;
} Card;

// this is a hand being played
typedef struct {
  Card cards[HAND_SIZE];
  int rank_ct[NUM_RANKS];
  int suit_ct[NUM_SUITS];
  HandType type;
} Hand;

// this is the deck being used
typedef struct {
  Card cards[DECK_SIZE];
  int size;
} Deck;


// set up the deck
void init_deck(Deck &deck) {
  srand((int)time(NULL));
  deck.size = DECK_SIZE;
  for (int i = 0; i < NUM_SUITS; i++) {
    for (int j = 0; j < NUM_RANKS; j++) {
      int card_no = i * NUM_RANKS + j;
      deck.cards[card_no].suit = (Suit) i;
      if (i == 52)
        int a = 1;
      deck.cards[card_no].rank = (Rank) j;
    }
  }
}

// select card from deck[0:size-1], shuffle cards down, shrink size (which must be > 0), and return card
Card deal_card(Deck &deck) {
  // find card to return
  int next_no = deck.size * (rand() / ((double) RAND_MAX));
  if (next_no < 0 || next_no > 51)
    int c = 2;
  Card next_card = deck.cards[next_no];
  if ((int) next_card.suit == 52)
    int b=2;
  for (int i = next_no; i < deck.size - 1; i++)
  {
    deck.cards[i] = deck.cards[i+1];
  }
  //deck.size = DECK_SIZE;
  deck.size--;
  return next_card;
}

// count the ranks of cards in a hand (rank_count[NUM_RANKS])
void count_ranks(Hand &hand) {
  // set up the rank counts
  for (int i = 0; i < NUM_RANKS; i++)
    hand.rank_ct[i] = 0;
  // count the hand ranks
  for (int i = 0; i < HAND_SIZE; i++)
    hand.rank_ct[hand.cards[i].rank]++;
}

// count the suits of cards in a hand (suit_count[NUM_SUITS])
void count_suits(Hand &hand) {
  // set up the suit counts
  for (int i = 0; i < NUM_SUITS; i++)
    hand.suit_ct[i] = 0;
  // count the hand suits
  for (int i = 0; i < HAND_SIZE; i++)
    hand.suit_ct[hand.cards[i].suit]++;
}

// detect if hand is a flush
HandType flush_type(Hand &hand) {
  // check for a flush
  for (int i = 0; i < NUM_SUITS; i++)
    if (hand.suit_ct[i] == 5)
      return FLUSH;
    else if (hand.suit_ct[i] == 4)
      return FOUR_FLUSH;
    else if (hand.suit_ct[i] == 3)
      return THREE_FLUSH;
  return NO_TYPE;
}

// detect multiples
HandType multiple_type(Hand &hand) {
  // check for a pair
  BOOLEAN saw_three = FALSE;
  int pair_ct = 0;
  for (int i = 0; i < NUM_RANKS; i++) {
    if (hand.rank_ct[i] == 4)
      return FOUR_OF_A_KIND;
  else if (hand.rank_ct[i] == 3)
      saw_three == true;
  else if (hand.rank_ct[i] == 2)
      pair_ct++;
  }
  if (saw_three && pair_ct)
    return FULL_HOUSE;
  else if (pair_ct == 2)
    return TWO_PAIR;
  else if (pair_ct == 1)
    return ONE_PAIR;
  else
    return NO_TYPE;
}

// detect straight
HandType straight_type(Hand &hand) {
  // check for a straight
  BOOLEAN saw_straight = FALSE;
  int seq_ct = 0;
  int max_seq = 0;
  for (int i = 0; i < NUM_RANKS; i++)
    if (hand.rank_ct[i] == 1) {
      seq_ct++;
      if (seq_ct > max_seq)
        max_seq = seq_ct;
    } else
      seq_ct = 0;
  if (max_seq == 5)
    return STRAIGHT;
  else if (max_seq == 4)
    return FOUR_STRAIGHT;
  else if (max_seq == 3)
    return THREE_STRAIGHT;
  return NO_TYPE;
}

void evaluate_hand(Hand &hand) {
  HandType flushType = flush_type(hand);
  HandType straightType = straight_type(hand);
  HandType multipleType = multiple_type(hand);
  if (flushType == FLUSH && straightType == STRAIGHT) 
    return STRAIGHT_FLUSH;
  else if (multipleType == FOUR_OF_A_KIND)
    return FOUR_OF_A_KIND;
  else if (multipleType == FULL_HOUSE)
    return FULL_HOUSE;
  else if (flushType = FLUSH) 
    return FLUSH;
  else if (straightType = STRAIGHT) 
    return STRAIGHT;
  else if (multipleType == THREE_OF_A_KIND)
    return THREE_OF_A_KIND;
  else if (multipleType == TWO_PAIR)
    return TWO_PAIR;
  else if (multipleType == ONE_PAIR)
    return ONE_PAIR;
  else if (flushType == FOUR_FLUSH || flushType == THREE_FLUSH)
    return flushType;
  else if (straightType == FOUR_STRAIGHT || straightType == THREE_STRAIGHT)
    return straightType;
  return BUPKISS;
}

// deal hand Card[HAND_SIZE] from deck[DECK_SIZE]
HandType deal_hand(Hand &hand, Deck &deck) {
  for (int i = 0; i < HAND_SIZE; i++) {
    hand.cards[i] = deal_card(deck);
  }
  count_ranks(hand);
  count_suits(hand);
  evaluate_hand(hand);
  return handType;
}

// format card into string
void card_format(Card card, char card_string[]) {
  if (card.suit < 0 || card.suit > 3)
    int a = 1;
  sprintf(card_string, "%s of %s ", 
  rank_names[card.rank], suit_names[card.suit]);
}

// format hand into string
void hand_format(Hand &hand, char card_string[]) {
  sprintf(card_string, "%s", type_names[hand.type]);
}
int main(int argc, char** argv) {
  Deck deck;
  Hand hand1;
  Hand hand2;
  int type_ct[NUM_HAND_TYPES];
  /*
  if (argc < 2) {
    printf("usage: %s count\n", argv[0]);
    exit(0);
  }
  */
  int count = 1; // atoi(argv[1]); printf("%d\n", count);
  for (int j = 0; j < count; j++) {
    printf("hand %d.\n", j);
    init_deck(deck);
    deal_hand(hand1, deck);
    deal_hand(hand2, deck);
    char card1_string[100];
    char card2_string[100];
    // show them their hand
    hand_format(hand1, card1_string);
    printf("You have %s:\n", card1_string);
    for (int i = 0; i < HAND_SIZE; i++) {
      card_format(hand1.cards[i], card1_string);
      printf("%-17s ", card1_string);
    }
    printf("\n");
    // show them their hand
    printf("My hand:\n");
    hand_format(hand2, card2_string);
    printf("%-8s: ", card2_string);
    for (int i = 0; i < HAND_SIZE; i++) {
      card_format(hand2.cards[i], card2_string);
      printf("%-17s ", card2_string);
    }
    printf("\n\n");
  }
}




