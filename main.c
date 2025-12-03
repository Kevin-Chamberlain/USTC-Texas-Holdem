#include <stdio.h>
#include "menu.h"
int main() {
    int ai_strategy, file_choice;
    for (int i = 0; i < 1; i++) {
        ai_strategy = do_welcome();
        file_choice = do_work();
        i += file_choice == -1 ? -1 : 0;
    }

    return 0;
}