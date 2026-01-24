# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -O2 -Iinclude

# Directories
OBJDIR := obj

# Target executable (default, can be overridden)
TARGET ?= watch_changes

.PHONY: objects
objects:
	$(CC) $(CFLAGS) -c $(lib/%.c) -o obj

