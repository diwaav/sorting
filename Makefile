CC = clang
CFLAGS = -Werror -Wall -Wextra -Wpedantic
TARGET = sorting
LFLAGS = -lm

OBJECTS = sorting.o insert.o heap.o quick.o stats.o shell.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.c stats.h 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) -f $(TARGET) *.o

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make
