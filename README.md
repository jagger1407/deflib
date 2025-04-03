# deflib
deflib, originally short for "Default Library" (as a reference to stdlib - Standard Library) is a library I made to simplify making programs in C++.

I tried to keep the syntax similar to Java or C#, while also giving the programmer freedom to use the underlying data in its C form. This way, 
people who come from Java or similar languages can handle C++ without namespace std.
## Overview
This library is meant to handle allocated memory via constructors and destructors. It creates objects on the stack while creating the data it's representing
on the heap (via malloc/realloc), and relies heavily on copying.

the `string` class can create strings from `char*`s, and can be added to using + and +=.

If direct access or manual memory management is wished, a `c_str()` function returns the underlying C String.

Collection Classes (Arrays + ArrayLists) can take any data type via templates. The data type can be converted via C-Style type casting, 
or reinterpreted using either `reinterpret<>()` or `reinterpretCopy<>()`. Important to note is that the former method invalidates the previous pointer.

If direct access or manual memory management is wished, a `ptr()` function returns the underlying C-Style pointer.

This library also has a class called `Cvt` which handles type conversions, similar to C#s `Convert` class.

## Usage
In order to use this library, download the deflib folder from this repo and use 
```cpp
#include "deflib/deflib.h"
```
in your source code.

In case you want your projects entry function to be similar to Java as well, a  `boot.cpp` is included.
It expects a file called `main.h` to exist in the same directory and contain a public static Main function.

An example main class is included in this repo.
