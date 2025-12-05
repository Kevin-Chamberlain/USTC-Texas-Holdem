#ifndef GLOBAL_H
#define GLOBAL_H

/* 全局筹码 */
extern int pot;
extern int chip;
extern int chip1;

void set_chip(int value);
int get_chip(void);
void set_chip1(int value);
int get_chip1(void);
void set_pot(int value);
int get_pot(void);

#endif /* GLOBAL_H */