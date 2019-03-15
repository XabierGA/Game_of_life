CFLAGS=-Wall
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

gameoflife_graphics: gameoflife_graphics.o graphics.o
	gcc -o gameoflife_graphics gameoflife_graphics.o graphics.o $(LDFLAGS)

gameoflife_graphics.o: gameoflife_graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c gameoflife_graphics.c

graphics.o: graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c graphics.c

clean:
	rm -f ./gameoflife_graphics *.o
