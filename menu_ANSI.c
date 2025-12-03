#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "posix_getch.h"

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
int do_welcome(){
    int cursor_row = 1;  //光标行
    int total_items = 5; //菜单项数
    int key;
    
    // 隐藏光标
    printf("\033[?25l");

    display_welcome(cursor_row);
    while (1) {
        key = posix_getch();
        
        // 检测 ESC 序列（箭头键）
        if (key == 27) {
            int next1 = posix_getch();
            if (next1 == '[') {
                int next2 = posix_getch();
                if (next2 == 'A') {  // 上箭头
                    if (cursor_row > 1) {
                        cursor_row--;
                    } else {
                        cursor_row = total_items;
                    }
                    display_welcome(cursor_row);
                }
                else if (next2 == 'B') {  // 下箭头
                    if (cursor_row < total_items) {
                        cursor_row++;
                    } else {
                        cursor_row = 1;
                    }
                    display_welcome(cursor_row);
                }
            } else {
                // 纯 ESC 键退出
                clear_screen();
                printf("\033[?25h");
                printf("已退出\n");
                exit(0);
            }
        }
        // 回车键
        else if (key == '\r' || key == '\n') {
            clear_screen();
            if (cursor_row == 5) {
                printf("退出程序...\n");
                printf("\033[?25h");    // 显示光标
                exit(0);
            } else {
                return cursor_row;
            }
        }
    }
}

// 二级菜单
void display_work(int se_cursor_row) {

    clear_screen();
    set_color(36);  // 青色
    printf("=== 游戏内容 ===\n\n");
    reset_color();

    set_color(33);  // 黄色
    printf("请选择AI处理对象：\n\n");
    reset_color();

    char* se_menu_items[] = {
        "1. games_1.csv",
        "2. games_2.csv",
        "3. games_3.csv",
        "4. games_master.csv",
        "5. real-time play",
        "6. 返回主菜单"
    };
    int se_total_items = sizeof(se_menu_items) / sizeof(se_menu_items[0]);
 
    for (int i = 0; i < se_total_items; i++) {
        if (i + 1 == se_cursor_row) {
            set_color(31);  // 红色
            printf("> ");
        } else {
            printf("  ");
        }
        printf("%s\n", se_menu_items[i]);
        reset_color();
    }
    printf("\n");
}
int do_work(){
    int se_cursor_row = 1;  //光标行
    int se_total_items = 6; //菜单项数
    int key;
    
    // 隐藏光标
    printf("\033[?25l");
    
    display_work(se_cursor_row);
    while (1) {
        key = posix_getch();
        
        // 检测 ESC 序列（箭头键）
        if (key == 27) {
            int next1 = posix_getch();
            if (next1 == '[') {
                int next2 = posix_getch();
                if (next2 == 'A') {  // 上箭头
                    if (se_cursor_row > 1) {
                        se_cursor_row--;
                    } else {
                        se_cursor_row = se_total_items;
                    }
                    display_work(se_cursor_row);
                }
                else if (next2 == 'B') {  // 下箭头
                    if (se_cursor_row < se_total_items) {
                        se_cursor_row++;
                    } else {
                        se_cursor_row = 1;
                    }
                    display_work(se_cursor_row);
                }
            } else {
                // 纯 ESC 键返回上级菜单
                clear_screen();
                printf("\033[?25h");
                printf("return\n");
                return -1;
            }
        }
        // 回车键
        else if (key == '\r' || key == '\n') {
            clear_screen();
            if (se_cursor_row == 6) {
                return -1;
            } else {
                return se_cursor_row;
            }
        }
    }
}