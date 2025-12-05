#include<stdio.h>
#include<stdlib.h>
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
    int sum_list[15] = {0};
    for(int i = 0; i < size; i++){
        hand_suits[i] = hand[i].suit;
        hand_ranks[i] = hand[i].rank;
        sum_list[hand_ranks[i]] += 1;   /*sumlist下标与牌面正对应*/
    }


    /*straight flush 8*/
    if (have_flush(hand_suits,size) && have_straight(hand_ranks,size)){
        result.weight = 0x00800000;
        int top = highest_of_straight(hand_ranks, size);
        result.weight += top;
        int tmp = single_exist(hand_ranks, size, top);
        for(int i = 0; i < 5; i++){
            result.best_hand[i] = hand[tmp + i];
        }
        result.hand_type = STRAIGHT_FLUSH;
        return result;
    }

    /*four of a kind 7*/
    if (single_exist(sum_list, 15, 4) != -1){
        result.weight = 0x00700000;
        int four_rank, kicker;          /*kicker::踢脚*/
        for(int i = 14; i >= 2; i--){
            if(sum_list[i] == 4){
                four_rank = i;
                result.weight += four_rank << 4;
                break;
            }
        }
        int tmp = single_exist(hand_ranks, size, four_rank);
        for (int j = 0; j < 4; j++){
            result.best_hand[j] = hand[tmp + j];
        }
        kicker = tmp > 0 ? hand_ranks[0] : hand_ranks[0];
        result.weight += kicker;
        result.best_hand[4] = hand[tmp > 0 ? 0 : 4];
        result.hand_type = FOUR_OF_A_KIND;  
        return result;
    }

    /*full house 6*/
    if (single_exist(sum_list, 15, 3) != -1 && single_exist(sum_list, 15, 2) != -1){
        result.weight = 0x00600000;
        int three_rank = single_exist(sum_list, 15, 3);
        int kicker = single_exist(sum_list, 15, 2);
        int kicker1 = multiple_exist(sum_list, 15, 2, 2);
        if (kicker1 != -1){
            kicker = kicker1;
        }
        result.weight += (three_rank << 4) + kicker;
        int tmp = single_exist(hand_ranks, size, three_rank);
        for (int i = 0; i < 3; i++){
            result.best_hand[i] = hand[tmp + i];
        }
        tmp = single_exist(hand_ranks, size, kicker);
        for (int j = 0; j < 2; j++){
            result.best_hand[j + 3] = hand[tmp + j];
        }
        result.hand_type = FULL_HOUSE;
        return result;
    }

     /*flush 5*/
    if (have_flush(hand_suits, size)){
        result.weight = 0x00500000;
        Suit key = best_of_flush(hand_suits, size);
        int count = 0;
        for (int i = 0; i < size; i++){
            if (hand_suits[i] == key){
                result.best_hand[count] = hand[i];
//              result.weight += hand_ranks[i] * pow(16, 4 - count);
                result.weight += hand_ranks[i] << (4 * (4 - count));
            }
            count++;
            if(count == 5){
                break;
            }
        }
        result.hand_type = FLUSH;
    }

    /*straight 4*/
    if (have_straight(hand_ranks, size)){
        result.weight = 0x00400000;
        int top = highest_of_straight(hand_ranks, size);
        result.weight += top;
        int tmp = single_exist(hand_ranks, size, top);
        for(int i = 0; i < 5; i++){
            result.best_hand[i] = hand[tmp + i];
        }
        result.hand_type = FLUSH;
        return result;
    }

    /*three of a kind 3*/
    if (single_exist(sum_list, 15, 3) != -1){
        result.weight = 0x00300000;
        int three_rank = single_exist(sum_list, 15, 3);
        int three_rank1 = multiple_exist(sum_list, 15, 2, 3);
        if (three_rank1 != -1){
            three_rank = three_rank1;
        }
        int tmp = single_exist(hand_ranks, size, three_rank);
        int kicker = tmp > 0 ? hand_ranks[0] : hand_ranks[3];
        int kicker1 = tmp > 1 ? hand_ranks[1] : hand_ranks[4];
        result.weight += (kicker << 4) + kicker1;
        for (int i = 0; i < 3; i++){
            result.best_hand[i] = hand[tmp + i];
        }
        result.best_hand[3] = tmp > 0 ? hand[0] : hand[3];
        result.best_hand[4] = tmp > 1 ? hand[1] : hand[4];
        result.hand_type = THREE_OF_A_KIND;
        return result;
    }

    /*two pair 2*/    
    if ((multiple_exist(sum_list, 15, 2, 2) != -1)){
        result.weight = 0x00200000;
        int pair[3], loc[2], kicker;
        pair[1] = single_exist(sum_list, 15, 2);
        pair[0] = multiple_exist(sum_list, 15, 2, 2);
        pair[2] = multiple_exist(sum_list, 15, 3, 2);
        if (pair[2] != -1){
            pair[1] = pair[0];
            pair[0] = pair[2];
        }
        loc[0] = single_exist(hand_ranks, size, pair[0]);
        loc[1] = single_exist(hand_ranks, size, pair[1]);
        for (int i = 0; i < 2; i++){
            result.best_hand[i] = hand[loc[0] + i];
            result.best_hand[i + 2] = hand[loc[1] + i];
        }
        if (loc[0] > 0){
            kicker = hand_ranks[0];
            result.best_hand[4] = hand[0];
        } else if (loc[1] > 2){
            kicker = hand_ranks[2];
            result.best_hand[4] = hand[2];
        } else {
            kicker = hand_ranks[4];
            result.best_hand[4] = hand[4];
        }
        result.weight += (pair[0] << 8) + (pair[1] << 4) + kicker;
        result.hand_type = TWO_PAIR;
        return result;
    }

    /*one pair 1*/
    if (single_exist(sum_list, 15, 2) != -1){
        result.weight = 0x00100000;
        int pair = single_exist(sum_list, 15, 2);
        int loc = single_exist(hand_ranks, size, pair);
        for (int i = 0; i < 2; i++){
            result.best_hand[i] = hand[loc + i];
        }
        result.weight += (pair << 3 * 4);
        int kicker[3], point = 0, count = 0;
        while (count < 3 && point < size){
            if (point != loc && point != loc + 1){
                result.best_hand[2 + count] = hand[point];
                kicker[count] = hand_ranks[point];
                result.weight += kicker[count] << (2 - count) * 4;
                count++;
            }
            point++;
        }
        result.hand_type = ONE_PAIR;
        return result;
    }

    /*high card*/
    if (true){
        result.weight = 0x00000000;
        for (int i = 0; i < 5; i++){
            result.best_hand[i] = hand[i];
            result.weight += hand_ranks[i] << (4 - i)*4;
        }
        result.hand_type = HIGH_CARD;
        return result;
    }
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
/*未确认同花会返回默认黑桃*/
Suit best_of_flush(Suit suits[], int size){
    for (int i = 0; i < size-4; i++){
        int count = 1;
        for (int j = i+1; j < size; j++){
            if (suit_match(suits[i], suits[j])){
                count++;
            }
        }
        if (count >= 5){
            return suits[i];
        } else {
            continue;
        }
    }
    return S;
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


/*寻找一个，返回下标，不存在返回-1*/
int single_exist(int ranks[], int size, int num){
    for(int i = 0; i < size; i++){
        if(ranks[i] == num){
            return i;
        }
    }
    return -1;
}
/*寻找多条，返回最后一个下标，不足返回-1*/
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
/*返回最大值*//*怎么没用上。。*/
int find_max_value(int arr[], int size) {
    int tmp = arr[0];
    for(int i = 1; i < size; i++) {
        if(arr[i] > tmp) {
            tmp = arr[i];
        }
    }
    return tmp;
}
