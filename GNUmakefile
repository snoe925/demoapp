all: app test
	echo "Build and test complete"

TSRCS=test/main.cpp test/demoapp_test.cpp
SRCS=app/main.cpp app/demoapp.h

app: build/CMakeCache.txt $(SRCS)
	cmake --build build

build/CMakeCache.txt: $(find . -name CMakeLists.txt)
	mkdir -p build
	cmake -E chdir build cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=OFF -DBUILD_EXTERNAL=OFF ..

debug: build.debug/CMakeCache.txt $(SRCS)
	cmake --build build.debug

build.debug/CMakeCache.txt: $(find . -name CMakeLists.txt)
	mkdir -p build.debug
	cmake -E chdir build.debug cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=OFF -DBUILD_EXTERNAL=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

build.test/CMakeCache.txt: $(find . -name CMakeLists.txt)
	mkdir -p build.test
	ln -s build.test out
	cmake -E chdir build.test cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON ..

build.test/test/demoapp-test: build.test/CMakeCache.txt $(TSRCS) $(SRCS)
	cmake --build build.test

test: build.test/test/demoapp-test $(SRCS) $(shell find test -type f)
	cmake -E chdir build.test test/demoapp-test

clean:
	rm -rf build.debug build.test build out

# Reformat with clang-format

format:
	git status | egrep 'modified:|new.file:' | egrep -v 'CMakeList|GNUmakefile|.vscode' | cut -f2 -d: | xargs echo clang-format -style=llvm  -i
	git status | egrep 'modified:|new.file:' | egrep -v 'CMakeList|GNUmakefile|.vscode' | cut -f2 -d: | xargs clang-format -style=llvm  -i

format-all:
	find . -name \*.h -o -name \*.cpp | xargs clang-format -style=file  -i

# Coverage profiling of tests

build.test/demoapp-test.profraw: build.test/test/demoapp-test
	cmake -E chdir build.test env LLVM_PROFILE_FILE=demoapp-test.profraw test/demoapp-test

coverage: build.test/demoapp-test.profraw
	xcrun llvm-profdata merge -sparse build.test/demoapp-test.profraw -o build.test/demoapp-test.profdata
	xcrun llvm-cov report -summary-only -instr-profile=build.test/demoapp-test.profdata build.test/test/demoapp-test app/*.cpp app/*.h

coverage-details: clean coverage
	xcrun llvm-cov show -format=html -show-line-counts -instr-profile=build.test/demoapp-test.profdata build.test/test/demoapp-test app/*.cpp app/*.h >build.test/coverage.html

stress-test: clean test
	cmake -E chdir build.test env LLVM_PROFILE_FILE=demoapp-test.profraw test/demoapp-test --gtest_repeat=27 --gtest_shuffle --gtest_output=json:out.json
	grep failure build.test/out.json
