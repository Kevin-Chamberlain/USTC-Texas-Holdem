test: test.c card.c judgement.c
	gcc test.c card.c judgement.c -o test
	

clean:
	rm -f test

.PHONY:clean
