# Shelby Stanly
ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model

SRCS= driver.cpp scaleLabelUnitTest.cpp \
	  scaleLabelModel.cpp
OBJS=${SRCS:S/cpp$/o/g}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS=-L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt

.PHONY: all clean

.PATH:=${MODEL_FOLDER}

all: scaleLabelUnitTest

scaleLabelUnitTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

scaleLabelModel.o: ${MODEL_FOLDER}/scaleLabelModel.cpp ${MODEL_FOLDER}/scaleLabelModel.h

test: scaleLabelUnitTest
	@./scaleLabelUnitTest 2>/dev/null || ./scaleLabelUnitTest

clean:
	@rm -f scaleLabelUnitTest *.o *.core
