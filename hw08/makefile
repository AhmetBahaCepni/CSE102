all: compile run clean

compile: main.c utils.h
	@gcc main.c -o 8_puzzle

run: 8_puzzle
	@./8_puzzle

clean:
	@rm -f 8_puzzle