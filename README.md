# malloc

_This project has been created as part of the 42 curriculum by molasz-a._

> Part of [42 Barcelona — molasz-a](https://github.com/Molasz/42), a monorepo centralizing every project completed at 42 Barcelona.

## Description

**malloc** is a project from the 42 curriculum that involves implementing a custom memory allocator in C. This project provides a deeper understanding of dynamic memory management, including heap allocation, deallocation, and memory fragmentation.

The implementation includes the standard `malloc`, `free` and `realloc` functions, along with a debugging function `show_alloc_mem` to visualize the current state of the heap.

---

## Implemented Functions

The following functions have been implemented:

| Function        | Description                                      |
| --------------- | ------------------------------------------------ |
| `malloc`        | Allocates a block of memory of the specified size |
| `free`          | Deallocates a previously allocated memory block  |
| `realloc`       | Changes the size of a previously allocated block |
| `show_alloc_mem`| Displays the current heap allocation state       |

---

## Architecture

![Skills](https://skillicons.dev/icons?i=c,linux)

The project is organized as follows:

- **`src/`**: Contains the implementation files for each function.
- **`includes/`**: Contains the header files defining the function prototypes.
- **`test/`**: Contains test programs to verify the functionality.

The `Makefile` compiles the source files into a shared library (`libmalloc.so`) and provides targets for testing.

---

## ⚙️ Instructions

```bash
# Compile the library
make

# Run the tests
make test

# Cleanup object files
make clean

# Cleanup object files and the library
make fclean

# Recompile the library
make re
```

To use the custom malloc in another program, preload the library:

```bash
gcc main.c -o main
LD_PRELOAD=./libmalloc.so ./main
```

---

_molasz-a · 42 Barcelona_