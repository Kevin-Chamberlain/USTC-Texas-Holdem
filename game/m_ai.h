#ifndef M_AI_H
#define M_AI_H
#include "action.h"
#include "card.h"

typedef React (*Func_ptr)();
Func_ptr def_ai(int i);
React ai_repeater(RoundInfo info);
React ai_gambler(RoundInfo info);
React ai_conservative(RoundInfo info);
React ai_rational(RoundInfo info);
React is_possible(React o_react);
React demote(React o_react);

#endif