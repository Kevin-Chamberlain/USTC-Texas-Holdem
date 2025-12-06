#ifndef ACTION_H
#define ACTION_H

typedef enum {
    FOLD,
    CALL,
    RAISE
} Action;

typedef struct{
    Action act;
    int amt;
    double pp;
} React;

#endif /* ACTION_H */