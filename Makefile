prog:
	g++ test.cpp --coverage -o test.out
	g++ meta_test.cpp --coverage -o meta_test.out

test:
	./test.out > test.txt
	diff test.txt test_output.txt
	rm test.txt
	./meta_test.out
