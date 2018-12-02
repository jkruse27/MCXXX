CC=gcc
FLAGS=-std=c99 -pedantic -Wall -lm
BIN=lab06
SOURCE=lab06.c
INPUT_PATH=input
OUTPUT_PATH=output

build:
	$(CC) $(SOURCE) $(FLAGS) -o $(BIN)

run:build
	./$(BIN) < $/arq1.in > $/arq1.out
	./$(BIN) < $/arq2.in > $/arq2.out
	./$(BIN) < $/arq3.in > $/arq3.out
	./$(BIN) < $/arq4.in > $/arq4.out
	./$(BIN) < $/arq5.in > $/arq5.out

test:run
	-sdiff -s $/arq1.out $/arq1.res
	-sdiff -s $/arq2.out $/arq2.res
	-sdiff -s $/arq3.out $/arq3.res
	-sdiff -s $/arq4.out $/arq4.res
	-sdiff -s $/arq5.out $/arq5.res

valgrind:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(BIN) < $/arq1.in > $/arq1.out -v
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(BIN) < $/arq2.in > $/arq2.out
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(BIN) < $/arq3.in > $/arq3.out
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(BIN) < $/arq4.in > $/arq4.out
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(BIN) < $/arq5.in > $/arq5.out
