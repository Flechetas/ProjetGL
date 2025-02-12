NAME = ./build/main
CC = gcc
MKDIR = mkdir -p
RM = rm -f
RMDIR = rm -rf
CFLAGS = -Wall -I/usr/include/SDL2 -Iinclude -D_REENTRANT
LDFLAGS = -lSDL2 -lm

SRC_DIR = src
INC_DIR = include
TEST_DIR = test
BUILD_DIR = build

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TESTS = $(shell find $(TEST_DIR) -name '*.c')
SRC_SUBDIRS = $(shell find $(SRC_DIR) -type d)
BUILD_SUBDIRS = $(SRC_SUBDIRS:$(SRC_DIR)%=$(BUILD_DIR)%)

.PHONY: all clean directories check-compiler test

all: check-compiler directories $(NAME)

check-compiler:
	@echo "Checking GCC version..."
	@$(CC) --version
	@if [ ! -x "$$(command -v $(CC))" ]; then \
		echo "Error: GCC not found"; \
		exit 1; \
	fi

directories: $(BUILD_SUBDIRS)

$(BUILD_SUBDIRS):
	@$(MKDIR) $@

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@
	@echo "Build complete!"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | directories
	@echo "Compiling $<..."
	$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

test: all $(TESTS)
	@echo "Starting test..."
	$(CC) -o t $(TESTS)
	./t

clean:
	@echo "Cleaning build files..."
	$(RMDIR) $(BUILD_DIR)
	$(RM) $(NAME)
