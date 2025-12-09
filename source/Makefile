PROGRAM_NAME = compiledCode
CXX = /opt/homebrew/opt/llvm/bin/clang++

CXXFLAGS_RELEASE = -std=c++23 -O3
CXXFLAGS_DEBUG   = -std=c++23 -O0 -g -DDEBUG_BUILD
CXXFLAGS         = $(CXXFLAGS_RELEASE)
CPPFLAGS         = -MMD -MP

# ---- GoogleTest config ----
GTEST_DIR      = /opt/homebrew/opt/googletest
GTEST_INCLUDE  = $(GTEST_DIR)/include
GTEST_LIB_DIR  = $(GTEST_DIR)/lib
GTEST_LIBS     = -L$(GTEST_LIB_DIR) -lgtest -lgtest_main -pthread

BUILD_DIR := ../build

# Source files for the main program (no test sources here)
SRCS := main.cpp worlds.cpp integrations.cpp util/vecmath.cpp util/error.cpp util/log.cpp

# Source files that contain unit tests
TEST_SRCS := util/vecmath_test.cpp

OBJS      := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:%.cpp=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

TEST_PROGRAM := tests

$(PROGRAM_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_PROGRAM): $(filter-out $(BUILD_DIR)/main.o,$(OBJS)) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -I$(GTEST_INCLUDE) -c $< -o $@

.PHONY: clean run render debug test

clean:
	rm -rf $(BUILD_DIR) *.dSYM $(PROGRAM_NAME) $(TEST_PROGRAM)

OUT ?= image.ppm

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS)

render: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS) > ../images/"$(OUT)"
	kitten icat ../images/"$(OUT)"

debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
debug: clean $(PROGRAM_NAME)

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

-include $(DEPS)

