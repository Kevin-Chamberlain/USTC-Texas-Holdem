#include <stdio.h>
#include <assert.h>
#include "card.h"
#include "judgement.h"

double probability_to_win(Card hand[7]){
    HandResult result = judge(hand);
    /*init library*/
    Card lib[4][13];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 13; j++){
            lib[i][j].rank = j + 2;
            lib[i][j].suit = (Suit)(1 << i);
        }
    }
    for (int k = 0; k < 7; k++){
        int tmp = (int)hand[k].suit / 2;
        if (tmp == 4) tmp = 3;
        lib[tmp][hand[k].rank - 2].rank = 0;
    }
    Card presume[7];
    for (int i = 0; i < 5; i++){
        presume[i] = hand[i];
    }
    
    int win_count = 0, lose_count = 0;
    for (int i = 0; i < 4; i++){
    for (int j = 0; j < 13; j++){
            if (lib[i][j].rank == 0) continue;
            presume[5] = lib[i][j];
        for (int k = i; k < 4; k++){
        for (int l = (k == i ? j + 1 : 0); l < 13; l++){
            if (lib[k][l].rank == 0) continue;
            presume[6] = lib[k][l];
            HandResult sume_result = judge(presume);
            if (result.weight <= sume_result.weight){
                lose_count++;
            } else {
                win_count++;
            }
        }
        }
    }
    }
/*    
**  printf("%d,%d", win_count, lose_count);
**  fflush(stdout); 
*/
    assert(lose_count + win_count == 990);  /*45C2*/
    return (double)win_count / 990 * 100;   /*%*/
    
}