#include<stdio.h>
#include<stdlib.h>
#include"card.h"
#include<string.h>

static Suit char_to_suit(char c) {
    switch (c) {
        case 'C': return C;
        case 'D': return D;
        case 'H': return H;
        case 'S': return S;
        default:
            fprintf(stderr, "Invalid suit character: '%c' (0x%02x)\n", c, (unsigned char)c);
            exit(1);  // return C
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
        default:
            fprintf(stderr, "Invalid rank character: '%c' (0x%02x)\n", c, (unsigned char)c);
            exit(1);  // return 0
    }
}
static char *handtype_to_string(HandType ht) {
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
    char cc[9][4];
    /* make a local copy and strip trailing CR/LF */
    char buf[512];
    strncpy(buf, line, sizeof(buf)-1);
    buf[sizeof(buf)-1] = '\0';
    size_t bl = strlen(buf);
    while (bl > 0 && (buf[bl-1] == '\n' || buf[bl-1] == '\r')) { buf[--bl] = '\0'; }
    /* skip UTF-8 BOM if present */
    char *start = buf;
    if ((unsigned char)start[0] == 0xEF && (unsigned char)start[1] == 0xBB && (unsigned char)start[2] == 0xBF) {
        start += 3;
    }

    int check = sscanf(start ,
        "%2[^,],%2[^,],%2[^,],%2[^,],%2[^,],%lld,%2[^,],%2[^,],%2[^,],%2[^,],%d",
        cc[0], cc[1], cc[2], cc[3], cc[4],
        &info.pot,
        cc[5], cc[6], cc[7], cc[8],
        &info.result
    );
    if (check != 11) {
        fprintf(stderr, "\nBad CSV line: expected 11 fields but got %d -- line='%.80s'\n", check, start);
        exit(1);
    }
    /* ensure tokens are 2 chars (rank + suit) */
    for (int t = 0; t < 9; ++t) {
        if ((int)strlen(cc[t]) < 2) {
            fprintf(stderr, "Invalid card token at slot %d: '%s'\n", t, cc[t]);
            exit(1);
        }
    }
    for (int i = 0; i < 5; i++) {
        info.player2[i] = info.player1[i] = 
            (Card){ .suit = char_to_suit(cc[i][1]) , .rank = char_to_rank(cc[i][0]) };
    }
    for (int i = 5; i < 7; i++) {
        info.player1[i] = (Card){ .suit = char_to_suit(cc[i][1]) , .rank = char_to_rank(cc[i][0]) };
        info.player2[i] = (Card){ .suit = char_to_suit(cc[i+2][1]) , .rank = char_to_rank(cc[i+2][0]) };
    }
    return info;
}
