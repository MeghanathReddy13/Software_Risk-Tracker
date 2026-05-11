
ROOT != git rev-parse --show-toplevel
MODEL_FOLDER = ${ROOT}/src/model

SRCS = main.cpp \
       TestProject.cpp

CXXFLAGS = -Wall -std=c++20
CXXFLAGS += -I/usr/local/include -I${MODEL_FOLDER}

LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lpthread

.PHONY: all clean test

all: run_tests

run_tests: ${SRCS} ${MODEL_FOLDER}/userModel.h ${MODEL_FOLDER}/accessModel.h ${MODEL_FOLDER}/projectModel.h ${MODEL_FOLDER}/riskItemModel.h
	${CXX} ${CXXFLAGS} -o $@ ${SRCS} ${LDFLAGS}

test: run_tests
	./run_tests

clean:
	rm -f run_tests *.o *.core *.db
