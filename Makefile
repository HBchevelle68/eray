CC=gcc
CFLAGS= -Werror -Wall
RELEASE= -s -Os
LFLAGS=
DBG= -g3 -fsanitize=address
ASAN_LIBS = -lasan
DIR := ${CURDIR}
INCLUDE= $(DIR)/include
BIN = $(DIR)/binaries
SRC = $(DIR)/src

.PHONY: clean

all: clean eray-release eray-debug

eray-release: eray.o
	$(CC) $(SRC)/$^ $(LFLAGS) -o $(BIN)/$@ $(CFLAGS) $(RELEASE)

eray-debug: eray-debug.o
	$(CC) $(SRC)/$^ $(LFLAGS) $(ASAN_LIBS) -o $(BIN)/$@ $(CFLAGS)

%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $(RELEASE) $< -o $(SRC)/$@

%-debug.o: $(SRC)/%.c
	$(CC) -c $(DBG) $(CFLAGS) $< -o $(SRC)/$@

clean:
	rm -fr $(DIR)/binaries/* $(SRC)/*.o
