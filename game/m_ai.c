#include <stdio.h>
#include "action.h"
#include "judgement.h"
#include "var_global.h"
#include "m_ai.h"
#include "library.h"
#define LIMIT_CALL 35.0        /*行为分界：保守调高*/
#define LOWER_LIMIT_CALL 15.0  /*一线生机*/
#define LIMIT_RAISE 78.0       /*行为分界：保守调高*/
#define BUDGER_LIMIT 60.0      /*加注上限百分比*/
#define SECURITY_LIMIT 50.0    /*池底-筹码安全感百分比*/
#define EVERAGE_POT 255.0      /*计算得到：平均池底大小*/

char *aitype_to_string(int i) {
    switch (i) {
        case 1: return "Repeater";
        case 2: return "Gambler";
        case 3: return "Conservative";
        case 4: return "Rational";

        default: return "Unknown Type";
    }
}

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
            fprintf(stderr, "quit: bad choice");
            return NULL;
    }
}

React ai_repeater(RoundInfo info){
    React react;
    react.act = CALL;
    react.amt = info.pot;
    react.pp = -1;
    return is_possible(react);
}

React ai_gambler(RoundInfo info){
    React react;
    HandResult result = judge(info.player1);
    int r = (int)result.hand_type;
    react.act = RAISE;
    react.amt = info.pot + r * 100 + 1;
    react.pp = -1;    
    return is_possible(react);
}

React ai_conservative(RoundInfo info){
    React react;
    double prob = probability_to_win(info.player1);
    react.pp = prob;
    HandResult result = judge(info.player1);
    int r = (int)result.hand_type;
    if (r >= 1){
        react.act = CALL;
        react.amt = info.pot;
    } else {
        react.act = FOLD;
        react.amt = info.pot / 2;
    }
    react.pp = -1;
    return is_possible(react);
}

/*线性*/
React ai_rational(RoundInfo info){
    React react;
    if (info.count <= 7){
        return ai_conservative(info);
    }
    double prob = probability_to_win(info.player1);
    react.pp = prob;
    if (prob <= LIMIT_CALL) {
        if (get_chip() - info.pot / 2 <= EVERAGE_POT && prob >= LOWER_LIMIT_CALL){
            react.act = CALL;
            react.amt = info.pot;       /*背水一战*/
        } else {
            react.act = FOLD;
            react.amt = info.pot / 2;
        }
    } else if (prob >= LIMIT_RAISE){
        double percentage = info.pot / get_chip() * 100.0;
        if (percentage <= SECURITY_LIMIT){
            double scale = (prob - LIMIT_RAISE) / (100.0 - LIMIT_RAISE);
            if (scale < 0) scale = 0;
            if (scale > 1) scale = 1;
            double max_frac = (double)BUDGER_LIMIT / 100.0;
            double per = scale * max_frac;
            
            react.act = RAISE;
            react.amt = (long long)(per * (double)(get_chip() - info.pot)) + info.pot;
        } else {
            react.act = CALL;
            react.amt = info.pot;
        }
    } else {
        react.act = CALL;
        react.amt = info.pot;
    }
    return is_possible(react);
}

//TODO:其他算法

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

