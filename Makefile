run:
	g++ -std=c++11 main.cpp hexbase.cpp hexarray.cpp hexvector.cpp -o main -Wall -Wextra
	./main
	rm main
	rm *.txt


dev:
	g++ -std=c++11 test.cpp hexbase.cpp hexarray.cpp hexvector.cpp -o test -Wall -Wextra
	./test
	rm test


