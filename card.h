#ifndef POKER_CARD_H
#define POKER_CARD_H

typedef enum {
    C,  /*CLUB*/
    D,  /*DIAMOND*/
    H,  /*HEART*/
    S   /*SPADE*/
} Suit;
typedef enum {
    II = 2, III, IV, V, VI, VII, VIII, IX,
    T = 10, J, Q, K, A
} Rank;

typedef struct {
    Suit suit;
    Rank rank;
} Card;

typedef struct {
    Card community[5];
    Card pocket1[2];
    Card pocket2[2];
    int pot;
    int result;
} RoundInfo;


#endif //POKER_CARD_H