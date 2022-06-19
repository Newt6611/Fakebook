
output: main.o Server.o HttpResponse.o HttpRequest.o UserService.o
	g++ main.o Server.o HttpResponse.o HttpRequest.o UserService.o -l sqlite3 -o output

main.o: main.cpp
	g++ -c main.cpp

Server.o: Server.cpp Server.h
	g++ -c Server.cpp

HttpResponse.o: HttpResponse.cpp HttpResponse.h
	g++ -c HttpResponse.cpp

HttpRequest.o: HttpRequest.cpp HttpRequest.h
	g++ -c HttpRequest.cpp

UserService.o: Services/UserService.cpp Services/UserService.h
	g++ -c Services/UserService.cpp
c: #clean
	rm -f *.o *.out output

