all: compile run clean

compile: main.c
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc main.c -o snake_game

run: snake_game
	@echo "-------------------------------------------"
	@echo "Running.."
	@./snake_game

leaks: main.c	# This rule allow users to compile and run the program with valgrind
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -g main.c -o snake_game_test
	@echo "-------------------------------------------"
	@echo "Running valgrind..."
	@valgrind --leak-check=full ./snake_game_test
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f snake_game_test

clean: # clean rule works for cleaning the extra files that created in make process, for example object files and output files in this make
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f snake_game