# go-NOM
A golang based Network Object library for storing information on chemical reaction networks.  

## Description

The library supports the storage and management of information that represents a reaction network. In addition to the 
species and reactions, the library also stores visualization information including positioning and various visual attributes of species and reactions. These are sumamrized below.

# Object Model

### Features

As well and providing settters and getters for the various data items stored in the model, the object also support undo/redo. That is any operations applied to the model can be undo or redo by calling the undo and redo methods. Inaddition, the model provides a means to pserist the object model in the form of json import and export. 

## Object Model

Describe the object model, network, nodes and reactions. Maybe a simple UML diagram would work.

# How to use the library

The NOM can be used from golang, Python or C.

## Example of using the C API

Provide an example of using the library from C

The library has been precompiled as a 64-bit DLL, iodine.dll. This can be used directly in a host application. The iodine.h is header file and contains all the C method signatures.

see [user_Demo.c](https://github.com/zrj26/go-NOM/blob/master/Iodine_C_API/user_Demo.c)

## Example of using the Python interface

Provide an example of using the library from Python

## Running the Tests

see [testIodine.py](https://github.com/zrj26/go-NOM/blob/master/Iodine_python_API/testIodine.py)

see [unit_test.c](https://github.com/zrj26/go-NOM/blob/master/Iodine_C_API/unit_test.c)

# API Documenation

[Documentation for the Go API](https://github.com/zrj26/go-NOM/blob/master/docs/Go-NOM%20documentation.md)

# Download


