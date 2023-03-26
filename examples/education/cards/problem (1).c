#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define HAND_SIZE 5
#define NUM_RANKS 13
#define NUM_SUITS 4
#define TRUE 1
#define FALSE 0
#define BOOLEAN int

// rank of cards Ace - King (though Ace can go low or high in a poker hand)
typedef enum {
    ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
} Rank;
char* rank_names[NUM_RANKS] =
{ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"  };
typedef enum {
    CLUBS, DIAMONDS, HEARTS, SPADES
} Suit;
char* suit_names[NUM_SUITS] =
{ "CLUBS", "DIAMONDS", "HEARTS", "SPADES" };
typedef enum {
    STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_A_KIND, TWO_PAIR, PAIR, BUPKISS
} HandType;
#define NUM_HAND_TYPES 9

// Playing card = (suit, rank)
typedef struct {
    Suit suit;
    Rank rank;
} Card;

// convert

// count the ranks of cards in a hand (rank_count[NUM_RANKS])
void count_ranks(Card hand[], int rank_ct[]) {
    // set up the rank counts
    for (int i = 0; i < NUM_RANKS; i++)
        rank_ct[i] = 0;
    // count the hand ranks
    for (int i = 0; i < HAND_SIZE; i++)
        rank_ct[hand[i].rank]++;
}

// count the suits of cards in a hand (suit_count[NUM_SUITS])
void count_suits(Card hand[], int suit_ct[]) {
    // set up the suit counts
    for (int i = 0; i < NUM_SUITS; i++)
        suit_ct[i] = 0;
    // count the hand suits
    for (int i = 0; i < HAND_SIZE; i++)
        suit_ct[hand[i].suit]++;
}

// select card from deck[0:size-1], shuffle cards down, shrink size (which must be > 0), and return card
Card deal(Card deck[], int* size) {
    // find card to return
    int next_no = *size * (rand() / ((double) RAND_MAX));
    Card next_card = deck[next_no];
    for (int i = next_no; i < *size; i++)
        deck[i] = deck[i+1];
    *size -= 1;
    return next_card;
}

// deal hand Card[HAND_SIZE] from deck[DECK_SIZE]
void deal_hand(Card hand[], Card deck[], int* size) {
    for (int i = 0; i < HAND_SIZE; i++)
        hand[i] = deal(deck, size);
}

// format card into string
void card_format(Card card, char card_string[]) {
    sprintf(card_string, "%s of %s", rank_names[card.rank], suit_names[card.suit]);
}

// set up the deck
void init_deck(Card deck[]) {
    for (int i = 0; i < NUM_SUITS; i++) {
        for (int j = 0; j < NUM_RANKS; j++) {
            int card_no = i * NUM_RANKS + j;
            deck[card_no].suit = i;
            deck[card_no].rank = j;
        }
    }
}

// detect if hand is a flush
BOOLEAN is_flush(Card hand[], int suit_ct[]) {
    // check for a flush
    BOOLEAN saw_flush = FALSE;
    for (int i = 0; i < NUM_SUITS; i++)
        if (suit_ct[i] == 5)
            saw_flush = TRUE;
    return saw_flush;
}

// detect four of a kind
BOOLEAN is_four_of_a_kind(Card hand[], int rank_ct[]) {
    // check for a four_of_a_kind
    BOOLEAN saw_four_of_a_kind = FALSE;
    for (int i = 0; i < NUM_RANKS; i++)
        if (rank_ct[i] == 4)
            saw_four_of_a_kind = TRUE;
    return saw_four_of_a_kind;
}

// detect full house
BOOLEAN is_straight(Card hand[], int rank_ct[]);
BOOLEAN is_flush(Card hand[], int suit_ct[]);
BOOLEAN is_straight_flush(Card hand[], int rank_ct[], int suit_ct[]) {
    return is_straight(hand, rank_ct) && is_flush(hand, suit_ct);
}
BOOLEAN is_three_of_a_kind(Card hand[], int rank_ct[]);
BOOLEAN is_pair(Card hand[], int rank_ct[]);
BOOLEAN is_full_house(Card hand[], int rank_ct[]) {
    return is_three_of_a_kind(hand, rank_ct) && is_pair(hand, rank_ct);
}

// detect two of a kind
BOOLEAN is_pair(Card hand[], int rank_ct[]) {
    // check for a pair
    BOOLEAN saw_pair = FALSE;
    for (int i = 0; i < NUM_RANKS; i++)
        if (rank_ct[i] == 2)
            saw_pair = TRUE;
    return saw_pair;
}

// detect straight
BOOLEAN is_straight(Card hand[], int rank_ct[]) {
    // check for a straight
    BOOLEAN saw_straight = FALSE;
    int seq_ct = 0;
    for (int i = 0; i < NUM_RANKS; i++)
        if (rank_ct[i] == 1) {
            seq_ct++;
            if (seq_ct == 5)
                saw_straight = TRUE;
        } else
            seq_ct = 0;
    return saw_straight;
}

// detect three of a kind
BOOLEAN is_three_of_a_kind(Card hand[], int rank_ct[]) {
    // check for a three_of_a_kind
    BOOLEAN saw_three_of_a_kind = FALSE;
    for (int i = 0; i < NUM_RANKS; i++)
        if (rank_ct[i] == 3)
            saw_three_of_a_kind = TRUE;
    return saw_three_of_a_kind;
}

// detect two pair
BOOLEAN is_two_pair(Card hand[], int rank_ct[]) {
    // check for two pair
    BOOLEAN saw_one_pair = FALSE;
    BOOLEAN saw_two_pair = FALSE;
    for (int i = 0; i < NUM_RANKS; i++) {
        if (rank_ct[i] == 2) {
            if (saw_one_pair)
                saw_two_pair = TRUE;
            else
                saw_one_pair = TRUE;
        }
    }
    return saw_two_pair;
}

int main(int argc, char** argv) {
    Card deck[DECK_SIZE];
    Card hand[HAND_SIZE];
    int type_ct[NUM_HAND_TYPES];
    if (argc < 2) {
        printf("usage: %s count\n", argv[0]);
        exit(0);
    }
    int count = atoi(argv[1]);
    printf("%d\n", count);
    srand((int)time(NULL));
    for (int j = 0; j < count; j++) {
        int size = DECK_SIZE;
        init_deck(deck);
        deal_hand(hand, deck, &size);
        char card_string[100];
        for (int i = 0; i < HAND_SIZE; i++) {
            card_format(hand[i], card_string);
            printf("%-17s ", card_string);
            //printf("card %d: %s\n", i, card_string);
        }
        int rank_ct[NUM_RANKS];
        count_ranks(hand, rank_ct);
        int suit_ct[NUM_SUITS];
        count_suits(hand, suit_ct);
        /*
                for (int i = 0; i < NUM_RANKS; i++)
                    printf("  rank %2d: %d\n", i, rank_ct[i]);
        */
        if (is_straight_flush(hand, rank_ct, suit_ct)) {
            printf("is straight flush\n");
            type_ct[STRAIGHT_FLUSH]++;
        }
        else if (is_four_of_a_kind(hand, rank_ct)) {
            printf("is four of a kind\n");
            type_ct[FOUR_OF_A_KIND]++;
        }
        else if (is_full_house(hand, rank_ct)) {
            printf("is full house\n");
            type_ct[FULL_HOUSE]++;
        }
        else if (is_flush(hand, suit_ct)) {
            printf("is flush\n");
            type_ct[FLUSH]++;
        }
        else if (is_straight(hand, rank_ct)) {
            printf("is straight\n");
            type_ct[STRAIGHT]++;
        }
        else if (is_three_of_a_kind(hand, rank_ct)) {
            printf("is three of a kind\n");
            type_ct[THREE_OF_A_KIND]++;
        }
        else if (is_two_pair(hand, rank_ct)) {
            printf("is two pair\n");
            type_ct[TWO_PAIR]++;
        }
        else if (is_pair(hand, rank_ct)) {
            printf("is pair\n");
            type_ct[PAIR]++;
        }
        else {
            printf("is bupkiss\n");
            type_ct[BUPKISS]++;
        }
    }
    printf("\ntype            count  fraction\n");
    printf("%-15s %-5d %7.4f %%\n",
           "STRAIGHT_FLUSH", type_ct[STRAIGHT_FLUSH], 100*type_ct[STRAIGHT_FLUSH]/((float)count)
          );
    printf("%-15s %-5d %7.4f %%\n",
           "FOUR_OF_A_KIND", type_ct[FOUR_OF_A_KIND], 100*type_ct[FOUR_OF_A_KIND]/((float)count)
          );
    printf("%-15s %-5d %7.4f %%\n",
           "FULL_HOUSE", type_ct[FULL_HOUSE], 100*type_ct[FULL_HOUSE]/((float)count)
          );
    printf("%-15s %-5d %7.4f %%\n",
           "FLUSH", type_ct[FLUSH], 100*type_ct[FLUSH]/((float)count)
          );
    printf("%-15s %-5d %7.4f %%\n",
           "STRAIGHT", type_ct[STRAIGHT], 100*type_ct[STRAIGHT]/((float)count)
          );
    printf("%-15s %-5d %7.4f %%\n",
           "THREE_OF_A_KIND", type_ct[THREE_OF_A_KIND], 100*type_ct[THREE_OF_A_KIND]/((float)count)
          );
    printf("%-15s %-5d %7.4f %%\n",
           "TWO_PAIR", type_ct[TWO_PAIR], 100*type_ct[TWO_PAIR]/((float)count)
          );
    printf("%-15s %-5d %7.4f %%\n",
           "PAIR", type_ct[PAIR], 100*type_ct[PAIR]/((float)count)
          );
    printf("%-15s %-5d %7.4f %%\n",
           "BUPKISS", type_ct[BUPKISS], 100*type_ct[BUPKISS]/((float)count)
          );
}



