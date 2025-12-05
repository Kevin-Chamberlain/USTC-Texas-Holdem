#include <stdio.h>
#include "action.h"
#include "judgement.h"
#include "var_global.h"
#include "m_ai.h"
#include "library.h"

Func_ptr def_ai(int i){
    switch (i){
        case 1:
            return ai_repeater;
        case 2:
            return ai_gambler;
        case 3:
            return ai_conservative;
        case 4:
            return ai_rational;
    
        default:
            sprintf(stderr, "quit: bad choice");
            return NULL;
    }
}

React ai_repeater(RoundInfo info){
    React react;
    react.act = CALL;
    react.amt = info.pot;
    return is_possible(react);
}

React ai_gambler(RoundInfo info){
    React react;
    HandResult result = judge(info.player1);
    int r = (int)result.hand_type;
    react.act = RAISE;
    react.amt = info.pot + r * 100 + 1;
    return is_possible(react);
}

React ai_conservative(RoundInfo info){
    React react;
    HandResult result = judge(info.player1);
    int r = (int)result.hand_type;
    if (r >= 1){
        react.act = CALL;
        react.amt = info.pot;
    } else {
        react.act = FOLD;
        react.amt = info.pot / 2;
    }
    return is_possible(react);
}

React ai_rational(RoundInfo info){
    React react;
    double prob = probability_to_win(info.player1);
    if (prob <= 25) {
        react.act = FOLD;
        react.amt = info.pot / 2;
    }
    if (prob)
//TODO:
    return is_possible(react);
}

React is_possible(React o_react){
    React react = o_react;
    for (int i = 0; i < 2; i++){
        if (react.amt >= get_chip()){
            react = demote(react);
        }
    }
    return react;
}

React demote(React o_react){
    React react = o_react;
    if (react.act == RAISE){
        react.act = CALL;
        react.amt = get_pot();
    } else if (react.act == CALL){
        react.act = FOLD;
        react.amt = get_pot() / 2;
    }
    return react;
}

