all: texthandler.o passwordhandler.o main.o test clean

passwordhandler.o: ./src/PasswordHandler/passwordhandler.cpp ./src/PasswordHandler/passwordhandler.h
	g++-11 -c ./src/PasswordHandler/passwordhandler.cpp

texthandler.o: ./src/TextHandler/texthandler.cpp ./src/TextHandler/texthandler.h
	g++-11 -c ./src/TextHandler/texthandler.cpp

main.o: ./src/main.cpp
	g++-11 -c ./src/main.cpp

test: texthandler.o passwordhandler.o main.o 
	g++-11 texthandler.o passwordhandler.o main.o -o test

clean:
	rm -f *.o