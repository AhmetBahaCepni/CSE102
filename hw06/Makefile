all: compile run clean

compile: main.c file_ops.c search_product.c stock_status.c brand_stock.c export_report.c utils.h
	@gcc main.c file_ops.c search_product.c stock_status.c brand_stock.c export_report.c -o test

run: test
	@./test

clean:
	@rm -f test