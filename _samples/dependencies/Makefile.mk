
main: main.o
	gcc $< -o $@

%.o: %.c
	gcc -c $< -o $@

-include main.d
