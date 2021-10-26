program1:
	gcc parte1.c -o parte1 -Wall
program2:	
	gcc parte2.c -o parte2 -Wall
.PHONY: parte1
.PHONY: parte2
.PHONY: clean
parte1: program1
	./parte1
parte2: program2
	./parte2
clean:
	rm ./parte1
	rm ./parte2