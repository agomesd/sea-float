# Compiler and tools
CC = gcc
CFLAGS = -Wall -Wextra -I include
AR = ar
ARFLAGS = rcs

# Sources
SRC = src/test-suite.c
SRC_TEST = tests/main.c tests/tests.c

# Object files
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(SRC_TEST:.c=.o)

# Library and executable
LIB = build/libsea-float.a
TARGET = build/sea-float

# Install directories
PREFIX ?= /usr/local
INCDIR = $(PREFIX)/include/sea-float
LIBDIR = $(PREFIX)/lib

# Default target: build and run tests
all: $(TARGET)

# Build static library if any object changes
$(LIB): $(OBJ)
	@mkdir -p build
	$(AR) $(ARFLAGS) $@ $^

# Build test executable if test objects or library change
$(TARGET): $(TEST_OBJ) $(LIB)
	@mkdir -p build
	$(CC) $(CFLAGS) $(TEST_OBJ) -L build -lsea-float -o $@
	@echo "Running tests..."
	./$@

# Pattern rule for compiling .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Install library and headers
install: $(LIB)
	mkdir -p $(INCDIR)
	mkdir -p $(LIBDIR)
	cp include/test-suite.h $(INCDIR)/
	cp $(LIB) $(LIBDIR)/
	@echo "Library installed to $(LIBDIR) and headers to $(INCDIR)"

# Uninstall library and headers
uninstall:
	rm -f $(LIBDIR)/libsea-float.a
	rm -f $(INCDIR)/test-suite.h
	@echo "Library and headers removed from $(LIBDIR) and $(INCDIR)"

# Clean build artifacts
clean:
	rm -rf build/*.o build/libsea-float.a build/sea-float
