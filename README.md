# Multi-Unimolecular Language (MUL) - mini-compiler

Needed Dependencies
- JDK 16.1
- gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

## Usage
To run this project on Linux Manually

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



## References for Documentation
- Checkout our [Documentation](https://docs.google.com/document/d/1jL--KCBrAb3tdpe1NQFmuw6aDuBinwDqdtXAIhM-xTw/edit?usp=sharing)

