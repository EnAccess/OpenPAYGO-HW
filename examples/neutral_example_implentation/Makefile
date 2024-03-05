CC = gcc
LIBS = -lm

SRC_DIR   := . unix_device ../../src
INC_DIR   := ../../src

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ       := $(patsubst src/%.c,build/%.o,$(SRC))

vpath %.c $(SRC_DIR)

.PHONY: all clean

all: opaygo.bin

opaygo.bin: $(OBJ)
	$(CC) -I$(INC_DIR) $^ $(LIBS) -o $@

check: $(OBJ)
	$(CC) -I$(INC_DIR) -Werror $^ $(LIBS) -o /dev/null

clean:
	@rm -f opaygo.bin
