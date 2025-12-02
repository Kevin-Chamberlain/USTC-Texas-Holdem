#include<stdio.h>
#include<stdlib.h>
#include"card.h"

RoundInfo read_round_info(const char* line){
    RoundInfo info;
    char cc[9][3];
    int check = sscanf(line ,"%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%d",
        cc[0], cc[1], cc[2], cc[3], cc[4],
        &info.pot,
        cc[5], cc[6], cc[7], cc[8],
        &info.result
    );
    if (check != 11) {
        fprintf(stderr, "Error: Invalid round info format.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 5; i++) {
        info.community[i] = (Card){ .suit = cc[i][1], .rank = cc[i][0] };
    }
    for (int i = 0; i < 2; i++) {
        info.pocket1[i] = (Card){ .suit = cc[i + 5][1], .rank = cc[i + 5][0] };
        info.pocket2[i] = (Card){ .suit = cc[i + 7][1], .rank = cc[i + 7][0] };
    }
    return info;
}

