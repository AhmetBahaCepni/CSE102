all: clean compile run # all rule cleans the object and output files than compiles the program and then runs the program

compile: main.c  # compile rule will look for main.c is changed or not and then compiles the c file
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test main.c -lm
	@echo "Compiled"

run: # run rule runs the output file ./test
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test

clean: # clean rule cleans the all object files and output file ./test
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
	@echo "Cleaned"

