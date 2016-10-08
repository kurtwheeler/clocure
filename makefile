compile:
	gcc -o clocure main.c

run: compile
	./clocure

clean:
	rm *.out
