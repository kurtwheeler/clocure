compile:
	gcc -o clocure main.c repl.c reader.c value.c -I.

run: compile
	./clocure

clean:
	rm *.out
