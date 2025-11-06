PROGRAM_NAME = compiledCode
CXX = clang++
CXXFLAGS = -std=c++23 -O3 -march=native
CPPFLAGS = -MMD -MP

SRCS := main.cpp worlds.cpp integrations.cpp util/vecmath.cpp
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
