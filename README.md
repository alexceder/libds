# Data structures library in ANSI C

This is a project of mine where I try and figure out how the C language works. It is also an exercise in data structures, testing and general programming. But it's really just an excuse to do something.

If you find any errors I've made or other improvements that can be made, please tell me about it and maybe how to fix it.

I've learned a few thing and hopefully someone else can too.

## Data structures

The library contains the following data structures:

### Binary Heap (bheap)

Depends on the **vector** part of the library.

**status:** Ready

### Binary Search Tree(bst)

**status:** Not ready, removal does not exist.

### Hash Table (hash)

Utilizes linear probing for resolving collisions.

**status:** Ready

### Singly Linked List (slist)

The list is implemented as sorted. It is missing a lot of methods. It should probably be implemented more generally. The problem is that an ``insert_after`` method needs to have a pointer to a node, but we don't want to have the nodes visible to the user. One solution would be an interator, but that would get rather verbose. Thoughts on this are appreciated.

**status:** Not ready, needs more operations probably even an overhaul.

### Vector (vector)

Vector is implemented inspired by the C++ STL and includes a subset of its methods and a few other.

**status:** Ready

## Compiling

Use the ``make`` utility to compile the library.

For production you may run just ``make`` to compile and build the library to a library file that can be included to your library path.

Running only ``make tests`` will compile to binaries and run tests for all parts of the library.

You may run ``make <part>`` to compile and run tests for a certain part. e.g. ``make hash`` will compile and run tests for the hash table part of the library.

## Usage

So if you are still hell bent on using the library for any ridiculous reason. Compile a shared library by running ``make`` and include the ``lds.h`` file in your program. You may of course only include a single header file if that is just what you need. See the example below:

```c
#include <stdio.h>
#include <stdlib.h>
#include "lds.h"

int main() {
    char *dump;
    list *l;
    htable *h;

    l = list_create();
    list_insert(l, "carl");
    list_insert(l, "alex");
    list_insert(l, "bobby");

    puts("\nTesting the singly linked list.");
    dump = list_dump(l);
    printf("%s\n", dump);
    free(dump);

    list_destroy(l);

    h = htable_create();

    htable_insert(h, "this is a key", "this is a value");

    puts("\nTesting the hash table.");
    printf("%s\n", htable_find(h, "this is a key"));

    htable_destroy(h);

    return 0;
}
```

Compiling and running the program above will output:

```
$ gcc test.c -o test -I./include -L./shared -lds && ./test

Testing the singly linked list.
{ alex bobby carl }

Testing the hash table.
this is a value
```

## Author

Alexander Cederblad <<alexcederblad@gmail.com>>  
www.alexceder.se  
@alexceder

## License

The MIT Licence (MIT)

Copyright (c) 2014 Alexander Cederblad

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
