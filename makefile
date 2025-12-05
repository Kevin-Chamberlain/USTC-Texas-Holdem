test: test.c game/card.c game/judgement.c game/library.c
	gcc test.c game/card.c game/judgement.c game/library.c -o test -I.
	

clean:
	rm -f test

.PHONY:clean

#记得关断言