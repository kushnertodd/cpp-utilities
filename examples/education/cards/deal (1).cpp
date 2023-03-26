#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define HAND_SIZE 5
#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_HAND_TYPES 9
#define TRUE 1
#define FALSE 0
#define BOOLEAN int

// card types

// rank of cards Ace - King (though Ace can go low or high in a poker hand)
typedef enum {
  ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
} Rank;

const char* rank_names[NUM_RANKS] =
{ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"  };

typedef enum {
  CLUBS, DIAMONDS, HEARTS, SPADES
} Suit;

const char* suit_names[NUM_SUITS] =
{ "CLUBS", "DIAMONDS", "HEARTS", "SPADES" };

typedef enum {
  STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_A_KIND, TWO_PAIR, PAIR, BUPKISS
} HandType;

const char* type_names[NUM_HAND_TYPES] =
{ "A STRAIGHT_FLUSH", "FOUR_OF_A_KIND", "A FULL_HOUSE", "A FLUSH", "A STRAIGHT", "THREE_OF_A_KIND", "TWO_PAIR", "A PAIR", "NADA" };

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
      deck.cards[card_no].rank = (Rank) j;
      if (i == 52)
        int b = 2;
    }
  }
}

// select card from deck[0:size-1], shuffle cards down, shrink size (which must be > 0), and return card
Card deal_card(Deck &deck) {
  // find card to return
  int next_no = deck.size * (rand() / ((double) RAND_MAX));
  Card next_card = deck.cards[next_no];
  for (int i = next_no; i < deck.size; i++)
  {
    deck.cards[i] = deck.cards[i+1];
    if (deck.cards[i].suit == (Suit) 52)
      int c = 3;
  }
  deck.size = DECK_SIZE;
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
BOOLEAN is_flush(Hand &hand) {
  // check for a flush
  BOOLEAN saw_flush = FALSE;
  for (int i = 0; i < NUM_SUITS; i++)
    if (hand.suit_ct[i] == 5)
      saw_flush = TRUE;
  return saw_flush;
}

// detect four of a kind
BOOLEAN is_four_of_a_kind(Hand hand) {
  // check for a four_of_a_kind
  BOOLEAN saw_four_of_a_kind = FALSE;
  for (int i = 0; i < NUM_RANKS; i++)
    if (hand.rank_ct[i] == 4)
      saw_four_of_a_kind = TRUE;
  return saw_four_of_a_kind;
}

// detect two of a kind
BOOLEAN is_pair(Hand &hand) {
  // check for a pair
  BOOLEAN saw_pair = FALSE;
  for (int i = 0; i < NUM_RANKS; i++)
    if (hand.rank_ct[i] == 2)
      saw_pair = TRUE;
  return saw_pair;
}

// detect straight
BOOLEAN is_straight(Hand &hand) {
  // check for a straight
  BOOLEAN saw_straight = FALSE;
  int seq_ct = 0;
  for (int i = 0; i < NUM_RANKS; i++)
    if (hand.rank_ct[i] == 1) {
      seq_ct++;
      if (seq_ct == 5)
        saw_straight = TRUE;
    } else
      seq_ct = 0;
  return saw_straight;
}

// detect three of a kind
BOOLEAN is_three_of_a_kind(Hand &hand) {
  // check for a three_of_a_kind
  BOOLEAN saw_three_of_a_kind = FALSE;
  for (int i = 0; i < NUM_RANKS; i++)
    if (hand.rank_ct[i] == 3)
      saw_three_of_a_kind = TRUE;
  return saw_three_of_a_kind;
}

BOOLEAN is_full_house(Hand &hand) {
  return is_three_of_a_kind(hand) && is_pair(hand);
}

// detect two pair
BOOLEAN is_two_pair(Hand &hand) {
  // check for two pair
  BOOLEAN saw_one_pair = FALSE;
  BOOLEAN saw_two_pair = FALSE;
  for (int i = 0; i < NUM_RANKS; i++) {
    if (hand.rank_ct[i] == 2) {
      if (saw_one_pair)
        saw_two_pair = TRUE;
      else
        saw_one_pair = TRUE;
    }
  }
  return saw_two_pair;
}

BOOLEAN is_straight_flush(Hand &hand) {
  return is_straight(hand) && is_flush(hand);
}

void evaluate_hand(Hand &hand) {
  if (is_straight_flush(hand)) {
//    printf("is straight flush\n");
    hand.type = STRAIGHT_FLUSH;
  }
  else if (is_four_of_a_kind(hand)) {
//    printf("is four of a kind\n");
    hand.type = FOUR_OF_A_KIND;
  }
  else if (is_full_house(hand)) {
//    printf("is full house\n");
    hand.type = FULL_HOUSE;
  }
  else if (is_flush(hand)) {
//    printf("is flush\n");
    hand.type = FLUSH;
  }
  else if (is_straight(hand)) {
//    printf("is straight\n");
    hand.type = STRAIGHT;
  }
  else if (is_three_of_a_kind(hand)) {
//    printf("is three of a kind\n");
    hand.type = THREE_OF_A_KIND;
  }
  else if (is_two_pair(hand)) {
//    printf("is two pair\n");
    hand.type = TWO_PAIR;
  }
  else if (is_pair(hand)) {
//    printf("is pair\n");
    hand.type = PAIR;
  }
  else {
//    printf("is bupkiss\n");
    hand.type = BUPKISS;
  }
}

// deal hand Card[HAND_SIZE] from deck[DECK_SIZE]
void deal_hand(Hand &hand, Deck &deck) {
  for (int i = 0; i < HAND_SIZE; i++)
    hand.cards[i] = deal_card(deck);
  count_ranks(hand);
  count_suits(hand);
  evaluate_hand(hand);
}

// format card into string
void card_format(Card card, char card_string[]) {
  if (card.suit < 0 || card.suit > 3)
    int a = 1;
  sprintf(card_string, "%s of %s ", 
  rank_names[card.rank], suit_names[card.suit]);
  //sprintf(card_string, "%s [%d] of %s [%d]", 
  //rank_names[card.rank], card.rank, suit_names[card.suit], card.suit);
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
  if (argc < 2) {
    printf("usage: %s count\n", argv[0]);
    exit(0);
  }
  int count = atoi(argv[1]);
  printf("%d\n", count);
  for (int j = 0; j < count; j++) {
    printf("hand %d.\n", j);
    init_deck(deck);
    deal_hand(hand1, deck);
    deal_hand(hand2, deck);
    char card_string[100];
    // show them their hand
    hand_format(hand1, card_string);
    printf("You have %s:\n", card_string);
    for (int i = 0; i < HAND_SIZE; i++) {
      card_format(hand1.cards[i], card_string);
      printf("%-17s ", card_string);
    }
    printf("\n");
    // show them their hand
    printf("My hand:\n");
    hand_format(hand2, card_string);
    printf("%-8s: ", card_string);
    for (int i = 0; i < HAND_SIZE; i++) {
      card_format(hand2.cards[i], card_string);
      printf("%-17s ", card_string);
    }
    printf("\n\n");
  }
}




