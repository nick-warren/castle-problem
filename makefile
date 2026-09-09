all: CastleProblem.exe

CastleProblem.exe: CastleProblem.o
	 gcc -o CastleProblem.exe CastleProblem.o

CastleProblem.o: CastleProblem.cpp
	 gcc -c CastleProblem.cpp

clean:
	 rm CastleProblem.o CastleProblem.exe
