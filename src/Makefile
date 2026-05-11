PROG=app
PORT=8086
SRCS=main.cpp riskTrackerApp.cpp \
	 loginView.cpp loginModel.cpp \
	 userManagerModel.cpp projectManagerModel.cpp riskManagerModel.cpp \
         authManagerModel.cpp databaseModel.cpp databaseManagerModel.cpp \
	 userModel.cpp riskItemModel.cpp projectModel.cpp accessModel.cpp auditLogModel.cpp \
	 roleModel.cpp scaleLabelModel.cpp navView.cpp proForm.cpp createUser.cpp \
	 confirmDialog.cpp projectNavView.cpp riskMatrixView.cpp riskAddForm.cpp \
	 riskView.cpp riskExportView.cpp riskEditForm.cpp
OBJS=${SRCS:S/cpp$/o/g}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${.CURDIR} -I${.CURDIR}/model -I${.CURDIR}/view
#LDFLAGS=-L/usr/local/lib
#LDFLAGS+=-lwthttp -lwt -lwtdbo -lcrypto -lsqlite3 -lpthread
LDFLAGS=-L/usr/local/lib
LDFLAGS+=-lwthttp -lwt -lwtdbo -lwtdbosqlite3 -lcrypto -lsqlite3 -lpthread

.PHONY: all clean start stop

all: ${PROG}

${PROG}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

# application
riskTrackerApp.o: riskTrackerApp.h riskTrackerApp.cpp

# model
databaseModel.o: model/databaseModel.cpp model/databaseModel.h
databaseManagerModel.o: model/databaseManagerModel.cpp model/databaseManagerModel.h
userModel.o: model/userModel.cpp model/userModel.h
riskItemModel.o: model/riskItemModel.cpp model/riskItemModel.h
projectModel.o: model/projectModel.cpp model/projectModel.h
accessModel.o: model/accessModel.cpp model/accessModel.h
auditLogModel.o: model/auditLogModel.cpp model/auditLogModel.h
roleModel.o: model/roleModel.cpp model/roleModel.h
scaleLabelModel.o: model/scaleLabelModel.cpp model/scaleLabelModel.h
projectManagerModel.o: model/projectManagerModel.h model/projectManagerModel.cpp
riskManagerModel.o: model/riskManagerModel.h model/riskManagerModel.cpp
authManagerModel.o: model/authManagerModel.h model/authManagerModel.cpp
loginModel.o: model/loginModel.h model/loginModel.cpp
userManagerModel.o: model/userManagerModel.h model/userManagerModel.cpp

# views
loginView.o: view/loginView.h view/loginView.cpp #view/login.css
navView.o: view/navView.h view/navView.cpp #view/nav.css
proForm.o: view/proForm.h view/proForm.cpp #view/nav.css
createUser.o: view/createUser.h view/createUser.cpp #view/style.css
confirmDialog.o: view/confirmDialog.h view/confirmDialog.cpp
projectNavView.o: view/projectNavView.h view/projectNavView.cpp #view/projectNavView.css
riskMatrixView.o: view/riskMatrixView.h view/riskMatrixView.cpp #view/riskMatrix.css
riskAddForm.o: view/riskAddForm.h view/riskAddForm.cpp #riskAddForm.css
riskEditForm.o: view/riskEditForm.h view/riskEditForm.cpp #riskEditForm.css
riskView.o: view/riskView.h view/riskView.cpp #view/style.css
riskExportView.o: view/riskExportView.h view/riskExportView.cpp 


# utilities
clean:
	@rm -f ${PROG} ${OBJS} *.core *.o risk.db

start: ${PROG}
	./${PROG} --docroot ../ --http-address 0.0.0.0 --http-port ${PORT} --resource-dir ./resources &

stop:
	@pkill ${PROG}
