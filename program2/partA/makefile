cc = g++  # use g++ compiler
path = ..
standard = c++17

flags = -std=$(standard)  # compile with standard
flags += -Wall  # compile with all warnings
flags += -pedantic  # even more warnings
flags += -I $(path)  # add parent to preprocessor include path
flags += -g  # include gdb instrumentation

link = $(cc) $(flags) -o  # final linked build to binary executable

compile = $(cc) $(flags) -c  # compilation to intermediary .o files

heap-bottom-up: main.o functions.o
	$(link) heap-bottom-up main.o functions.o

main.o: main.cc
	$(compile) main.cc

functions.o: functions.cc
	$(compile) functions.cc

clean:
	rm *.o heap-bottom-up