# Compiler and flags
CC      = gcc
CFLAGS  = -std=c99 -O -Wall -Wextra -c
LDFLAGS = 

# Files
TARGET  = leaf
SOURCE  = leaf.c
OBJS    = leaf.o

# Build target
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files
$(OBJS): $(SOURCE)
	$(CC) $(CFLAGS) -o $(OBJS) $(SOURCE)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Clean up LaTeX files
latex-clean:
	rm -f *.aux *.log *.dvi *.toc *.out *.bbl *.blg *.lof *.lot *.fls *.fdb_latexmk
