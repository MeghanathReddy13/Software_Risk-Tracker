#makefile for witty hello world
CXXFLAGS=-Wall -g -I/usr/local/include
LDFLAGS=-L/usr/local/lib -lwt -lwthttp

.PHONY: all clean start stop

all: view

view: main1.cpp navView1.o
	${CXX} ${CXXFLAGS} -o $@ main1.cpp navView1.o ${LDFLAGS}

navView1.o: navView1.h navView1.cpp

clean:
	@rm -f hello *.o

start: view 
	./view --docroot . --http-address 0.0.0.0 --http-port 8084 & 

stop:
	pkill(1)


