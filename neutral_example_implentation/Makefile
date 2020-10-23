CC = gcc
LIBS = -lm

SRC_DIR   := . unix_device opaygo_decoder

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ       := $(patsubst src/%.c,build/%.o,$(SRC))

vpath %.c $(SRC_DIR)

.PHONY: all clean

all: opaygo.bin

opaygo.bin: $(OBJ)
	$(CC) $^ $(LIBS) -o $@

clean:
	@rm -f opaygo.bin