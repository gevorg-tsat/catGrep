CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LGFLAGS=
SOURCES1=cat/cat.c
SOURCES2=grep/grep.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=
EXECUTABLE1=cat/s21_cat
EXECUTABLE2=grep/s21_grep

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) 

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf cat/*.o grep/*.o $(EXECUTABLE) $(EXECUTABLE1) $(EXECUTABLE2)

build_cat:
	make SOURCES="$(SOURCES1)" EXECUTABLE=$(EXECUTABLE1) all

build_grep:
	make SOURCES="$(SOURCES2)" EXECUTABLE=$(EXECUTABLE2) all