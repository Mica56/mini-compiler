# Multi-Unimolecular Language (MUL) - mini-compiler

Needed Dependencies
- JDK 16.1
- gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

File Name Conventions/Equivalents
- **file.mul** => sample output file
- **lexical.c** => The actual lexical analyzer file. its responsible for lexical operations. 
- **MulParser.java** => The actual syntax analyzer file. its responsible for analyzing syntax and grammar of our language.
- **output.mul** => part of the output of the lexical analyzer. generates  a symbol table for the syntax analyzer for later.
- **output.multree** => output of the syntax analyzer. Contains the flattened form of the syntax tree for later use.
- **a.out** => compiled form of the lexical
- **Makefile** => contains default instructions to autocompile all programs.
 
## Usage
### To run this project on Linux Manually

Compile the lexical compiler and generate the symbol table.
```shell
gcc lexical.c -o a.out
./a.out <filename>
```

Run the syntax analyzer and generate the Syntax Tree in Flattened Form.
This program will detect for any "output.mul" in the current directory.

```shell
javac MulParser.java
java MulParser
```
### To run this project the lazy way on Linux

Just use our makefile program!

file.mul => the corresponding file name for your source code.
```shell
make run_program FILENAME=<file.mul>
```


## References for Documentation
- Checkout our [Documentation](https://docs.google.com/document/d/1jL--KCBrAb3tdpe1NQFmuw6aDuBinwDqdtXAIhM-xTw/edit?usp=sharing)

