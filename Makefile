prog:
	clang++ test.cpp -o test.out

test:
	./test.out > test.txt
	diff test.txt test_output.txt
	rm test.txt
