all: texthandler.o passwordhandler.o utility.o main.o pasman clean

passwordhandler.o: ./src/PasswordHandler/passwordhandler.cpp ./src/PasswordHandler/passwordhandler.h
	g++  -c ./src/PasswordHandler/passwordhandler.cpp

texthandler.o: ./src/TextHandler/texthandler.cpp ./src/TextHandler/texthandler.h
	g++ -c ./src/TextHandler/texthandler.cpp

utility.o: ./src/Utility/utility.cpp ./src/Utility/utility.h
	g++ -c ./src/Utility/utility.cpp

main.o: ./src/main.cpp
	g++ -c ./src/main.cpp

pasman: texthandler.o passwordhandler.o utility.o main.o 
	g++ texthandler.o passwordhandler.o utility.o main.o -o pasman

clean:
	rm -f *.o