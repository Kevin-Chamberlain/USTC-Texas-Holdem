#include<stdio.h>
#include "action.h"
#include "var_global.h"

void do_presettle(React react){
    set_chip(get_chip() - react.amt);
    if (react.act == RAISE || react.amt == CALL){
        set_pot(2 * react.amt);
    } 
    return;
}