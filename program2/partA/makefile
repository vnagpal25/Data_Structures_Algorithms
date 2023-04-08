cc = g++  # use g++ compiler
path = ..
standard = c++17

flags = -std=$(standard)  # compile with standard
flags += -Wall  # compile with all warnings
flags += -pedantic  # even more warnings
flags += -I $(path)  # add parent to preprocessor include path
flags += -g  # include gdb instrumentation

link = $(cc) $(flags) $^ -o #links all prerequisites

compile = $(cc) $(flags) -c $< -o #compiles first prerequisite

make: bin maxheap minheap

maxheap: bin/maxheap.o bin/functions.o
	$(link) $@

minheap: bin/minheap.o bin/functions.o
	$(link) $@

bin:
	mkdir -p bin

bin/maxheap.o: src/maxheap.cc
	$(compile) $@

bin/minheap.o: src/minheap.cc
	$(compile) $@

bin/functions.o: src/functions.cc
	$(compile) $@

clean:
	rm -f bin/*.o maxheap minheap