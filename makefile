# Makefile for a C++ Breakout project
CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS ?=
LIBS ?=

# Toggle debug: make DEBUG=1
ifeq ($(DEBUG),1)
CXXFLAGS += -O0 -g -DDEBUG
else
CXXFLAGS += -O2 -DNDEBUG
endif

SRC_DIR := src
BUILD_DIR := build
TARGET := breakout

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean distclean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# compile and generate dependency files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(wildcard $(DEPS))

clean:
	rm -rf $(BUILD_DIR)

distclean: clean
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)