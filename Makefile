CC := gcc
CFLAGS := -Wall -Wextra -Werror -Wunused-parameter -g
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC_DIR := ./src
BUILD_DIR := ./build
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
EXEC := program

.PHONY: all run clean
all : $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $(EXEC)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(EXEC)

build: main.c
	$(CC) main.c -o $(EXEC)

clean:
	rm -rf $(BUILD_DIR) $(EXEC)
