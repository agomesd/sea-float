# Sea-Float Test Framework

**Sea-Float** is a lightweight, project-agnostic **C test framework** for writing and running unit tests.  
It supports dynamic test registration, colored terminal output, and easy reuse as a static library across C projects.

---

## Features

- Define and register tests dynamically
- Run all tests with automatic pass/fail tracking
- Colorized terminal output:
  - ✅ Green for passed tests
  - ❌ Red for failed tests
- Generates a test summary with total, passed, and failed counts
- Easy to integrate into other projects as a **static library**
- Supports `install` and `uninstall` for system-wide usage

---

## Project Structure

sea-float/
├─ include/ # Public headers
│ └─ test-suite.h
├─ src/ # Framework implementation
│ └─ test-suite.c
├─ tests/ # Example usage & test cases
│ ├─ main.c
│ └─ tests.c
├─ build/ # Build artifacts (library, objects, executable)
├─ Makefile
└─ README.md

---

## Requirements

- GCC or any standard C compiler
- Unix-like environment (Linux/macOS/Windows with MinGW)
- Make

---

## Building and Running Tests

1. Clone the repository:

```bash
git clone [Repo](https://github.com/agomesd/sea-float)
cd sea-float
```

2. Build and run tests:

`make`

- This will:
  1.  Compile the framework

  2.  Compile test files

  3.  Link build/sea-float executable

  4.  Run tests with colored output and a summary

3. Clean build artifacts:

`make clean`

---

## Installing the Library System-wide

To use the framework in other projects:

`sudo make install`

- Installs the static library to /usr/local/lib/libsea-float.a

- Installs headers to /usr/local/include/sea-float/test-suite.h

To uninstall:

`sudo make uninstall`

---

## Using in Another Project

Once installed, you can include and link the framework in your C projects:

```
#include <sea-float/test-suite.h>

int my_test(void) {
    // return 0 = pass, 1 = fail
}

int main(void) {
    test_suite_t suite;
    test_suite_init(&suite, "MyProjectTests");

    register_test(&suite, my_test, "My test");
    run_all_tests(&suite);

    test_suite_destroy(&suite);
    return 0;
}
```

Compile your project with:

`gcc -I /usr/local/include/sea-float -L /usr/local/lib -lsea-float main.c -o myproject`

---

## Example Test Output

```
Now running test: Test add
Test Test add PASSED
Now running test: Test sub
Test Test sub FAILED

Test Summary for suite: test_suite
Total: 2, Passed: 1, Failed: 1
```

---

## Contributing

Contributions are welcome! You can:

Add new features

Improve colored output or formatting

Extend framework to support test fixtures or parameterized tests

Please submit a pull request or open an issue.

License

MIT License © 2026
