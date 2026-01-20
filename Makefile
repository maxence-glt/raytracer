.PHONY: run debug test clean rebuild configure-release configure-debug \
        build-release build-debug help

CXX := /opt/homebrew/opt/llvm/bin/clang++
ARGS ?=

configure-release:
	cmake -S . -B build/release \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-G Ninja

configure-debug:
	cmake -S . -B build/debug \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-G Ninja

build-release: configure-release
	cmake --build build/release -j
	rm compile_commands.json
	mv build/release/compile_commands.json .

build-debug: configure-debug
	cmake --build build/debug -j

run: build-release
	./build/release/raytracer $(ARGS)

OUT ?= image.exr
render: build-release
	./build/release/raytracer
	kitten icat "$(OUT)"

debug: build-debug
	./build/debug/raytracer_debug $(ARGS)

debug-render: build-debug
	./build/debug/raytracer_debug $(ARGS) > images/debug-"$(OUT)"
	kitten icat images/debug-"$(OUT)"

test: configure-debug
	cmake --build build/debug --target tests -j
	ctest --test-dir build/debug --output-on-failure

clean:
	rm -rf build/release build/debug

rebuild: clean run

help: configure-release
	cmake --build build/release --target help
