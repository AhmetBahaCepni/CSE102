all: clean compile run

# We compile our files with -lm flag because we use math.h library and math.h library wants this linking flag
compile: main.c util.c util.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test main.c util.c -lm

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test

