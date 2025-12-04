#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"card.h"
#include"judgement.h"
#define CONSIDER_SIZE 7


// 判定牌型---判定权重
HandResult judge(const Card o_hand[CONSIDER_SIZE]){
    int size = CONSIDER_SIZE;
    HandResult result;
    Card temp, hand[size];
    for(int i = 0; i < size; i++){
        hand[i] = o_hand[i];
    }
    for(int i = 1; i < size; i++){
        for(int j = 0; j < size-i; j++){
            if(hand[j].rank < hand[j+1].rank){
                temp = hand[j];
                hand[j] = hand[j+1];
                hand[j+1] = temp;
            }
        }
    }
    Suit hand_suits[size];
    int hand_ranks[size];
    int sum_list[15] = {0};   //画正字
    for(int i = 0; i < size; i++){
        hand_suits[i] = hand[i].suit;
        hand_ranks[i] = hand[i].rank;
        sum_list[hand_ranks[i]] += 1;
    }


    /*straight flush*/
    if (have_flush(hand_suits,size) && have_straight(hand_ranks,size)){
        result.weight = 0x00800000;
        result.weight += highest_of_straight(hand_ranks,size);
        int tmp = single_exist(hand_ranks, size,
             highest_of_straight(hand_ranks,size));
        for(int i = 0; i < 5; i++){
            result.best_hand[i] = hand[tmp + i];
        }
        result.hand_type = STRAIGHT_FLUSH;
        return result;
    }

    /*four of a kind*/
    if (find_max_value(sum_list, 15) == 4){
        result.weight = 0x00700000;
        int four_rank, kicker;
        for(int i = 14; i >= 2; i--){
            if(sum_list[i] == 4){
                four_rank = i;
                result.weight += four_rank * 16;
                break;
            }
        }
        int tmp = single_exist(hand_ranks, size, four_rank);
        for (int j = 0; j < 4; j++){
            result.best_hand[j] = hand[tmp + j];
        }
        if (tmp > 0){
            kicker = hand_ranks[0];
        } else {
            kicker = hand_ranks[4];
        }
        result.weight += kicker;
        result.best_hand[4] = hand[tmp > 0 ? 0 : 4];
        result.hand_type = FOUR_OF_A_KIND;  
        return result;
    }

    /*full house*/
//TODO:
}


bool have_flush(Suit suits[], int size){
    for (int i = 0; i < size-4; i++){
        int count = 1;
        for (int j = i+1; j < size; j++){
            if (suit_match(suits[i], suits[j])){
                count++;
            }
        }
        if (count >= 5){
            return true;
        } else {
            continue;
        }
    }
    return false;
}

bool have_straight(int ranks[], int size){
    for(int i = 0; i < size-4; i++){
        int count = 1, point = i;
        while((point = single_exist(ranks, size, ranks[point]+1)) != -1){
            count++;
        }
        point = i;
        while((point = single_exist(ranks, size, ranks[point]-1)) != -1){
            count++;
        }

        if (count >= 5){
            return true;
        } else {
            continue;
        }
    }
    if (   single_exist(ranks, size, 14) != -1
        && single_exist(ranks, size, 5) != -1
        && single_exist(ranks, size, 4) != -1
        && single_exist(ranks, size, 3) != -1
        && single_exist(ranks, size, 2) != -1){
            return true;
    }
    return false;
}
/*弱:排序后使用*/
int highest_of_straight(int ranks[], int size){
    for(int i = 0; i < size-4; i++){
        int count = 1, record = i;
        while(ranks[i] == ranks[i+1] + 1){
            count++;
            i++;
        }
        if (count >= 5){
            return ranks[record];
        } else {
            i = record;
            continue;
        }
    }
    if (   single_exist(ranks, size, 14) != -1
        && single_exist(ranks, size, 5) != -1
        && single_exist(ranks, size, 4) != -1
        && single_exist(ranks, size, 3) != -1
        && single_exist(ranks, size, 2) != -1){
            return 5;
    }
    return -1;
}



int single_exist(int ranks[], int size, int num){
    for(int i = 0; i < size; i++){
        if(ranks[i] == num){
            return i;
        }
    }
    return -1;
}
/*寻找多条，返回最后一个下标*/
int multiple_exist(int ranks[], int size, int mul, int num){
    int count = 0;
    for(int i = 0; i < size; i++){
        if(ranks[i] == num){
            count++;
            if(count == mul){
                return i;
            }
        }
    }
    return -1;
}



bool suit_match(Suit a, Suit b){
    return (a & b) != 0;
}

int find_max_value(int arr[], int size) {
    int tmp = arr[0];
    for(int i = 1; i < size; i++) {
        if(arr[i] > tmp) {
            tmp = arr[i];
        }
    }
    return tmp;
}