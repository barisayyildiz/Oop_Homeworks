run:
	g++ main.cpp hex.cpp -o main
	./main
	rm main

dev:
	g++ test.cpp -o test
	./test
	rm test