#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  //用_getch()

void clear_screen() {
    printf("\033[2J");      // 清除屏幕
    printf("\033[H");       // 光标移动到左上角
}

// 移动光标到指定位置
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

// 设置颜色
void set_color(int color) {
    printf("\033[%dm", color);
}

// 重置颜色
void reset_color() {
    printf("\033[0m");
}

// 欢迎
void display_welcome(int cursor_row) {
    clear_screen();
    
    set_color(36);  // 青色
    printf("=== 德州扑克欢迎您 ===\n\n");
    reset_color();
    
    set_color(33);  // 黄色
    printf("请选择AI策略：\n\n");
    reset_color();
    
    char* menu_items[] = {
        "1. 复读机",
        "2. 激进赌徒",
        "3. 傻瓜保守",
        "4. 神奇AI",
        "5. 退出程序"
    };

    int total_items = sizeof(menu_items) / sizeof(menu_items[0]);
    
    for (int i = 0; i < total_items; i++) {
        if (i + 1 == cursor_row) {
            set_color(31);  // 红色
            printf("> ");
        } else {
            printf("  ");
        }
        
        printf("%s\n", menu_items[i]);
        reset_color();
    }
    printf("\n");

}

