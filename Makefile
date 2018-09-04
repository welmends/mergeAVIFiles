#mergeAVI makefile

all: callShell mergeAVI run

callShell:
	$(shell mkdir -p objs avi_out)

mergeAVI: src/mergeAVI.cpp
	g++ src/mergeAVI.cpp -o objs/mergeAVI.o `pkg-config opencv --cflags --libs opencv`

run:
	objs/mergeAVI.o

clean:
	rm -rf objs/mergeAVI.o

PREFIX ?= /usr


.PHONY: clean all mergeAVI run
