run:
	g++ -std=c++11 main.cpp ./src/hexbase.cpp ./src/hexarray.cpp ./src/hexvector.cpp ./src/globals.cpp -o main -Wall -Wextra
	./main
	rm main

