default:
	gcc -g -o prog main.c time.c listArrayList.c listElem.c mapElem.c mapArrayList.c stringCode.c input.c utils.c airline.c airport.c flight.c projectMethods.c -lm
clean:
	rm -f prog
debug:
	gcc -g -o prog main.c time.c listArrayList.c listElem.c mapElem.c mapArrayList.c stringCode.c input.c utils.c airline.c airport.c flight.c projectMethods.c -lm
	valgrind --leak-check=full ./prog
run:
	./prog