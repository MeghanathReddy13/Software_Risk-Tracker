# Shelby Stanly
ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model
VIEW_FOLDER=${ROOT}/src/view

SRCS= driver.cpp exportTest.cpp \
	  riskItemModel.cpp riskExportView.cpp
OBJS=${SRCS:S/cpp$/o/g}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER} -I${VIEW_FOLDER}
LDFLAGS=-L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt

.PHONY: all clean

.PATH:=${MODEL_FOLDER}

all: exportTest

exportTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

riskItemModel.o: ${MODEL_FOLDER}/riskItemModel.cpp ${MODEL_FOLDER}/riskItemModel.h
riskExportView.o: ${VIEW_FOLDER}/riskExportView.cpp ${VIEW_FOLDER}/riskExportView.h

test: exportTest
	@./exportTest 2>/dev/null || ./exportTest

clean:
	@rm -f exportTest *.o *.core
