# Hannah Lanier - 02/11/2026
MODEL_FOLDER=.

SRCS= main.cpp wittyTest.cpp login.cpp
OBJS=${SRCS:S/cpp$/o/g}

CXXFLAGS=-Wall -std=c++2b
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}

# Linking Wt, GTest, and Pthread
LDFLAGS=-L/usr/local/lib -lgtest -lgtest_main -lwttest -lwt -lwthttp -lpthread

.PATH: ${MODEL_FOLDER}

all: login_test_run

login_test_run: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

wittyTest.o: wittyTest.cpp wittyTest.h
login.o: login.cpp login.h wittyTest.h
main.o: main.cpp wittyTest.h login.h

clean:
	@rm -f login_test_run *.o
