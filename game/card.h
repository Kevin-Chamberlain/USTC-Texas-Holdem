#ifndef POKER_CARD_H
#define POKER_CARD_H
#define CONSIDER_SIZE 7
typedef enum {
    STRAIGHT_FLUSH = 8,
    FOUR_OF_A_KIND = 7,
    FULL_HOUSE = 6,
    FLUSH = 5,
    STRAIGHT = 4,
    THREE_OF_A_KIND = 3,
    TWO_PAIR = 2,
    ONE_PAIR = 1,
    HIGH_CARD = 0
} HandType;

typedef enum {
    C = 0b0001,  /*CLUB*/
    D = 0b0010,  /*DIAMOND*/
    H = 0b0100,  /*HEART*/
    S = 0b1000   /*SPADE*/
} Suit;

typedef struct {
    Suit suit;
    int rank;
} Card;

typedef struct {
    Card player1[CONSIDER_SIZE];    /*ai is player1*/
    Card player2[CONSIDER_SIZE];
    int pot;
    int result;
    int weight1;
    int weight2;
} RoundInfo;

typedef struct {
    int weight;         
    Card best_hand[5];
    HandType hand_type;
} HandResult;
/*权重（weight）考虑用0x00000000中的后六位统一表示，
**倒数第六位表示牌型级别，后位表示多级比较
**比较级数不多时，可只用到后几位表示
*/

static Suit char_to_suit(char c);
static int char_to_rank(char c);
static char *handtype_to_string(HandType ht);
RoundInfo read_round_info(const char *line);
#endif //POKER_CARD_H