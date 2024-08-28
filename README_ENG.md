# Mini-C Compiler to LLVM IR

This compiler is based on another project that was originally designed to generate MIPS assembly code; however, this one generates LLVM IR instead. The goals of this project are to learn about LLVM IR and the LLVM C++ API.

There are a few things to take into account:

* Mini-C is a very simple language without functions or even `for` loops. Although these features can be implemented, they are not the main goals of the project.
* It uses Flex + Bison and C++.
* This code should not be taken as an example of how to code in C++ since it has many improvable aspects.
* Every program must have a return statement that can be reached unconditionally.
* It uses LLVM 18.1.8.

## Usage

Once compiled with `make`, a binary called **comp** is created. By passing it a source code file, it will print the LLVM IR to stdout. (There are some source code examples in the directory test)

### Programs without input (read clause)

Simply use a bash pipe like this to pass it to the LLVM interpreter.

```shell
./comp file | lli
```

### Programs with input (read clause)

The previous method won't work in this case. Instead, something a little more complex can be used:

```shell
mkfifo /tmp/llvm_ir_pipe && ./comp file > /tmp/llvm_ir_pipe & lli /tmp/llvm_ir_pipe; rm /tmp/llvm_ir_pipe
```

## Short Explanation

As well as not being an example of how to code in C++, this project is not an example of how to use the LLVM API, since there are many ways to create a compiler with LLVM. I have chosen the approach closest to the original MIPS project.

In this case, a struct *ListaC* is used. It contains a vector with instructions and blocks (similar to MIPS tags) and a metadata field to differentiate them.

The instructions are added to the vector in the corresponding order. Finally, when there is no code left to analyze, the ``IRBuilder`` class creates the IR. That is to say, ``IRBuilder`` is only used at the end of the program; for the rest of the time, llvm::Instruction or similar classes are used. This is a different approach from the one proposed in the LLVM tutorials.

In the LLVM documentation and forums, a more direct usage of ``IRBuilder`` is recommended since it is a higher-level interface. However, this would imply building the AST in another way or reordering the instructions at certain points. Yet, changing that part of the project wasn't the objective, so Bison is used instead.

For the symbol table, a map is used. Furthermore, the file ``llvmHelper`` is used to include the necessary LLVM libraries and initialize the required values.
