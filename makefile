compile:
	gcc -o clocure main.c repl.c parser.c value.c -I.

run: compile
	./clocure

clean:
	rm *.out
