CC = gcc
TARGET_EXEC := engine
SRC_DIR := src
BUILD_DIR := build
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCFLAGS := -I./include -I./external/cglm/include
CFLAGS := $(INCFLAGS) -MMD -Wall -Wextra
LDFLAGS := $(shell sdl2-config --cflags --libs)
LDFLAGS += -lm

DEBUG ?= OFF
OPTIMIZE ?= OFF

ifeq ($(DEBUG), ON) 
	CFLAGS += -g -DDEBUG
else ifeq ($(OPTIMIZE), ON)
	CFLAGS += -O2
endif

$(TARGET_EXEC): $(OBJS)
	@echo "[INFO] DEBUG is set to $(DEBUG)"
	@echo "[INFO] OPTIMIZE is set to $(OPTIMIZE)"
	@echo "[INFO] CFLAGS is $(CFLAGS)"
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	
# $(OBJS): $(SRCS) $(BUILD_DIR)/$(SRC_DIR)
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BUILD_DIR)/$(SRC_DIR):
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	
.PHONY: clean
clean: 
	rm -rf build $(TARGET_EXEC)
	
-include $(DEPS)
