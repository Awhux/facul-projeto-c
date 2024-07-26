# Compiler
ifeq ($(OS),Windows_NT)
    CC = gcc
    RM = rmdir /S /Q
    MKDIR = mkdir
    TARGET = program.exe
else
    CC = gcc
    RM = rm -rf
    MKDIR = mkdir -p
    TARGET = program
endif

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Directories
OUTDIR = output

# Source files
SRCS = main.c

# Object files
OBJS = $(addprefix $(OUTDIR)/, $(SRCS:.c=.o))

# Default target
all: $(OUTDIR) $(TARGET)

# Create output directory
$(OUTDIR):
	$(MKDIR) $(OUTDIR)

# Linking (executable in root folder)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling
$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	$(RM) $(OUTDIR)
ifeq ($(OS),Windows_NT)
	if exist $(TARGET) del $(TARGET)
else
	$(RM) $(TARGET)
endif

.PHONY: all run clean
