CC=g++ --std=c++11 -g
exe_file=open_bookstore

$(exe_file): main.cpp book.o catalogue.o order.o store.o
	$(CC) main.cpp book.o catalogue.o order.o store.o -o $(exe_file)

book.o: book.h book.cpp
	$(CC) -c book.cpp

catalogue.o: catalogue.h catalogue.cpp
	$(CC) -c catalogue.cpp

order.o: order.h order.cpp
	$(CC) -c order.cpp

store.o: store.h store.cpp
	$(CC) -c store.cpp

clean: 
	rm -f *.o $(exe_file)