run:
	g++ -std=c++11 main.cpp hex.cpp -o main -Wall -Wextra
	./main
	rm main

dev:
	g++ -std=c++11 test.cpp hex.cpp -o test -Wall -Wextra
	./test
	rm test
