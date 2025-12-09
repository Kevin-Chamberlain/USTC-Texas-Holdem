#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include "../welcome/menu.h"
#include "m_ai.h"
#include "procedure.h"
#include "var_global.h"
#include "action.h"
#include "judgement.h"

int main() {
    int ai_strategy, file_choice;
    for (int i = 0; i < 1; i++) {
        ai_strategy = do_welcome();
        file_choice = do_work();
        i += file_choice == -1 ? -1 : 0;
    }
    Func_ptr ai_pointer = def_ai(ai_strategy);
    FILE *DATA = def_data(file_choice);
    if (!DATA) fprintf(stderr, "fopen failed");
    FILE *OUTPUT = def_output(file_choice);
    if (!OUTPUT) fprintf(stderr, "fopen failed");

    fprintf(OUTPUT, "using ai: %s\n", aitype_to_string(ai_strategy));
    if (ai_strategy == 4) 
        fprintf(OUTPUT, "牌局编号,AI胜率,AI决策,AI筹码变化,AI剩余筹码\n");
    else 
        fprintf(OUTPUT, "牌局编号,AI决策,AI筹码变化,AI剩余筹码\n");

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    linelen = getline(&line, &linecap, DATA);
    if (linelen == -1) {
        fprintf(stderr, "no header line\n");
    }
    
    int std_chip;
    printf("AI初始筹码:");
    int x = scanf("%d", &std_chip);
    if (x != 1) {
    fprintf(stderr, "invalid input, using default value\n");
    std_chip = 1000;
    }
    set_chip(std_chip);
    int count = 0;
/*  检查CSV输入
    if (line) {
        for (int i = 0; i < 20 && (unsigned char)line[i]; ++i)
            fprintf(stderr, "%02x ", (unsigned char)line[i]);
        fprintf(stderr, "\nline=\"%s\"\n", line);
    }
*/
    while ((linelen = getline(&line, &linecap, DATA)) != -1){
        /* CR/LF */
        while (linelen > 0 && (line[linelen-1] == '\n' || line[linelen-1] == '\r')) line[--linelen] = '\0';
        /* leading spaces / empty lines */
        char *p = line;
//        while (*p == ' ' || *p == '\t') ++p;
//        if (*p == '\0') continue;

        RoundInfo info = read_round_info(p);
        info.count = ++count;
        set_pot(info.pot);
        React react = ai_pointer(info);
        long long chip_change = -(long long)react.amt;
        do_presettle(react);
        HandResult ai_handresult = judge(info.player1);
        HandResult human_handresult = judge(info.player2);
        if (react.act != FOLD && ai_handresult.weight > human_handresult.weight){
            chip_change += (long long)get_pot();
            set_chip(get_chip() + get_pot());
            set_pot(0);
        } 

/*      检查judge是否正确
        int rrr = ai_handresult.weight > human_handresult.weight ? 1 : 0;
        if (rrr != info.result) printf("%d,%x,%x\t",count,ai_handresult.weight , human_handresult.weight);
*/
        if (react.pp >= 0.0)
            fprintf(OUTPUT, "%d,%.3lf,%s,%+lld,%lld\n",
                 count, react.pp, action_to_string(react.act), (long long)chip_change, (long long)get_chip());
        else 
            fprintf(OUTPUT, "%d,%s,%+lld,%lld\n",
             count, action_to_string(react.act), (long long)chip_change, (long long)get_chip());
        if (count % 1000 == 0) {
            printf("in round %d ...\n",count);
        }
        if (get_chip() <= 0) {
            printf("ai lose in round %d ...\n",count);
            break;
        }
    }
    fclose(DATA);
    fclose(OUTPUT);
    free(line);

    return 0;
}