#include "procedure.h"

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
            fprintf(stderr, "quit: bad choice");
            return NULL;
    }
}

FILE* def_output(int m){
    switch (m){
        case 1:
            cleaar_file("round_result/games_1_r.csv");
            return fopen("round_result/games_1_r.csv", "a");
        case 2:
            cleaar_file("round_result/games_2_r.csv");
            return fopen("round_result/games_2_r.csv", "a");
        case 3:
            cleaar_file("round_result/games_3_r.csv");
            return fopen("round_result/games_3_r.csv", "a");
        case 4:
            cleaar_file("round_result/games_master_r.csv");
            return fopen("round_result/games_master_r.csv", "a");
    
        default:
            fprintf(stderr, "quit: bad choice");
            return NULL;
    }
}

void cleaar_file(const char* filename){
    FILE *fp = fopen(filename, "w");
    if (!fp) perror("无法打开文件");
    fclose(fp);
}