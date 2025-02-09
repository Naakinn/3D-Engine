CC = gcc
TARGET_EXEC := engine
TARGET_BIN := $(TARGET_EXEC).tar.gz
SRC_DIR := src
BUILD_DIR := build
INC_DIR := include

SRCS := $(shell find $(SRC_DIR) -name '*.c')
INC_TO_FORMAT := $(shell find include -type f ! -name '*glad*' ! -name '*khr*')
OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCFLAGS := -I ./include -isystem ./external/cglm/include
CFLAGS := $(INCFLAGS) -MMD -Wall -Wextra -std=c99
LDFLAGS := $(shell sdl2-config --cflags --libs) -lm

all: debug

debug: CFLAGS += -g -DDEBUG 
release: CFLAGS += -O2
release: LDFLAGS += -flto
	
debug: $(TARGET_EXEC)
release: $(TARGET_EXEC)
	
$(TARGET_EXEC): $(OBJS)
	@echo "[INFO] CFLAGS is $(CFLAGS)"
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BUILD_DIR)/$(SRC_DIR):
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	
.PHONY: clean
clean: 
	rm -rf build $(TARGET_EXEC)
	rm -f $(TARGET_BIN)
	
format: $(INC_TO_FORMAT) $(subst $(SRC_DIR)/glad.c,,$(SRCS))
	@echo "[INFO] Formatting files $?"
	clang-format -i $?
	touch format
	
.PHONY: package
package: $(TARGET_BIN)
	
$(TARGET_BIN): $(TARGET_EXEC)
	@echo "[INFO] Packaging $(TARGET_EXEC) to $(TARGET_BIN)"
	tar -czf $(TARGET_BIN) $(TARGET_EXEC)
	
-include $(DEPS)
