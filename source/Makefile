PROGRAM_NAME = compiledCode
CXX = /opt/homebrew/opt/llvm/bin/clang++

CXXFLAGS_RELEASE = -std=c++23 -O3
CXXFLAGS_DEBUG   = -std=c++23 -O0 -g
CXXFLAGS         = $(CXXFLAGS_RELEASE)

CPPFLAGS = -MMD -MP

BUILD_DIR := ../build

SRCS := main.cpp worlds.cpp integrations.cpp util/vecmath.cpp util/error.cpp util/log.cpp

OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

$(PROGRAM_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# generic rule to build objects into build/, mirroring subdirectories
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean run render debug

clean:
	rm -rf $(BUILD_DIR) *.dSYM $(PROGRAM_NAME)

OUT ?= image.ppm

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS)

render: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS) > ../images/"$(OUT)"
	kitten icat ../images/"$(OUT)"

debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
debug: clean $(PROGRAM_NAME)

-include $(DEPS)
