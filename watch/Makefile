CC = sdcc

OUTPUT = build/result

SRC_DIR = src
OBJ_DIR = build/obj
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.rel,$(SRC_FILES))

CFLAGS = --std-sdcc17 -mstm8

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(CFLAGS) -o $(OUTPUT)

$(OBJ_DIR)/%.rel: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ_DIR)/*.* $(OUTPUT).* $(OUTPUT)

.PHONY: all clean
