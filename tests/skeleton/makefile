# Hannah Lanier - 02/01/2026

MODEL_FOLDER=.

SRCS= main.cpp wittyTest.cpp
OBJS=${SRCS:S/cpp$/o/g}

CXXFLAGS=-Wall -std=c++2b
# Includes the current directory for your .h files
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}

# Libraries for GTest and Wt
LDFLAGS=-L/usr/local/lib -lgtest -lgtest_main -lwt -lwttest

.PHONY: all clean
.PATH: ${MODEL_FOLDER}

all: itest

itest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

# Dependency tracking
wittyTest.o: ${MODEL_FOLDER}/wittyTest.cpp ${MODEL_FOLDER}/wittyTest.h
main.o: ${MODEL_FOLDER}/main.cpp ${MODEL_FOLDER}/wittyTest.h

clean:
	@rm -f itest *.o
