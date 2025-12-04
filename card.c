#include<stdio.h>
#include<stdlib.h>
#include"card.h"

static Suit char_to_suit(char c) {
    switch (c) {
        case 'C': return C;
        case 'D': return D;
        case 'H': return H;
        case 'S': return S;
        default:  perror("Invalid suit character");
    }
}
static int char_to_rank(char c) {
    if (c >= '2' && c <= '9') return c - '0';
    switch (c) {
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 14;
        default:  perror("Invalid rank character");
    }
}
static char* handtype_to_string(HandType ht) {
    switch (ht) {
        case STRAIGHT_FLUSH: return "Straight Flush";
        case FOUR_OF_A_KIND: return "Four of a Kind";
        case FULL_HOUSE:     return "Full House";
        case FLUSH:          return "Flush";
        case STRAIGHT:       return "Straight";
        case THREE_OF_A_KIND:return "Three of a Kind";
        case TWO_PAIR:       return "Two Pair";
        case ONE_PAIR:       return "One Pair";
        case HIGH_CARD:      return "High Card";
        default:             return "Unknown Hand Type";
    }
}
RoundInfo read_round_info(const char* line){
    RoundInfo info;
    char cc[9][3];
    int check = sscanf(line ,
        "%2s,%2s,%2s,%2s,%2s,%d,%2s,%2s,%2s,%2s,%d",
        cc[0], cc[1], cc[2], cc[3], cc[4],
        &info.pot,
        cc[5], cc[6], cc[7], cc[8],
        &info.result
    );
    for (int i = 0; i < 5; i++) {
        info.community[i] = (Card){ .suit = char_to_suit(cc[i][1]) , .rank = char_to_rank(cc[i][0]) };
    }
    for (int i = 0; i < 2; i++) {
        info.pocket1[i] = (Card){ .suit = char_to_suit(cc[i+5][1]) , .rank = char_to_rank(cc[i+5][1]) };
        info.pocket2[i] = (Card){ .suit = char_to_suit(cc[i+7][1]) , .rank = char_to_rank(cc[i+7][1]) };
    }
    return info;
}
