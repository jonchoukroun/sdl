CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c99

DEPS=l_texture.h main.h
OBJ=dist/l_texture.o dist/main.o
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf

dist/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

play: $(OBJ)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) -I include -o $@ $^
