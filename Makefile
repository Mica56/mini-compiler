SHELL := /bin/bash

.PHONY: run_program

run_program:
	gcc lexical.c -o a.out
	./a.out $(FILENAME)
	javac MulParser.java
	java MulParser



