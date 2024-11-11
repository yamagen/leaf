# Compiler and flags
CC      = gcc
CFLAGS  = -std=c99 -O -Wall -Wextra -c
LDFLAGS = 

# Files
TARGET  = slp
SOURCE  = slp.c
OBJS    = slp.o
TEXRM   = $(wildcard *.aux *.log *.dvi *.toc *.out *.bbl *.blg *.lof *.lot *.fls *.fdb_latexmk *.synctex.gz)

# Build target
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files
$(OBJS): $(SOURCE)
	$(CC) $(CFLAGS) -o $(OBJS) $(SOURCE)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS) $(TEXRM)
