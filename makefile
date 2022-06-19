
output: main.o Server.o HttpResponse.o HttpRequest.o
	g++ main.o Server.o HttpResponse.o HttpRequest.o -l sqlite3 -o output

main.o: main.cpp
	g++ -c main.cpp

Server.o: Server.cpp Server.h
	g++ -c Server.cpp

HttpResponse.o: HttpResponse.cpp HttpResponse.h
	g++ -c HttpResponse.cpp

HttpRequest.o: HttpRequest.cpp HttpRequest.h
	g++ -c HttpRequest.cpp


clean:
	rm -f *.o *.out output

