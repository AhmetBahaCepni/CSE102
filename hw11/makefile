all: compile run clean

compile: main.c utils.c utils.h # This rule allow users to compile the program
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc main.c utils.c -o hw11

run: hw11
	@echo "-------------------------------------------"
	@echo "Running.."
	@./hw11

clean: # clean rule works for cleaning the extra files that created in make process, for example object files and output files in this make
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f hw11