#ifndef JUDGEMENT_H
#define JUDGEMENT_H
#include<stdbool.h>
#include"card.h"
#define CONSIDER_SIZE 7

HandResult judge(const Card o_hand[CONSIDER_SIZE]);
bool have_flush(Suit suits[], int size);
Suit best_of_flush(Suit suits[], int size);
bool have_straight(int ranks[], int size);
int highest_of_straight(int ranks[], int size);
int single_exist(int ranks[], int size, int num);
int multiple_exist(int ranks[], int size, int order, int num);
bool suit_match(Suit a, Suit b);
int find_max_value(int list[], int size);




#endif //JUDGEMENT_H