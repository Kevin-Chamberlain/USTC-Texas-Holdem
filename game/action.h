#ifndef ACTION_H
#define ACTION_H
#include <stdint.h>

typedef enum {
    FOLD,
    CALL,
    RAISE
} Action;

typedef struct{
    Action act;
    long long amt;
    double pp;
} React;

char* action_to_string(Action react);
void do_presettle(React react);

#endif /* ACTION_H */