CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c99

#---- No header files ----#
#-------------------------#

# play: main.o
# 	$(CC) $(CFLAGS) -I include -L lib -l SDL2-2.0.0 -l SDL2_image-2.0.0 -o $@ $^

#---- With header files ----#
#---------------------------#

DEPS=l_texture.h l_button.h main.h
OBJ=dist/l_texture.o dist/l_button.o dist/main.o
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf

dist/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

play: $(OBJ)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) -I include -o $@ $^
