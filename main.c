#include <stdio.h>
#include "menu.h"
int main() {
    int cursor_row = 1;  //光标行
    int total_items = 5; //菜单项数
    char key;
    
    // 隐藏光标
    printf("\033[?25l");
    
    display_welcome(cursor_row);
    while (1) {
        key = _getch();
        if (key == 0xE0) {  // 双字节扩展键前缀
            key = _getch();
            switch (key) {
                case 72:  // 上箭头
                    if (cursor_row > 1) {
                        cursor_row--;
                    } else {
                        cursor_row = total_items;
                    }
                    display_welcome(cursor_row);
                    break;
                    
                case 80:  // 下箭头
                    if (cursor_row < total_items) {
                        cursor_row++;
                    } else {
                        cursor_row = 1;
                    }
                    display_welcome(cursor_row);
                    break;
            }
        }
        // 回车键
        else if (key == '\r' || key == '\n') {
            clear_screen();
            if (cursor_row == 5) {
                printf("退出程序...\n");
                printf("\033[?25h");    // 显示光标
                return 0;
            }
        
            int strategy = cursor_row;
            


            printf("\n按任意键返回...\n");
            _getch();
            display_welcome(cursor_row);
        }
        // ESC键
        else if (key == 27) {
            clear_screen();
            printf("\033[?25h");
            printf("已退出\n");
            return 0;
        }
    }
    
    return 0;
}