#ifndef GLOBAL_H
#define GLOBAL_H

/* 全局筹码，使用 LONG LONG 防止溢出 */
#include <stdint.h>
extern long long pot;
extern long long chip;
extern long long chip1;

void set_chip(long long value);
long long get_chip(void);
void set_chip1(long long value);
long long get_chip1(void);
void set_pot(long long value);
long long get_pot(void);

#endif /* GLOBAL_H */