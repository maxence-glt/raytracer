# --------- Toolchain ----------
PROGRAM_NAME ?= raytracer
CXX := /opt/homebrew/opt/llvm/bin/clang++

CXXFLAGS_COMMON  := -std=c++23

CXXFLAGS_RELEASE := $(CXXFLAGS_COMMON) -O3 \
	-Rpass=loop-vectorize -Rpass-missed=loop-vectorize \
	# -Rpass-analysis=loop-vectorize \
	-Rpass=slp-vectorizer -Rpass-missed=slp-vectorizer

CXXFLAGS_DEBUG   := $(CXXFLAGS_COMMON) -O0 -g -DDEBUG_BUILD \
	-fno-omit-frame-pointer -fno-optimize-sibling-calls \
	-fsanitize=address,undefined,leak -Wno-character-conversion

CPPFLAGS := -MMD -MP

# ---- GoogleTest config ----
GTEST_DIR      ?= /opt/homebrew/opt/googletest
GTEST_INCLUDE  := $(GTEST_DIR)/include
GTEST_LIB_DIR  := $(GTEST_DIR)/lib
GTEST_LIBS     := -L$(GTEST_LIB_DIR) -lgtest -lgtest_main -pthread

# --------- Build dirs ----------
BUILD_RELEASE := ../build/release
BUILD_DEBUG   := ../build/debug

# --------- Sources ----------
# main program sources (no test sources here)
SRCS := main.cpp worlds/manyballs.cpp util/error.cpp util/log.cpp util/profiler.cpp util/transform.cpp render/render.cpp util/transform.cpp

# Use bash so we can use PIPESTATUS
SHELL := /bin/bash

empty :=
space := $(empty) $(empty)

# dirs from SRCS: "worlds/ util/ render/" etc (no "./")
PROJ_DIRS := $(sort $(filter-out ./,$(dir $(SRCS))))
PROJ_DIR_ALT := $(subst $(space),|,$(PROJ_DIRS))

VEC_FILTER = rg -v '^In file included from' \
  | rg '^[^/].*:[0-9]+(:[0-9]+)?: (remark|warning|error):'

# test sources (recursive)
TEST_SRCS := $(shell find test -type f -name '*.cpp')

# --------- Objects ----------
RELEASE_OBJS := $(patsubst %.cpp,$(BUILD_RELEASE)/%.o,$(SRCS))
DEBUG_OBJS   := $(patsubst %.cpp,$(BUILD_DEBUG)/%.o,$(SRCS))
TEST_OBJS    := $(patsubst %.cpp,$(BUILD_DEBUG)/%.o,$(TEST_SRCS))

RELEASE_DEPS := $(RELEASE_OBJS:.o=.d)
DEBUG_DEPS   := $(DEBUG_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# --------- Binaries ----------
RELEASE_BIN := $(PROGRAM_NAME)
DEBUG_BIN   := $(PROGRAM_NAME)_debug
TEST_BIN    := tests

# --------- Default ----------
.PHONY: all
all: $(RELEASE_BIN)

# --------- Link rules ----------
$(RELEASE_BIN): $(RELEASE_OBJS)
	@$(CXX) $(CXXFLAGS_RELEASE) -o $@ $^ 2>&1 | $(VEC_FILTER); exit $${PIPESTATUS[0]}

$(DEBUG_BIN): $(DEBUG_OBJS)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^

# tests link against debug-built library objects (no main.o) + debug-built test objs
$(TEST_BIN): $(filter-out $(BUILD_DEBUG)/main.o,$(DEBUG_OBJS)) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^ $(GTEST_LIBS)

# --------- Compile rules ----------
$(BUILD_RELEASE)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS_RELEASE) $(CPPFLAGS) -c $< -o $@ 2>&1 | $(VEC_FILTER); exit $${PIPESTATUS[0]}

$(BUILD_DEBUG)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS_DEBUG) $(CPPFLAGS) -c $< -o $@

$(TEST_OBJS): CPPFLAGS += -I$(GTEST_INCLUDE)

# --------- Convenience targets ----------
.PHONY: clean run render debug test

clean:
	rm -rf ../build *.dSYM $(RELEASE_BIN) $(DEBUG_BIN) $(TEST_BIN)

OUT ?= image.ppm

run: $(RELEASE_BIN)
	./$(RELEASE_BIN) $(ARGS)

render: $(RELEASE_BIN)
	./$(RELEASE_BIN) $(ARGS) > ../images/"$(OUT)"
	kitten icat ../images/"$(OUT)"

debug: $(DEBUG_BIN)
	./$(DEBUG_BIN) $(ARGS)

test: $(TEST_BIN)
	./$(TEST_BIN)

-include $(RELEASE_DEPS) $(DEBUG_DEPS)

# --------- Notes ----------
# set your LLVM_SYMBOLIZER_PATH
# ASan: enable symbolization + leak detection on macOS
# set -gx ASAN_OPTIONS "detect_leaks=1:symbolize=1:abort_on_error=1:halt_on_error=1:malloc_context_size=50:verbosity=1"
# UBSan: print stack traces
# set -gx UBSAN_OPTIONS "print_stacktrace=1:symbolize=1:halt_on_error=1:verbosity=1"
# LSan verbosity (optional)
# set -gx LSAN_OPTIONS "verbosity=1"
