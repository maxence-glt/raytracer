PROGRAM_NAME = compiledCode
CPPFLAGS = -std=c++23 -O3

$(PROGRAM_NAME): main.cpp
	clang++ $(CPPFLAGS) -o $(PROGRAM_NAME) main.cpp

.PHONY: clean run

clean:
	rm -rf *.o *.dSYM $(PROGRAM_NAME)

OUT ?= image.ppm

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS) > "$(OUT)"
	kitten icat "$(OUT)"
