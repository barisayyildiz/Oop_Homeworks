run:
	g++ -std=c++11 main.cpp hex.cpp -o main -Wall -Wextra
	./main
	rm main

deneme:
	g++ test.cpp -o test
	./test
	rm test