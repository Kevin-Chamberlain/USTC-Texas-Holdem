poker.exe: game/main.o game/card.o game/judgement.o game/library.o game/m_ai.o game/procedure.o game/action.o game/var_global.o welcome/menu_ANSI.o welcome/posix_getch.o
	gcc -std=c11 -O2 -g game/main.o game/card.o game/judgement.o game/library.o game/m_ai.o game/procedure.o game/action.o game/var_global.o welcome/menu_ANSI.o welcome/posix_getch.o -o poker.exe -I.


game/main.o: game/main.c
	gcc -std=c11 -O2 -g -c game/main.c -o game/main.o -I.

game/card.o: game/card.c
	gcc -std=c11 -O2 -g -c game/card.c -o game/card.o -I.

game/judgement.o: game/judgement.c
	gcc -std=c11 -O2 -g -c game/judgement.c -o game/judgement.o -I.

game/library.o: game/library.c
	gcc -std=c11 -O2 -g -c game/library.c -o game/library.o -I.

game/m_ai.o: game/m_ai.c
	gcc -std=c11 -O2 -g -c game/m_ai.c -o game/m_ai.o -I.

game/procedure.o: game/procedure.c
	gcc -std=c11 -O2 -g -c game/procedure.c -o game/procedure.o -I.

game/action.o: game/action.c
	gcc -std=c11 -O2 -g -c game/action.c -o game/action.o -I.

game/var_global.o: game/var_global.c
	gcc -std=c11 -O2 -g -c game/var_global.c -o game/var_global.o -I.

welcome/menu_ANSI.o: welcome/menu_ANSI.c
	gcc -std=c11 -O2 -g -c welcome/menu_ANSI.c -o welcome/menu_ANSI.o -I.

welcome/posix_getch.o: welcome/posix_getch.c
	gcc -std=c11 -O2 -g -c welcome/posix_getch.c -o welcome/posix_getch.o -I.

clean:
	rm -f poker.exe game/*.o welcome/*.o

.PHONY:clean

# 备注: 这个 Makefile 使用显式的 .o 生成规则并不使用 Make 变量或自动替换。