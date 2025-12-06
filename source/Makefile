PROGRAM_NAME = compiledCode
CXX = /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS = -std=c++23 -O3
CPPFLAGS = -MMD -MP

SRCS := main.cpp worlds.cpp integrations.cpp util/vecmath.cpp util/error.cpp # util/log.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

$(PROGRAM_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean run render
clean:
	rm -rf $(OBJS) $(DEPS) *.dSYM $(PROGRAM_NAME)

OUT ?= image.ppm

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS)

render: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS) > ../images/"$(OUT)"
	kitten icat ../images/"$(OUT)"

-include $(DEPS)
