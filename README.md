# Square Problem Solver (How many squares can you see?)

An application that simply solves the square problem. The app comes with unit tests (CTest+Unity) and builds trough CMake+Make.

## Prerequisites 
- git
- CMake
- make
- Any C Compiler

## Build instructions
In the top folder:
```
$ mkdir build && cd build
$ cmake -DCMAKE_C_COMPILER=<Your_C_Compiler> ..
$ make
```

## Application Execution
Inside the top/build folder:
```
$ ./Square_App
```

To exit the app, input n=0.

## Unit Testing
To execute the unit tests, inside the top/build folder:
```
$ ctest -V
```
All unit tests should pass if no modifications has been made to the source or test code.
