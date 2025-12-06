#include "var_global.h"

long long chip = 0, chip1 = 0, pot = 0;

void set_chip(long long value){
    chip = value;
}

long long get_chip(void){
    return chip;
}

void set_chip1(long long value){
    chip1 = value;
}

long long get_chip1(void){
    return chip1;
}

void set_pot(long long value){
    pot = value;
}

long long get_pot(void){
    return pot;
}