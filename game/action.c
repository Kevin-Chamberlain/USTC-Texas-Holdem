#include<stdio.h>
#include "action.h"
#include "var_global.h"

char* action_to_string(Action a){
    switch (a) {
        case FOLD : return "FOLD";
        case CALL : return "CALL";
        case RAISE: return "RAISE";

        default: return "Unknown Action Type";
    }
}

void do_presettle(React react){

    set_chip(get_chip() - (long long)react.amt);
    if (react.act == RAISE || react.act == CALL){
        set_pot(2LL * (long long)react.amt);
    }
    return;
}