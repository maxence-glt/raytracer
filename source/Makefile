PROGRAM_NAME = compiledCode
CPPFLAGS = -std=c++23 -O3 -march=native # -Weverything -Wno-c++98-compat -Wno-c++98-compat -Wno-c++98-compat-pedantic

$(PROGRAM_NAME): main.cpp
	clang++ $(CPPFLAGS) -o $(PROGRAM_NAME) main.cpp worlds.cpp integrations.cpp

.PHONY: clean run

clean:
	rm -rf *.o *.dSYM $(PROGRAM_NAME)

OUT ?= image.ppm

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS)

render: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS) > ../images/"$(OUT)"
	kitten icat ../images/"$(OUT)"
