test: main.c menu_ANSI.c posix_getch.c
	gcc -o test main.c menu_ANSI.c posix_getch.c

clean:
	rm -f test

.PHONY:clean
