CC = g++
CFLAGS = -Wall -g /usr/X11R6/include
EXEC = chess
OBJECTS = main.o window.o move.o helper.o game.o board.o piece.o pieceImpl.o pawnImpl.o knightImpl.o bishopImpl.o rookImpl.o queenImpl.o kingImpl.o
DEPENDS = ${OBJECTS:.o=.d}

all: ${OBJECTS}
	${CC} ${CFLAGS} /usr/X11R6/lib -X11 ${OBJECTS} -o ${EXEC}

main.o: main.cc
	${CC} ${CFLAGS} -c -o main.o main.cc

window.o: window.cc window.h
	${CC} ${CFLAGS} -c -o window.o window.cc

move.o: move.cc move.h
	${CC} ${CFLAGS} -c -o move.o move.cc

helper.o: helper.cc helper.h
	${CC} ${CFLAGS} -c -o helper.o helper.cc

game.o: game.cc game.h
	${CC} ${CFLAGS} -c -o game.o game.cc

board.o: board.cc board.h
	${CC} ${CFLAGS} -c -o board.o board.cc

piece.o: piece.cc piece.h
	${CC} ${CFLAGS} -c -o piece.o piece.cc

pieceImpl.o: pieceImpl.cc pieceImpl.h
	${CC} ${CFLAGS} -c -o pieceImpl.o pieceImpl.cc

pawnImpl.o: pawnImpl.cc pawnImpl.h
	${CC} ${CFLAGS} -c -o pawnImpl.o pawnImpl.cc

knightImpl.o: knightImpl.cc knightImpl.h
	${CC} ${CFLAGS} -c -o knightImpl.o knightImpl.cc

bishopImpl.o: bishopImpl.cc bishopImpl.h
	${CC} ${CFLAGS} -c -o bishopImpl.o bishopImpl.cc

rookImpl.o: rookImpl.cc rookImpl.h
	${CC} ${CFLAGS} -c -o rookImpl.o rookImpl.cc

queenImpl.o: queenImpl.cc queenImpl.h
	${CC} ${CFLAGS} -c -o queenImpl.o queenImpl.cc

kingImpl.o: kingImpl.cc kingImpl.h
	${CC} ${CFLAGS} -c -o kingImpl.o kingImpl.cc

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
