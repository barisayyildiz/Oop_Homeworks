run:
	g++ -std=c++11 main.cpp hexbase.cpp hexarray.cpp -o main -Wall -Wextra
	./main
	rm main
	rm *.txt
