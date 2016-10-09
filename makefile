compile:
	gcc -o clocure main.c repl.c parser.c -I.

run: compile
	./clocure

clean:
	rm *.out
