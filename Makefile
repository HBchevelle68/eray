
## Path variables
DIR := ${CURDIR}
INCLUDE= $(DIR)/include
BIN = $(DIR)/binaries
SRC = $(DIR)/src

#Build variables
CC=gcc
CFLAGS= -Werror -Wall -I$(INCLUDE)
RELEASE= -s -Os
LFLAGS=
DBG= -g3 -fsanitize=address
ASAN_LIBS = -lasan
DEPS= $(addprefix $(INCLUDE)/, e32.h e64.h )
ROBJS=$(addprefix $(SRC)/, eray.o e32.o e64.o)
DOBJS=$(addprefix $(SRC)/, eray-debug.o e32-debug.o e64-debug.o)

.PHONY: clean

all: clean eray-release eray-debug

eray-release: $(ROBJS)
	$(CC) $(CFLAGS) $(RELEASE) $^ $(LFLAGS) -o $(BIN)/$@

eray-debug: $(DOBJS) 
	$(CC) $(CFLAGS) $(DBG) $^ $(LFLAGS) $(ASAN_LIBS) -o $(BIN)/$@

%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) $(RELEASE) $< -o $@

%-debug.o: %.c $(DEPS)
	$(CC) -c $(DBG) $(CFLAGS) $< -o $@

clean:
	rm -fr $(DIR)/binaries/* $(SRC)/*.o
