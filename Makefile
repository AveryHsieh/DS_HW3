all: a.out

a.out:
	g++ -std=c++11 main.cpp

test: a.out
	./a.out 1

clean:
	rm a.out