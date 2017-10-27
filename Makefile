prog:
	clang++ test.cpp -o test.out
	clang++ meta_test.cpp -o meta_test.out

test:
	./test.out > test.txt
	diff test.txt test_output.txt
	rm test.txt
	./meta_test.out
