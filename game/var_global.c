#include "var_global.h"

int chip = 0, chip1 = 0, pot = 0;

void set_chip(int value){
    chip = value;
}

int get_chip(void){
    return chip;
}

void set_chip1(int value){
    chip1 = value;
}

int get_chip1(void){
    return chip1;
}

void set_pot(int value){
    pot = value;
}

int get_chip1(void){
    return pot;
}