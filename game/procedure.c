#include "procedure.h"
#include<stdio.h>
//#include<stdlib.h>



FILE* def_data(int n){
    switch (n){
        case 1:
            return fopen("round_info/games_1.csv", "r");
        case 2:
            return fopen("round_info/games_2.csv", "r");
        case 3:
            return fopen("round_info/games_3.csv", "r");
        case 4:
            return fopen("round_info/games_master.csv", "r");
    
        default:
            sprintf(stderr, "quit: bad choice");
            return NULL;
    }
}

FILE* def_output(int m){
    switch (m){
        case 1:
            return fopen("round_result/games_1_r.csv", "a");
        case 2:
            return fopen("round_result/games_2_r.csv", "a");
        case 3:
            return fopen("round_result/games_3_r.csv", "a");
        case 4:
            return fopen("round_result/games_master_r.csv", "a");
    
        default:
            sprintf(stderr, "quit: bad choice");
            return NULL;
    }
}