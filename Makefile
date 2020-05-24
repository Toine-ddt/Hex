#GSL_PATH=/net/ens/renault/save/gsl-2.6/install/include/

# '?=' Variable defined only if it wasn't defined before
GSL_PATH ?= /usr/local
SRC = src
TEST = test
INST = install
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O0	 
CPPFLAGS = -I ${GSL_PATH}/include -I ${SRC} #-I /home/omar/gsl/include
LIBFLAGS = -fPIC -shared
CFILES = graph.c move.c server.c player_rand.c
TESTFILES = test_graph test_func_rand test_is_winning alltests
OBJ = $(SRC:.c=.o)
BIN = server
TMP = tmp_clem
LIB = libplayer1.so libplayer2.so Djiplayer.so Djiplayer2.so
LD_LIBRARY_FLAGS = -L${GSL_PATH}/lib -lgsl -lgslcblas -ldl

ifeq ($(shell uname -s), Darwin)
	LIBGCOV=-fprofile-arcs -ftest-coverage
else
	LIBGCOV=-lgcov
endif



all: build

build: ${BIN}

test: ${TESTFILES}

tmp: ${TMP}

#Installe les fichiers demandés dans le répertoire install et les ajoute à la branche sur git
install: server ${LIB} alltests
	cp ${LIB} server alltests ${INST}/


#Remove all comiled and intalled files (libraries , object files etc.)
clean:
	rm -f *.o src/*.o *~ *\# *.so ${SRC}/*~ ${TEST}/*~ ${BIN} ${TESTFILES} ${TMP} ${INST}/server ${INST}/alltests ${INST}/libplayer1.so ${INST}/libplayer2.so ${INST}/Djiplayer.so ${INST}/Djiplayer2.so 

#Enregistre les modification des fichiers dans install à l'interieur de la branche master


#Dynamic library.

libplayer1.so: ${SRC}/player_rand.c ${SRC}/graph_operation.c	
	${CC} ${CFLAGS} ${CPPFLAGS} ${LIBFLAGS} -o $@ ${SRC}/player_rand.c

libplayer2.so: ${SRC}/player_rand.c ${SRC}/graph_operation.c	
	${CC} ${CFLAGS} ${CPPFLAGS} ${LIBFLAGS} -o $@ ${SRC}/player_rand.c

Djiplayer.so: ${SRC}/Djiplayer.c ${SRC}/graph_operation.c	
	${CC} ${CFLAGS} ${CPPFLAGS} ${LIBFLAGS} -o $@ ${SRC}/Djiplayer.c


Djiplayer2.so: ${SRC}/Djiplayer.c ${SRC}/graph_operation.c	
	${CC} ${CFLAGS} ${CPPFLAGS} ${LIBFLAGS} -o $@ ${SRC}/Djiplayer.c

#Sources:
server: libplayer2.so Djiplayer.so Djiplayer2.so libplayer1.so ${SRC}/server.c graph_operation.o player_operation.o
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ graph_operation.o player_operation.o ${SRC}/server.c ${LD_LIBRARY_FLAGS} -lm

player_operation.o: ${SRC}/player_operation.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c ${SRC}/player_operation.c ${LD_LIBRARY_FLAGS}


player_rand.o: ${SRC}/player_rand.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c ${SRC}/player_rand.c ${LD_LIBRARY_FLAGS}

Djiplayer.o: ${SRC}/Djiplayer.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c ${SRC}/Djiplayer.c ${LD_LIBRARY_FLAGS}

graph_operation.o: ${SRC}/graph_operation.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c ${SRC}/graph_operation.c ${LD_LIBRARY_FLAGS}



#Test executables.

tmp_clem: ${SRC}/tmp_clem.c graph_operation.o
	${CC}  ${CPPFLAGS} ${CFLAGS} -lm -o $@ graph_operation.o ${SRC}/tmp_clem.c ${LD_LIBRARY_FLAGS} 

test_graph: graph_operation.o ${TEST}/test_graph.c
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ graph_operation.o ${SRC}/graph.c ${TEST}/test_graph.c ${LD_LIBRARY_FLAGS}

#test_move:graph_operation.o player_operation.o player_rand.o ${SRC}/move.c ${TEST}/test_move.c
#	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ player_operation.o player_rand.o graph_operation.o ${SRC}/move.c ${TEST}/test_move.c ${LD_LIBRARY_FLAGS}

test_func_rand:graph_operation.o player_rand.o player_operation.o ${TEST}/func_test_strat_player.c
	${CC} ${CPPFLAGS} ${CFLAGS} -DRAND -o $@ graph_operation.o player_rand.o player_operation.o ${TEST}/func_test_strat_player.c ${LD_LIBRARY_FLAGS}

test_func_dji:graph_operation.o Djiplayer.o player_operation.o ${TEST}/func_test_strat_player.c
	${CC} ${CPPFLAGS} ${CFLAGS} -DDJI -o $@ graph_operation.o Djiplayer.o player_operation.o ${TEST}/func_test_strat_player.c ${LD_LIBRARY_FLAGS}

test_is_winning:${TEST}/test_is_winning.c graph_operation.o
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ graph_operation.o ${TEST}/test_is_winning.c ${LD_LIBRARY_FLAGS}

#mytest:${SRC}/mytest.c graph_operation.o
#	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ graph_operation.o ${SRC}/mytest.c ${LD_LIBRARY_FLAGS}

alltests: ${TEST}/alltests.c

#	${CC} -fprofile-arcs -ftest-coverage ${CPPFLAGS} ${CFLAGS} -lgcov -o $@ ${TEST}/alltests.c #${LD_LIBRARY_FLAGS}

	${CC} ${CPPFLAGS} ${CFLAGS} -lgcov -o $@ ${TEST}/alltests.c ${LD_LIBRARY_FLAGS} ${LIBGCOV}
